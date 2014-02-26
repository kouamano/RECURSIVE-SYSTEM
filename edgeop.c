/* d_route.egdeop.c */
int if_match_int_sc_vec(int sc, int *vec, int len){
	int i;
	int count = 0;
	//printf("  sc:%d:\n",sc);
	for(i=0;i<len;i++){
		if(vec[i] == sc){count++;}
	}
	return(count);
}
