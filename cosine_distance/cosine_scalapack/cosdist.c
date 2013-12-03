#include <stdio.h>
#include <memory.h>
#include <malloc.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define LEN_FILENAME 1000
#define FIELD_SEPARATOR ','

int DEBUG_MODE = 0;
void get_option(int argc, char** argv, char* ifilename, char* ofilename, int* num, int* dim);
void print_usage(char* progname);
void read_data(char* filename, int num, int dim, double* Data);
void printArray(char* arrayname, int myproc, double* A, int num, int dim);
void output_results(char* filename, double* CosineDistance, int num, int dim);

int MAIN__(int argc, char** argv) {
    int num;  // number of data
    int dim;  // dimension of each data
    int nprow=4; // number of row
    int npcol=1;  // number of columnn
    int zero=0, one=1; // constant value
    int ictxt,myrow,mycol,pnum,pdim,info;
    char ifilename[LEN_FILENAME];
    char ofilename[LEN_FILENAME];

    int myproc, nprocs;
    Cblacs_pinfo(&myproc, &nprocs);
    Cblacs_setup(&myproc, &nprocs);
    Cblacs_get(-1,0,&ictxt);
    nprow = nprocs;
    npcol = 1; // fixed

    char order[] = "Row";
    Cblacs_gridinit(&ictxt, order, nprow, npcol);
    Cblacs_gridinfo(ictxt, &nprow, &npcol, &myrow, &mycol);

    if (DEBUG_MODE) {
        printf("ConTxt = %d\n", ictxt);
        printf("nprocs=%d, nprow=%d, npcol=%d\n", nprocs, nprow, npcol);
        printf("nprocs=%d, myrow=%d, mycol=%d\n", nprocs, myrow, mycol);
    }

    get_option(argc, argv, ifilename, ofilename, &num, &dim);

    // 0. cosinedist(ij) = 1 - V(i)V(j)/(Length(V(i))*Length(V(j)))

    // 1. calculate submatrix size
    int bsize = num / nprow; // blocking factor
    pnum = num / nprow;
    pdim = dim;
    if ( myrow < (num/bsize)%nprow) {
        pnum += bsize;
    }
    else if ( myrow == (num/bsize)%nprow) {
        pnum += (num % bsize);
    }
    else {
    }
    if(DEBUG_MODE)
        printf("myproc=%d: pnum=%d, pdim=%d, bsize=%d\n", myproc, pnum, pdim, bsize);

    int desc_input[9], desc_v[9], desc_ip[9], desc_n[9], desc_result[9];
    descinit_(desc_input,  &num, &dim, &num,   &dim,  &zero, &zero, &ictxt, &num,  &info);
    descinit_(desc_v,      &num, &dim, &bsize, &pdim, &zero, &zero, &ictxt, &pnum, &info);
    descinit_(desc_ip,     &num, &num, &bsize, &num,  &zero, &zero, &ictxt, &pnum, &info);
    descinit_(desc_n,      &num, &one, &bsize, &one,  &zero, &zero, &ictxt, &pnum, &info);
    descinit_(desc_result, &num, &num, &num,   &num,  &zero, &zero, &ictxt, &num,  &info);

    // 2. read input data
    double* input;
    if (myproc == 0) {
        input = (double*)malloc(sizeof(double)*num*dim);
        memset(input, 0, sizeof(double)*num*dim);
        read_data(ifilename, num, dim, input);
        printArray("input", myproc, input, num, dim);
    }

    // 3. distribute input data array
    double* V = (double*)malloc(sizeof(double)*pnum*pdim);
    memset(V, 0, sizeof(double)*pnum*pdim);
    Cpdgemr2d(num, dim, input, 1, 1, desc_input, V, 1, 1, desc_v, ictxt);
    printArray("V", myproc, V, pnum, pdim);

    // 4. InnerProduct = VV'
    double* InnerProduct = (double*)malloc(sizeof(double)*pnum*num);
    memset(InnerProduct, 0, sizeof(double)*pnum*num);
    char transa = 'N', transb = 'T';
    int m = num, n = num, k = dim;
    int lda = num, ldb = num, ldc = num;
    double alpha = 1.0f, beta = 0.0f;
    pdgemm_(&transa, &transb, &m, &n, &k, &alpha, V, &one, &one, desc_v, V, &one, &one, desc_v, &beta, InnerProduct, &one, &one, desc_ip);
    printArray("InnerProduct", myproc, InnerProduct, pnum, num);

    // 5. Norm of each vector
    double* Norm = (double*)malloc(sizeof(double)*pnum);
    for (int i = 0; i < pnum; i++) {
        int n = ((myproc*bsize)+(i/bsize)*(nprocs-1)*bsize+i)*pnum + i;
        Norm[i] = sqrt(InnerProduct[n]);
    }
    printArray("Norm", myproc, Norm, 1, pnum);

    // 6. Norm product matrix
    double* NormProduct = (double*)malloc(sizeof(double)*pnum*num);
    memset(NormProduct, 0, sizeof(double)*pnum*num);
    char uplo = 'U';
    n = num;
    alpha = 1.0f;
    int incx = 1;
    lda = num;
    pdsyr_(&uplo, &n, &alpha, Norm, &one, &one, desc_n, &incx, NormProduct, &one, &one, desc_ip);
    printArray("NormProduct", myproc, NormProduct, pnum, num);

    // 7. CosineDistance(ij) = 1-InnerProduct(ij)/NormProduct(ij)
    double* CosineDistance = (double*)malloc(sizeof(double)*pnum*num);
    memset(CosineDistance, 0, sizeof(double)*pnum*num);
    for (int j = 0; j < num; j++) {
        for (int i = 0; i < pnum; i++) {
            int n = ((myproc*bsize)+i+(i/bsize)*(nprocs-1)*bsize)*pnum+i;
            int p = i+j*pnum;
            if (p<=n) {
                CosineDistance[p] = 0.0;
            }
            else {
                CosineDistance[p] = 1 - InnerProduct[p]/NormProduct[p];
            }
        }
    }
    printArray("CosineDistance", myproc, CosineDistance, pnum, num);

    // 8. gather result
    double* result;
    if ( myproc == 0 ) {
        result = (double*)malloc(sizeof(double)*num*num);
        memset(result, 0, sizeof(double)*num*num);
    }
    Cpdgemr2d(num, num, CosineDistance, 1, 1, desc_ip, result, 1, 1, desc_result, ictxt);

    // 9. output to file
    if ( myproc == 0 ) {
        output_results(ofilename, result, num, num);
    }

    // a. cleanup memory
    free(V);
    free(InnerProduct);
    free(Norm);
    free(NormProduct);
    free(CosineDistance);
    if ( myproc == 0 ) {
        free(input);
        free(result);
    }

    blacs_exit_(&zero);

    return 0;
}

