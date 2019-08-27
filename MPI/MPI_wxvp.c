#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

#define MSG_SIZ 1000
#define FNAME_SIZ 1000

int main(int argc, char **argv){
        int my_rank;
        int np;
        int source;
        int dest;
        int tag = 0;
	FILE *IN;
        char *message = NULL;
        char *filename = NULL;
	char **commlist = NULL;
	int C;
	int LFcount = 0;
	int i;
	int j;

	if((message = malloc(sizeof(char) * MSG_SIZ)) == NULL){
		perror("[F]malloc@message");
		exit(1);
	}
	if((filename = malloc(sizeof(char) * FNAME_SIZ)) == NULL){
		perror("[F]malloc@message");
		exit(1);
	}

        //printf("arg:%s:\n",argv[1]);
        LFcount = 0;
	IN = fopen(argv[1],"r");
	while(C = fgetc(IN)){
		if(C == '\n'){
			LFcount++;
		}
	}
	LFcount++;
	//fseek(IN,0,SEEK_SET);
	close(IN);
	if((commlist = malloc(sizeof(char *) * LFcount)) == NULL){
		perror("[F]malloc@commlist");
		exit(1);
	}
	if((commlist[0] = malloc((sizeof(char) * MSG_SIZ * LFcount))) == NULL){
		perror("[F]malloc@commlist");
		exit(1);
	}
	for(i=1;i<LFcount;i++){
		commlist[i] = commlist[i+1]+MSG_SIZ;
	}
	IN = fopen(argv[1],"r");
	i = 0;
	j = 0;
	while(C = fgetc(IN)){
		if(C == '\n'){
			j++;
			commlist[i][j] = '\0';
			j = 0;
			i++;
		}else if(C == EOF){
			j++;
			commlist[i][j] = '\0';
			break;
		}else{
			commlist[i][j] = C;
			j++;
		}
	}


        MPI_Status status;
        MPI_Init(&argc, &argv);
        MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
        MPI_Comm_size(MPI_COMM_WORLD, &np);

        printf("rank:%d: np:%d: W:%d:com:%s:\n",my_rank,np,MPI_COMM_WORLD,commlist[my_rank%LFcount]);
        //printf("nproc:%d:\n",np);
        //printf("WORLD:%d:\n",MPI_COMM_WORLD);

        MPI_Finalize();

}

