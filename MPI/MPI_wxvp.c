#include <stdio.h>
#include <string.h>
#include <mpi.h>

int main(int argc, char **argv){
        int my_rank;
        int np;
        int source;
        int dest;
        int tag = 0;
        char message[100];
	FILE *IN;

        //printf("arg:%s:\n",argv[1]);
        IN = fopen(argv[1],"r");
	close(IN);

        MPI_Status status;
        MPI_Init(&argc, &argv);
        MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
        MPI_Comm_size(MPI_COMM_WORLD, &np);

        printf("rank:%d: np:%d: W:%d:\n",my_rank,np,MPI_COMM_WORLD);
        //printf("nproc:%d:\n",np);
        //printf("WORLD:%d:\n",MPI_COMM_WORLD);

        MPI_Finalize();

}