void get_option(int argc, char** argv, char* ifilename, char* ofilename, int* num, int* dim) {
    char mode = '0';
    int check = 0;
    for (int i = 1; i < argc; i++) {
        switch(mode) {
            case 'i':
                strcpy(ifilename, argv[i]);
                check |= 0x01;
                mode = '0';
                break;
            case 'o':
                strcpy(ofilename, argv[i]);
                check |= 0x02;
                mode = '0';
                break;
            case 'n':
                *num = atoi(argv[i]);
                if (*num>0) {
                    check |= 0x04;
                }
                mode = '0';
                break;
            case 'd':
                *dim = atoi(argv[i]);
                if (*dim>0) {
                    check |= 0x08;
                }
                mode = '0';
                break;
            default:
                if((argv[i][0] == '-') && (strlen(argv[i]) == 2)) {
                    mode = argv[i][1];
                }
                else if(strcmp(argv[i], "--debug") == 0) {
                    DEBUG_MODE = 1;
                }
                break;
        }
    }
    if(check != 0x0F) {
        print_usage(argv[0]);
        exit(1);
    }
    return;
}

void print_usage(char* progname) {
    printf("Usage: %s -i INPUT_FILE -o OUTPUT_FILE -n NUM_OF_DATA -d DATA_DIMENSION\n", progname);
    return;
}

void read_data(char* filename, int num, int dim, double* Data) {
    // read data
    FILE* fp;
    if ((fp = fopen(filename,"r")) == NULL) {
        printf("fopen error: file=%s, errno=%d", filename, errno);
        exit(1);
    }
    fseek(fp, 0, SEEK_END);
    int size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char* buff = (char*)malloc(size + 1);

    int i = 0;
    while (fgets(buff, size, fp) != NULL) {
        char* p = buff;
        for (int d = 0; d < dim; d++) {
            // read by "Column Major" for Fortran function
            Data[i+num*d] = atof(p);
            p = strchr(p, FIELD_SEPARATOR);
            if (p == NULL) {
                if (d < dim-1) {
                    printf("Error: Line %d has only %d (<%d) dimension(s).\n", i+1, d+1, dim);
                    exit(1);
                }
                break;
            }
            p++;
        }
        i++;
        if (i >= num) {
            break;
        }
    }
    if (i!=num) {
        printf("Error: %s has only %d lines. Set correct value to -n option.\n", filename, i);
        exit(1);
    }
    fclose(fp);
    free(buff);
}

void printArray(char* arrayname, int myproc, double* A, int num, int dim) {
    if(DEBUG_MODE) {
        printf("%s (p: %d)\n", arrayname, myproc);
        for (int j = 0; j<num; j++) {
            for (int i = 0; i < dim; i++) {
                printf("%.5lf,", A[j+num*i]);
            }
            printf("\n");
        }
    }
}

void output_results(char* filename, double* CosineDistance, int num, int dim) {
    FILE* fp;
    if ((fp = fopen(filename,"w")) == NULL) {
        printf("fopen error: file=%s, errno=%d", filename, errno);
        exit(1);
    }
    for (int i = 0; i < num; i++) {
        for (int j = 0; j < dim; j++) {
            fprintf(fp, "%lf,", CosineDistance[j*num+i]);
        }
        fprintf(fp,"\n");
    }
    fclose(fp);
}

