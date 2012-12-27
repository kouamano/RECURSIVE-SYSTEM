/*drop-utf8.c*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/home/pub/include/alloc.c"
#define FILE_NAME_SIZE 1024
#define UTF_BUF_SIZE 7

/* help */
void help(void){
	printf("USAGE:\n");
	printf("  drop-utf8 [<file>] [-h]\n");
	printf("DESCRIPTION:\n");
	printf("  drop-utf8 put insufficient code to STDERR.\n");
}

/* main */
int main(int argc, char **argv){
	/* vers */
	FILE *IN;
	//char file_name[FILE_NAME_SIZE];
	int is_open = 0;
	int in_stream = 0;
	int is_put = 0;
	int C = 0;
	int D = 0;
	int i = 0;
	int incomplete_utf = 0;
	//int in_utf = 0;
	//int utf_len = 0;
	int utf_expected_len = 0;
	char *utf_buf;
	utf_buf = c_calloc_vec(UTF_BUF_SIZE);

	/* file open */
	if(argc == 1){
		IN = stdin;
		in_stream = 1;
	}else if(argc == 2){
		if(strcmp(argv[1],"-h") == 0){
			help();
			exit(0);
		}else{
			IN = fopen(argv[1],"r");
			if(IN == NULL){
				perror(argv[1]);
				exit(1);
			}else{
				is_open++;
				in_stream = 1;
			}
		}
	}

	/* func */
	while(in_stream >= 1){
		//if(in_utf == 0){
			C = fgetc(IN);
		//}
		if(C == EOF){
			in_stream = 0;
			break;
		}
		if(C >= 0x00 && C <= 0x7f){ /* ASCII */
			incomplete_utf = 0;
			is_put = 0;
		}else if(C >= 0xc0 && C <= 0xdf){ /* 110yyyyx */
			utf_expected_len = 2;
			incomplete_utf = 0;
			utf_buf[0] = C;
			for(i=1;i<utf_expected_len;i++){
				D = fgetc(IN);
				if(D >= 0x80 && D <= 0xbf){
					;
				}else{
					incomplete_utf++;
				}
				utf_buf[i] = D;
			}
			utf_buf[i] = '\0';
			is_put = 0;
		}else if(C >= 0xe0 && C <= 0xef){ /* 1110yyyy */
			utf_expected_len = 3;
			incomplete_utf = 0;
			utf_buf[0] = C;
			for(i=1;i<utf_expected_len;i++){
				D = fgetc(IN);
				if(D >= 0x80 && D <= 0xbf){
					;
				}else{
					incomplete_utf++;
				}
				utf_buf[i] = D;
			}
			utf_buf[i] = '\0';
			is_put = 0;
		}else if(C >= 0xf0 && C <= 0xf7){ /* 11110yyy */
			utf_expected_len = 4;
			incomplete_utf = 0;
			utf_buf[0] = C;
			for(i=1;i<utf_expected_len;i++){
				D = fgetc(IN);
				if(D >= 0x80 && D <= 0xbf){
					;
				}else{
					incomplete_utf++;
				}
				utf_buf[i] = D;
			}
			utf_buf[i] = '\0';
			is_put = 0;
		}else if(C >= 0xf8 && C <= 0xfb){ /* 111110yy */
			utf_expected_len = 5;
			incomplete_utf = 0;
			utf_buf[0] = C;
			for(i=1;i<utf_expected_len;i++){
				D = fgetc(IN);
				if(D >= 0x80 && D <= 0xbf){
					;
				}else{
					incomplete_utf++;
				}
				utf_buf[i] = D;
			}
			utf_buf[i] = '\0';
			is_put = 0;
		}else if(C >= 0xfc && C <= 0xfd){ /* 1111110y */
			utf_expected_len = 6;
			incomplete_utf = 0;
			utf_buf[0] = C;
			for(i=1;i<utf_expected_len;i++){
				D = fgetc(IN);
				if(D >= 0x80 && D <= 0xbf){
					;
				}else{
					incomplete_utf++;
				}
				utf_buf[i] = D;
			}
			utf_buf[i] = '\0';
			is_put = 0;
		}else{
			is_put++;
		}
		if(incomplete_utf > 0){
			fprintf(stderr,"%s",utf_buf);
		}
		if(is_put > 0){
			fputc(C,stdout);
			//is_put = 0;
		}
	}

	/* file close */
	if(is_open > 0){
		fclose(IN);
	}
	return(0);
}
