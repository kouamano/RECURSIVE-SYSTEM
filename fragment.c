#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define STR_LEN 1024
/* fragment.c */

struct option {
	char file[STR_LEN];
	int total_size;
	int segment_size;
	int gap_size;
	int offset;
	int fasta;
	int space;	/*0: ignore, 1: print*/
	int check;
	int help;
	int header;
	int count_start;
	char head[STR_LEN];
	char format[STR_LEN];
};

void init_option(struct option *opt){
	opt->file[0] = '\0';
	opt->total_size = 350000000;
	opt->segment_size = 1000;
	opt->gap_size = 24;
	opt->offset = 0;
	opt->fasta = 1;
	opt->space = 0;
	opt->check = 0;
	opt->help = 0;
	opt->header = 1;
	opt->head[0] = '\0';
	opt->count_start = 0;
	sscanf("%012d","%s",opt->format);
}

void get_option(int optc, char **optv, struct option *opt){
	int i;
	for(i=0;i<optc;i++){
		if(strcmp(optv[i],"--help") == 0){
			opt->help = 1;
		}else if(strcmp(optv[i],"-h") == 0){
			opt->help = 1;
		}else if(strcmp(optv[i], "-c") == 0){
			opt->check = 1;
		}else if(strcmp(optv[i],"-s") == 0){
			opt->space = 0;
		}else if(strcmp(optv[i],"+s") == 0){
			opt->space = 1;
		}else if(strcmp(optv[i],"-f") == 0){
			opt->fasta = 1;
		}else if(strcmp(optv[i],"+f") == 0){
			opt->fasta = 0;
		}else if(strcmp(optv[i],"-H") == 0){
			opt->header = 1;
		}else if(strcmp(optv[i],"+H") == 0){
			opt->header = 0;
		}else if(strncmp(optv[i],"O=",2) == 0){
			sscanf(optv[i],"O=%d",&opt->offset);
		}else if(strncmp(optv[i],"G=",2) == 0){
			sscanf(optv[i],"G=%d",&opt->gap_size);
		}else if(strncmp(optv[i],"S=",2) == 0){
			sscanf(optv[i],"S=%d",&opt->segment_size);
		}else if(strncmp(optv[i],"L=",2) == 0){
			sscanf(optv[i],"L=%d",&opt->total_size);
		}else if(strncmp(optv[i],"bf=",3) == 0){
			sscanf(optv[i],"bf=%s",opt->file);
		}else if(strncmp(optv[i],"cs=",3) == 0){
			sscanf(optv[i],"cs=%d",&opt->count_start);
		}else if(strncmp(optv[i],"H=",2) == 0){
			sscanf(optv[i],"H=%s",opt->head);
		}else if(strncmp(optv[i],"F=",2) == 0){
			sscanf(optv[i],"F=%s",opt->format);
		}else{
			printf("unknown option: %s",optv[i]);
		}
	}
}

void print_option(struct option opt){
	printf("Settings:\n");
	printf("  print space    :%d:\n",opt.space);
	printf("  use FASTA      :%d:\n",opt.fasta);
	printf("  offset         :%d:\n",opt.offset);
	printf("  gap size       :%d:\n",opt.gap_size);
	printf("  segment size   :%d:\n",opt.segment_size);
	printf("  total length   :%d:\n",opt.total_size);
	printf("  file           :%s:\n",opt.file);
	printf("  header         :%d:\n",opt.header);
	printf("  head           :%s:\n",opt.head);
	printf("  count start    :%d:\n",opt.count_start);
	printf("  format         :%s:\n",opt.format);
}

void help(void){
	printf("Usage:\n");
	printf("  fragment bf=<file> L=<data length> S=<segment size> G=<gap size> O=<offset> H=<head> F=<format> cs=<count start> [-H|+H] [-c] [-s|+s] [-f|+f] [-h]\n");
	printf("Options:\n");
	printf("  --help|-h  :help\n");
	printf("  -c         :options check\n");
	printf("  -s         :print space\n");
	printf("  +s         :ignore space\n");
	printf("  -f         :FASTA format\n");
	printf("  +f         :plain sequence\n");
	printf("  -H         :with header\n");
	printf("  +H         :without header\n");
}

void print_lensize(char *sequence){
	int len;
	len = strlen(sequence);
	printf("%d\n",len);
}

void print_frg(int s_size, int g_size, int offset, char *sequence){
	int i,j,len;
	len = strlen(sequence);
	for(j=0+offset;j<=len-s_size;j=j+g_size){
		for(i=j;i<j+s_size;i++){
			printf("%c",sequence[i]);
		}
		printf("\n");
	}
}

void print_frg_h(int s_size, int g_size, int offset, char *sequence, char *head, int start, char *format){
	int i,j,count,len;
	count = 0;
	len = strlen(sequence);
	for(j=0+offset;j<=len-s_size;j=j+g_size){
		printf("%s",head);
		printf(format,count+start);
		count++;
		printf("\n");
		for(i=j;i<j+s_size;i++){
			printf("%c",sequence[i]);
		}
		printf("\n");
	}
}

int main(int argc, char **argv){
	struct option opt;
	FILE *IN;
	char *str;
	char cc;
	int len = 0;
	/* (* option setting */
	init_option(&opt);
	get_option(argc-1, argv+1, &opt);
	if(opt.help == 1){
		help();
	}
	if(opt.check == 1){
		print_option(opt);
	}
	if((opt.help == 1)||(opt.check == 1)||(strlen(opt.file) < 1)){
		exit(0);
	}
	/* *) */
	/* (* allocation */
	if((str = malloc(sizeof(char) * opt.total_size)) == NULL){
		fprintf(stderr,"failed: malloc() -- exit.\n");
		exit(1);
	}
	/* *) */
	IN = fopen(opt.file,"r");
	if(opt.fasta == 1){
		cc = getc(IN);
		if(cc == '>'){
			while((cc = getc(IN)) != '\n'){
			}
		}else{
			fprintf(stderr,"not FASTA format.\n");
			*(str+len) = cc;
			len++;
		}
	}
	if(opt.space == 0){
		while((cc = getc(IN)) != EOF){
			if((cc != '\n')&&(cc != ' ')&&(cc != '\t')){
				*(str+len) = cc;
				len++;
			}
		}
	}else if(opt.space == 1){
		while((cc = getc(IN)) != EOF){
				*(str+len) = cc;
				len++;
		}
	}
	fclose(IN);
	if(opt.header == 0){
		print_frg(opt.segment_size, opt.gap_size, opt.offset, str);
	}else if(opt.header == 1){
		print_frg_h(opt.segment_size, opt.gap_size, opt.offset, str, opt.head, opt.count_start, opt.format);
	}
	return(0);
}
