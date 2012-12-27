/* htclient.c */
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
#define STR_LEN 1024
#define LONG_STR_LEN 4096

struct argop {
	char method[STR_LEN];
	char host[STR_LEN];
	char path[LONG_STR_LEN];
	char cookie[LONG_STR_LEN];
	int port;
};

void print_help(void){
	printf("USAGE : \n");
	printf("  htclient host=\"host\" path=\"path\" [cookie=\"cookie\"] [port=\"port\"]\n");
}

void init_options(struct argop *option){
	sscanf("GET","%s",option->method);
	option->host[0] = '\0';
	option->path[0] = '\0';
	option->cookie[0] = '\0';
	option->port = 80;
}

int get_options(int arg_start, int arg_end, char **arg_s, struct argop *option){
	int i = 0;
	int s = 0;
		for(i=arg_start;i<arg_end;i++){
			if(strcmp(arg_s[i],"-h") == 0){
				print_help();
				exit(0);
			}else if(strncmp(arg_s[i],"host=",5) == 0){
				sscanf(arg_s[i],"host=%s",option->host);
				if((s&4) == 0){
					s = s + 4;
				}
			}else if(strncmp(arg_s[i],"path=",5) == 0){
				sscanf(arg_s[i],"path=%s",option->path);
				if((s&8) == 0){
					s = s + 8;
				}
			}else if(strncmp(arg_s[i],"port=",5) == 0){
				sscanf(arg_s[i],"port=%d",&option->port);
				if((s&16) == 0){
					s = s + 16;
				}
			}else if(strncmp(arg_s[i],"method=",7) == 0){
				sscanf(arg_s[i],"method=%s",option->method);
				if((s&32) == 0){
					s = s + 32;
				}
			}else if(strncmp(arg_s[i],"cookie=",7) == 0){
				sscanf(arg_s[i],"cookie=%s",option->cookie);
				if((s&64) == 0){
					s = s + 64;
				}
			}else{
				printf("Unknown optios.\n");
				exit(0);
			}
		}
	return(s);
}

int main(int argc, char *argv[]){
	struct argop options;
	int s = -1;
	struct hostent *serverhost = NULL;
	struct sockaddr_in server;
	char send_buf[BUF_LEN];
	char get_buf[BUF_LEN];
	char hostname[STR_LEN];
	char path[LONG_STR_LEN];
	/*char URL[LONG_STR_LEN];*/
	int port = 0;
	int read_size = 0;
	int opt_stat = 0;
	init_options(&options);
	if(argc == 1){
		print_help();
		exit(0);
	}else if(argc >= 2){
		opt_stat = get_options(1,argc,argv,&options);
		strcpy(hostname,options.host);
		strcpy(path,options.path);
		port = options.port;
		if((serverhost = gethostbyname(hostname)) == NULL){
			printf("failed : gethostbyname().\n");
			exit(1);
		}
		bzero((char *)&server,sizeof(server));
		server.sin_family = AF_INET;
		bcopy(serverhost->h_addr,(char *)&server.sin_addr,serverhost->h_length);
		server.sin_port = htons(port);
		if((s = socket(AF_INET,SOCK_STREAM,0)) < 0){
			printf("failed : socket().\n");
			exit(1);
		}
		if(connect(s,(struct sockaddr *)&server,sizeof(server)) == -1){
			printf("failed : connect.\n");
			exit(1);
		}
		sprintf(send_buf,"%s %s HTTP/1.0\r\n",options.method,path);
		write(s,send_buf,strlen(send_buf));
		sprintf(send_buf,"HOST: %s:%d\r\n",hostname,port);
		write(s,send_buf,strlen(send_buf));
		if((opt_stat & 64) == 64){
			sprintf(send_buf,"Cookie: %s\r\n",options.cookie);
			write(s,send_buf,strlen(send_buf));
		}
		sprintf(send_buf,"\r\n");
		write(s,send_buf,strlen(send_buf));
		while(1){
			read_size = read(s,get_buf,BUF_LEN);
			if(read_size > 0){
				write(1,get_buf,read_size);
			}else{
				break;
			}
		}
		close(s);
	}
	return(0);
}
