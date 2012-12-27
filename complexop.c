/* complexop.c */

/* NEEDS:      */
/* complexop.h */
/* <math.h>    */

/* PROCEDURES:                 */
/* alloc_cmplx_vec()           */
/* calloc_cmplx_vec()          */
/* calloc_cmplx_vec_ptr()      */
/* scaled_cmplx_vec()          */
/* abs_cmplx()                 */
/* plus_cmplx()                */
/* minus_cmplx()               */
/* times_cmplx()               */
/* division_cmplx()            */
/* print_cmplx_vec()           */
/* read_complex_vec_from_fp()  */
/* conjugate_complex_vec()     */
/* conjugate_new_complex_vec() */
/* product_complex_vec()       */
/* convolve_complex_vec()      */

#ifndef SHORT_BUFF_SIZE
#define SHORT_BUFF_SIZE 512
#endif
#ifndef BRK_S
#define BRK_S "{"
#endif
#ifndef BRK_E
#define BRK_E "}"
#endif

struct cmplx *alloc_cmplx_vec(struct cmplx *ptr, size_t size){
	if((ptr = (struct cmplx *)malloc(sizeof(struct cmplx) * size)) == NULL){
		fprintf(stderr,"[E]failed malloc in alloc_cmplx_list().\n");
		exit(1);
	}
	return(ptr);
}

struct cmplx *calloc_cmplx_vec(struct cmplx *ptr, size_t size){
	if((ptr = (struct cmplx *)calloc(size,sizeof(struct cmplx))) == NULL){
		fprintf(stderr,"[E]failed malloc in alloc_cmplx_list().\n");
		exit(1);
	}
	return(ptr);
}

struct cmplx **calloc_cmplx_vec_ptr(struct cmplx **ptr, size_t size){
	if((ptr = calloc(size,sizeof(struct cmplx *))) == NULL){
		fprintf(stderr,"[E]failed calloc() in calloc_cmplx_vec_ptr().\n");
		exit(1);
	}
	return(ptr);
}

struct cmplx *scaled_cmplx_vec(const struct cmplx *ptr, unsigned int size, int scale, struct cmplx *scaled_ptr){
	int i = 0;
	int j = 0;
	int scaled_position = 0;
	if(scaled_ptr == NULL){
		scaled_ptr = alloc_cmplx_vec(scaled_ptr, size*scale);
	}
	for(i=0;i<size;i++){
		for(j=0;j<scale;j++){
			scaled_ptr[scaled_position] = ptr[i];
			scaled_position++;
		}
	}
	return(scaled_ptr);
}

float abs_cmplx(struct cmplx n){
	float ret = 0;
	ret = sqrt(powf(n.real,2) + powf(n.image,2));
	return(ret);
}

struct cmplx plus_cmplx(struct cmplx ptr1, struct cmplx ptr2){
	struct cmplx ret;
	ret.real = (ptr1).real + (ptr2).real;
	ret.image = (ptr1).image + (ptr2).image;
	return(ret);
}

struct cmplx minus_cmplx(struct cmplx ptr1, struct cmplx ptr2){
	struct cmplx ret;
	ret.real = ptr1.real - ptr2.real;
	ret.image = ptr1.image - ptr2.image;
	return(ret);
}

struct cmplx times_cmplx(struct cmplx ptr1, struct cmplx ptr2){
	struct cmplx ret;
	ret.real = ptr1.real * ptr2.real - ptr1.image * ptr2.image;
	ret.image = ptr1.real * ptr2.image + ptr1.image * ptr2.real;
	return(ret);
}

struct cmplx division_cmplx(struct cmplx ptr1, struct cmplx ptr2){
	struct cmplx ret;
	struct cmplx n;
	float denominator = 0;
	n.real = ptr2.real;
	n.image = -ptr2.image;
	denominator = (ptr2.real * n.real - ptr2.image * n.image);
	ret = times_cmplx(ptr1,n);
	ret.real = ret.real / denominator;
	ret.image = ret.image / denominator;
	return(ret);
}

