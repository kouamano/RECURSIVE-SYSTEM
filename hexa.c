#include <stdio.h>

int main(){
	int i[6];
	int j;
	for(i[0]=0;i[0]<4;i[0]++){
	for(i[1]=0;i[1]<4;i[1]++){
	for(i[2]=0;i[2]<4;i[2]++){
	for(i[3]=0;i[3]<4;i[3]++){
	for(i[4]=0;i[4]<4;i[4]++){
	for(i[5]=0;i[5]<4;i[5]++){
				for(j=0;j<6;j++){
					if(i[j] == 0){
						printf("A");
					}else if(i[j] == 1){
						printf("G");
					}else if(i[j] == 2){
						printf("T");
					}else if(i[j] == 3){
						printf("C");
					}
				}
				printf("\n");
	}
	}
	}
	}
	}
	}
}
