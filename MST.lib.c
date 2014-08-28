#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN 1024
#include "../include/alloc.c"
#include "../include/data_read.c"
#include "../include/math_base.c"

struct path{
	int head_node;
	int tail_node;
	float dist;
};

int select_posUnflagedV(int *vpool, int size, int pos){
	int i;
	int count = -1;
	for(i=0;i<size;i++){
		if(vpool[i] == 1){
			count++;
			if(count == pos){
				return(i);
			}
		}
	}
	return(-1);
}

void moveVp2Vn(int *vpool, int *vnew, int id){
	vpool[id] = 0;
	vnew[id] = 1;
}

int poolremain(int *vpool, int size){
	int i;
	int count = 0;
	for(i=0;i<size;i++){
		if(vpool[i] == 1){
			count++;
		}
	}
	return(count);
}

float minimum_dist_from_Vnew(int *vnew, int size_vnew, int *vpool, int size_vpool, float **_dmat, int *vnpoint, int *vppoint){
	int i,j;
	float dist_min = -1;
	int pos_vn_min;
	int pos_vp_min;
	for(i=0;i<size_vnew;i++){
		for(j=0;j<size_vpool;j++){
			//printf("[i,j,vnew_i,vpool_i]:%d,%d,%d,%d:",i,j,vnew[i],vpool[j]);
			if(vnew[i] == 1 && vpool[j] == 1){
				//printf("\nHit[%d,%d,%f]\n",i,j,_dmat[i][j]);
				if(dist_min == -1){
					dist_min = _dmat[i][j];
					pos_vn_min = i;
					pos_vp_min = j;
				}else{
					if(dist_min > _dmat[i][j]){
						dist_min = _dmat[i][j];
						pos_vn_min = i;
						pos_vp_min = j;
					}else{
						;
					}
				}
			}
		}
	}
	*vnpoint = pos_vn_min;
	*vppoint = pos_vp_min;
	return(dist_min);
}

void myMST(int *opt_size, float **dmat, struct path *path_list){
	//float **dmat;
	//FILE *fp;
	int i,j;
	int *Vpool;
	int *Vnew;
	int Vppoint = -1;
	int Vnpoint = -1;
	int currentV = -1;
	float currentDist = -1;
	int R = -1;
	int *tmp_i;

	/* init Vpool */
	Vpool = i_alloc_vec(*opt_size);
	for(i=0;i<*opt_size;i++){
		Vpool[i] = 1;
	}
	/* init Vnew */
	Vnew = i_alloc_vec(*opt_size);
	for(i=0;i<*opt_size;i++){
		Vnew[i] = 0;
	}
	/* init path_list */
	if((path_list = malloc(sizeof(struct path) * (*opt_size))) == NULL){
		printf("failed: malloc() at path_list");
		exit(1);
	}
	

	/* initial select */
	currentV = select_posUnflagedV(Vpool,*opt_size,0);
	//printf("currentV:%d:\n",currentV);
	moveVp2Vn(Vpool, Vnew, currentV);
	/*
	for(i=0;i<(*opt).size;i++){
		printf("Vpool[%d]:%d:\n",i,Vpool[i]);
	}
	for(i=0;i<(*opt).size;i++){
		printf("Vnew[%d]:%d:\n",i,Vnew[i]);
	}
	*/

	/* while */
	i = 0;
	for(;;){
		//printf("path %d",currentV);
		/** find nimimum dist edge **/
		currentDist = minimum_dist_from_Vnew(Vnew, *opt_size, Vpool, *opt_size, dmat, &Vnpoint, &Vppoint);
		printf("%d\t%d\t%f\n",Vnpoint,Vppoint,currentDist);
		path_list[i].head_node = Vnpoint;
		path_list[i].tail_node = Vppoint;
		path_list[i].dist = currentDist;
		/** move Vp to Vn, switch currentV **/
		currentV = Vppoint;
		moveVp2Vn(Vpool, Vnew, currentV);
		/** check loop **/
		R = poolremain(Vpool,*opt_size);
		//printf("\nR:%d:\n",R);
		if(R <= 0){
			break;
		}
		i++;
	}
}