void print_cmplx_vec(struct cmplx *ptr, int size, char *format){
	int i = 0;
	if(strcmp(format,"Mathematica") == 0){
		printf(BRK_S);
		printf("%f + %f I",ptr[0].real,ptr[0].image);
		for(i=1;i<size;i++){
			printf(",\n%f + %f I",ptr[i].real,ptr[i].image);
		}
		printf(BRK_E);
		printf("\n");
	}else{
		printf("%f:%f",ptr[0].real,ptr[0].image);
		for(i=1;i<size;i++){
			printf(",%f:%f",ptr[i].real,ptr[i].image);
		}
	}
}

long int read_cmplx_vec_from_fp(struct cmplx *MW, int fmt, char fs, FILE *fp){
	signed char c = '\0';
	char *buff = NULL;
	int real_fill = 0;
	int image_fill = 0;
	int buff_position = 0;
	int cmplx_position = 0;
	if((buff = (char *)calloc(sizeof(char),SHORT_BUFF_SIZE)) == NULL){
		printf("[E]failed calloc() in read_cmplx_vec_from_fp.\n");
		exit(1);
	}
	if(fmt == 1){
		while((c = (signed char)fgetc(fp)) != EOF){
			if(c == fs){
				if((real_fill == 0)&&(1)&&(1)){
					buff[buff_position] = '\0';
					sscanf(buff,"%f",&(*(MW+cmplx_position)).real);
				}
				real_fill = 0;
				image_fill = 0;
				buff_position = 0;
				cmplx_position++;
			}else if(c == '-'){
				if((1)&&(1)&&(buff_position == 0)){
					buff[buff_position] = c;
					buff_position++;
				}else if((1)&&(1)&&(buff_position >= 1)){
					buff[buff_position] = '\0';
					sscanf(buff,"%f",&(*(MW+cmplx_position)).real);
					real_fill = 1;
					buff[0] = c;
					buff_position = 1;
				}
			}else if(c == '+'){
				if((1)&&(1)&&(buff_position == 0)){
					buff[buff_position] = c;
					buff_position++;
				}else if((1)&&(1)&&(buff_position >= 1)){
					buff[buff_position] = '\0';
					sscanf(buff,"%f",&(*(MW+cmplx_position)).real);
					real_fill = 1;
					buff[0] = c;
					buff_position = 1;
				}
			}else if(c == 'i'){
				if((1)&&(1)&&(buff_position == 0)){
					(*(MW+cmplx_position)).image = 1;
					image_fill = 1;
					buff_position = 0;
				}else if((1)&&(1)&&(buff_position == 1)&&(buff[0] == '+')){
					(*(MW+cmplx_position)).image = 1;
					image_fill = 1;
					buff_position = 0;
				}else if((1)&&(1)&&(buff_position == 1)&&(buff[0] == '-')){
					(*(MW+cmplx_position)).image = -1;
					image_fill = 1;
					buff_position = 0;
				}else{
					buff[buff_position] = '\0';
					sscanf(buff,"%f",&(*(MW+cmplx_position)).image);
					image_fill = 1;
					buff_position = 0;
				}
			}else if(c == 'I'){
				if((1)&&(1)&&(buff_position == 0)){
					(*(MW+cmplx_position)).image = 1;
					image_fill = 1;
					buff_position = 0;
				}else if((1)&&(1)&&(buff_position == 1)&&(buff[0] == '+')){
					(*(MW+cmplx_position)).image = 1;
					image_fill = 1;
					buff_position = 0;
				}else if((1)&&(1)&&(buff_position == 1)&&(buff[0] == '-')){
					(*(MW+cmplx_position)).image = -1;
					image_fill = 1;
					buff_position = 0;
				}else{
					buff[buff_position] = '\0';
					sscanf(buff,"%f",&(*(MW+cmplx_position)).image);
					image_fill = 1;
					buff_position = 0;
				}
			}else if((((int)c >= 48)&&((int)c <= 57))||(c == '.')){
				buff[buff_position] = c;
				buff_position++;
			}
		}

	}
	if(buff_position >= 1){
		buff[buff_position] = '\0';
		sscanf(buff,"%f",&(*(MW+cmplx_position)).real);
	}
	cmplx_position++;
	return(cmplx_position);
}

