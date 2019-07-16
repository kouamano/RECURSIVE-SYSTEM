/* countfrgs */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){

char st[8192];
char old[8192];
int count = 1;

sprintf(old,"%s","\0");
while((scanf("%s",st)) != EOF){
	if(strcmp(st,old) == 0){
		count++;
	}else{
		printf("%s ",old);
		printf("%d\n",count);
		count = 1;
	}
	sprintf(old,"%s",st);
}
printf("%s ",old);
printf("%d\n",count);
return(0);

} // main
