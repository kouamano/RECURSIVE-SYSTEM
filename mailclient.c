/* mailclient.c */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/param.h>
#include <sys/uio.h>
#include <sys/stat.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#define BUF_LEN 1024
#define LOWER_SIZE 1024
#define UP_SIZE 1600

struct argop {
	char inputfile[2048];
	char sender[1024];
	char rcpt[1024];
	char server[1024];
	char subj[1024];
};

void print_help(void){
	printf("  Usage:\n");
	printf("  mailclient [if=\"input file\"] sender=\"sender\" rcpt=\"recipient\" server=\"smtp server\" subj=\"subject\"\n");
}

int get_options(int arg_start, int arg_end, char **arg_s, struct argop *option){
	int i = 0;
	int s = 0;
		for(i=arg_start;i<arg_end;i++){
			if(strcmp(arg_s[i],"-h") == 0){
				print_help();
				exit(0);
			}else if(strncmp(arg_s[i],"if=",3) == 0){
				sscanf(arg_s[i],"if=%s",option->inputfile);
				if((s&2) == 0){
					s = s + 2;
				}
			}else if(strncmp(arg_s[i],"sender=",7) == 0){
				sscanf(arg_s[i],"sender=%s",option->sender);
				if((s&4) == 0){
					s = s + 4;
				}
			}else if(strncmp(arg_s[i],"rcpt=",5) == 0){
				sscanf(arg_s[i],"rcpt=%s",option->rcpt);
				if((s&8) == 0){
					s = s + 8;
				}
			}else if(strncmp(arg_s[i],"server=",7) == 0){
				sscanf(arg_s[i],"server=%s",option->server);
				if((s&16) == 0){
					s = s + 16;
				}
			}else if(strncmp(arg_s[i],"subj=",5) == 0){
				sscanf(arg_s[i],"subj=%s",option->subj);
				if((s&32) == 0){
					s = s + 32;
				}
			}else{
				printf("Unknown option.\n");
				exit(0);
			}
		}
	return(s);
}

int main(int argc, char *argv[]){
	struct argop opt;
	FILE *inputfile;
	int op_stat = 0;
	int s;
	char mypc[] = "localhost";
	struct hostent *servhost;
	struct sockaddr_in server;
	struct stat file_st;
	char *content;
	int i = 0;
	char c;
	int mem_size = 0;
	char send_buf[BUF_LEN];
	op_stat = get_options(1,argc,argv,&opt);
	printf("inputfile:%s:\n",opt.inputfile);
	printf("sender:%s:\n",opt.sender);
	printf("rcpt:%s:\n",opt.rcpt);
	printf("server:%s:\n",opt.server);
	if(strlen(opt.inputfile) == 0){
		content = malloc(sizeof(char)*LOWER_SIZE);
		mem_size += LOWER_SIZE;
		while(scanf("%c",&c) != EOF){
			content[i] = c;	
			i++;
			if((mem_size - strlen(content)) < 16){
				content = realloc(content,strlen(content)+UP_SIZE);
				mem_size = strlen(content)+UP_SIZE;
			}
		}
		content[i] = '\0';
	}else{
		stat(opt.inputfile,&file_st);
		content = malloc(sizeof(char)*(file_st.st_size+4));
		if((inputfile = fopen(opt.inputfile,"r")) == NULL){
			printf("fopen error.\n");
			exit(0);
		}
		while((c = fgetc(inputfile)) != EOF){
			content[i] = c;	
			i++;
		}
		content[i] = '\0';
		fclose(inputfile);
	}
	servhost = gethostbyname(opt.server);
	if(servhost == NULL){
		fprintf(stderr,"bind error.\n");
		return 0;
	}
	bzero((char *)&server,sizeof(server));
	server.sin_family = AF_INET;
	bcopy(servhost->h_addr,(char *)&server.sin_addr,servhost->h_length);
	server.sin_port = htons(25);
	if((s = socket(AF_INET,SOCK_STREAM,0)) < 0){
		fprintf(stderr,"socket error.\n");
		return 1;
	}
	if(connect(s,(struct sockaddr *)&server,sizeof(server)) == -1){
		fprintf(stderr,"connect error.\n");
		return 1;
	}
	sprintf(send_buf,"helo %s\n",mypc);
	write(s,send_buf,strlen(send_buf));
	sprintf(send_buf,"mail from: %s\n",opt.sender);
	write(s,send_buf,strlen(send_buf));
	sprintf(send_buf,"rcpt to: %s\n",opt.rcpt);
	write(s,send_buf,strlen(send_buf));
	sprintf(send_buf,"data\n");
	write(s,send_buf,strlen(send_buf));
	if((op_stat&32) == 32){
		sprintf(send_buf,"Subject: %s\n",opt.subj);
		write(s,send_buf,strlen(send_buf));
	}
	write(s,content,strlen(content));
	sprintf(send_buf,"\n.\n");
	write(s,send_buf,strlen(send_buf));
	sprintf(send_buf,"quit\n");
	write(s,send_buf,strlen(send_buf));
	while(1){
		char buf[BUF_LEN];
		int read_size;
		read_size = read(s,buf,BUF_LEN);
		if(read_size > 0){
			write(1,buf,read_size);
		}else{
			break;
		}
	}
	close(s);
	return 0;
}