long int conjugate_complex_vec(struct cmplx *base, long int base_len, int conj_direction, struct cmplx *addition, long int addition_len, int fill_direction){
	long int length_BASE = 0;
	int i = 0;
	length_BASE = base_len + addition_len;
	if((base = realloc(base,base_len + addition_len)) == NULL){
		fprintf(stderr,"[E] failed realloc() in conjugate_complex_vec.\n");
		exit(1);
	}
	if((conj_direction == 1)&&(fill_direction == 1)){
		for(i=0;i<addition_len;i++){
			base[base_len+i] = addition[i];
		}
	}else if((conj_direction == 1)&&(fill_direction == -1)){
		for(i=0;i<addition_len;i++){
			base[base_len+i] = addition[addition_len-1-i];
		}
	}else if((conj_direction == -1)&&(fill_direction == 1)){
		for(i=0;i<=base_len;i++){
			base[base_len+addition_len-i] = base[base_len-i];
		}
		for(i=0;i<addition_len;i++){
			base[i] = addition[i];
		}
	}else if((conj_direction == -1)&&(fill_direction == -1)){
		for(i=0;i<=base_len;i++){
			base[base_len+addition_len-i] = base[base_len-i];
		}
		for(i=0;i<addition_len;i++){
			base[i] = addition[addition_len-1-i];
		}
	}
	return(length_BASE);
}

struct cmplx *conjugate_new_complex_vec(struct cmplx *base, long int base_len, int conj_direction, struct cmplx *addition, long int addition_len, int fill_direction){
	struct cmplx *exbase = NULL;
	long int length_exbase = 0;
	int i = 0;
	length_exbase = base_len + addition_len;
	exbase = calloc_cmplx_vec(exbase,length_exbase);
	if((conj_direction == 1)&&(fill_direction == 1)){
		for(i=0;i<base_len;i++){
			exbase[i] = base[i];
		}
		for(i=0;i<addition_len;i++){
			exbase[base_len+i] = addition[i];
		}
	}else if((conj_direction == 1)&&(fill_direction == -1)){
		for(i=0;i<base_len;i++){
			exbase[i] = base[i];
		}
		for(i=0;i<addition_len;i++){
			exbase[base_len+i] = addition[addition_len-1-i];
		}
	}else if((conj_direction == -1)&&(fill_direction == 1)){
		for(i=0;i<=base_len;i++){
			exbase[base_len+addition_len-i] = base[base_len-i];
		}
		for(i=0;i<addition_len;i++){
			exbase[i] = addition[i];
		}
	}else if((conj_direction == -1)&&(fill_direction == -1)){
		for(i=0;i<=base_len;i++){
			exbase[base_len+addition_len-i] = base[base_len-i];
		}
		for(i=0;i<addition_len;i++){
			exbase[i] = addition[addition_len-1-i];
		}
	}
	return(exbase);
}

struct cmplx *convolve_complex_vec(struct cmplx *base, long int base_len, struct cmplx *mw, long int mw_len, char *method, int step, int direct_print){
	struct cmplx *conv = NULL;
	int conv_len = base_len - mw_len + 1;
	/*int base_position = 0;*/
	int i = 0;
	int j = 0;
	if((direct_print == 1)&&(1)){
		struct cmplx out;
		struct cmplx tmp;
		out.real = 0;
		out.image = 0;
		tmp.real = 0;
		tmp.image = 0;
		printf(BRK_S);
		while(i < conv_len-1){
			for(j=0;j<mw_len;j++){
				tmp = times_cmplx(base[i+j],mw[j]);
				out.real += tmp.real;
				out.image += tmp.image;
			}
			printf("%f + %f I,\n",out.real,out.image);
			out.real = 0;
			out.image = 0;
			i += step;
		}
		for(j=0;j<mw_len;j++){
			tmp = times_cmplx(base[conv_len-1+j],mw[j]);
			out.real += tmp.real;
			out.image += tmp.image;
		}
		printf("%f + %f I",out.real,out.image);
		out.real = 0;
		out.image = 0;
		i += step;
		printf(BRK_E);
		printf("\n");

	}else{
		conv = calloc_cmplx_vec(conv, conv_len);
	}
	return(conv);
}
