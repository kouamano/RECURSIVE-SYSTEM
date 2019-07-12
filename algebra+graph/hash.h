struct similarity_hash{
	int node_s;
	int node_e;
	float sim;
};

struct similarity_hash *f_alloc_similarity_hash(int num, struct similarity_hash *sim_hash){
	if((sim_hash = malloc(sizeof(struct similarity_hash)*num)) == NULL){
		fprintf(stderr,"[E] failed malloc().\n");
		exit(1);
	}
	return(sim_hash);
}

int read_simmilarity_hash_from_stream(int num, FILE *IN, struct similarity_hash *sim_hash){
	int i = 0;
	char line[TMP_STR_LEN_LONG];
	while(line,TMP_STR_LEN_LONG,IN){
		sscanf(line,"%d %d %f",&(*(sim_hash+i)).node_s,&(*(sim_hash+i)).node_e,&(*(sim_hash+i)).sim);
		i++;
	}
	return(i);
}
