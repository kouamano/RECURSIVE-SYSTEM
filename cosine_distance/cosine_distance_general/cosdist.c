#include <stdio.h>
#include <memory.h>
#include <malloc.h>
#include <errno.h>
#include <stdlib.h>
#include <math.h>

#define LEN_FILENAME 1000
#define FIELD_SEPARATOR ','

int DEBUG_MODE = 0;
void get_option(int argc, char** argv, char* filename, int* num, int* dim);
void print_usage(char* progname);
void read_data(char* filename, int num, int dim, double* Data);
void printArray(char* arrayname, double* A, int num, int dim);
void output_results(char* filename, double* CosineDistance, int num);

int MAIN__(int argc, char** argv) {
    int num;  // number of data
    int dim;  // dimension of each data
    char filename[LEN_FILENAME];
    get_option(argc, argv, filename, &num, &dim);

    // 0. cosinedist(ij) = 1 - V(i)V(j)/(Length(V(i))*Length(V(j)))

    // 1. read data
    double* V = (double*)malloc(sizeof(double)*num*dim);
    memset(V, 0, sizeof(double)*num*dim);
    read_data(filename, num, dim, V);
    printArray("V", V, num, dim);

    // 2. InnerProduct = VV'
    double* InnerProduct = (double*)malloc(sizeof(double)*num*num);
    memset(InnerProduct, 0, sizeof(double)*num*num);
    char transa = 'N', transb = 'T';
    int m = num, n = num, k = dim;
    int lda = num, ldb = num, ldc = num;
    double alpha = 1.0f, beta = 0.0f;
    dgemm_(&transa, &transb, &m, &n, &k, &alpha, V, &lda, V, &ldb, &beta, InnerProduct, &ldc);
    printArray("InnerProduct", InnerProduct, num, num);

    // 3. Norm of each vector
    double* Norm = (double*)malloc(sizeof(double)*num);
    for (int i = 0; i < num; i++) {
        Norm[i] = sqrt(InnerProduct[i*num+i]);
    }
    printArray("Norm", Norm, 1, num);

    // 4. Norm product matrix
    double* NormProduct = (double*)malloc(sizeof(double)*num*num);
    memset(NormProduct, 0, sizeof(double)*num*num);
    char uplo = 'U';
    n = num;
    alpha = 1.0f;
    int incx = 1;
    lda = num;
    dsyr_(&uplo, &n, &alpha, Norm, &incx, NormProduct, &lda);
    printArray("NormProduct", NormProduct, num, num);

    // 5. CosineDistance(ij) = 1-InnerProduct(ij)/NormProduct(ij)
    double* CosineDistance = (double*)malloc(sizeof(double)*num*num);
    memset(CosineDistance, 0, sizeof(double)*num*num);
    for (int i = 0; i < num; i++) {
        for (int j = 0; j < num; j++) {
            int n = j*num+i;
            if (j<=i) {
                CosineDistance[n] = 0.0;
            }
            else {
                CosineDistance[n] = 1 - InnerProduct[n]/NormProduct[n];
            }
        }
    }
    printArray("CosineDistance", CosineDistance, num, num);

    output_results("result.txt", CosineDistance, num);

    free(V);
    free(InnerProduct);
    free(Norm);
    free(NormProduct);
    free(CosineDistance);

    return 0;
}

void get_option(int argc, char** argv, char* filename, int* num, int* dim) {
    char mode = '0';
    int check = 0;
    for (int i = 1; i < argc; i++) {
        switch(mode) {
            case 'f':
                strcpy(filename, argv[i]);
                check |= 0x01;
                mode = '0';
                break;
            case 'n':
                *num = atoi(argv[i]);
                if (*num>0) {
                    check |= 0x02;
                }
                mode = '0';
                break;
            case 'd':
                *dim = atoi(argv[i]);
                if (*dim>0) {
                    check |= 0x04;
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
    if(check != 0x07) {
        print_usage(argv[0]);
        exit(1);
    }
    return;
}

void print_usage(char* progname) {
    printf("Usage: %s -f INPUT_FILE -n NUM_OF_DATA -d DATA_DIMENSION\n", progname);
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

void printArray(char* arrayname, double* A, int num, int dim) {
    if(DEBUG_MODE) {
        printf("%s\n", arrayname);
        for (int j = 0; j<num; j++) {
            for (int i = 0; i < dim; i++) {
                printf("%.5lf,", A[j+num*i]);
            }
            printf("\n");
        }
    }
}

void output_results(char* filename, double* CosineDistance, int num) {
    FILE* fp;
    if ((fp = fopen(filename,"w")) == NULL) {
        printf("fopen error: file=%s, errno=%d", filename, errno);
        exit(1);
    }
    for (int i = 0; i < num; i++) {
        for (int j = 0; j < num; j++) {
            fprintf(fp, "%lf,", CosineDistance[j*num+i]);
        }
        fprintf(fp,"\n");
    }
    fclose(fp);
}

