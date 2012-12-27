int t_score(float **f, int size_f_t, int size_f_d, float *n){
	int t;
	int d;
	float *F;
	F = malloc(sizeof(float) * size_f_t);
	for(t=0;t<size_f_t;t++){
		for(d=0;d<size_f_d;d++){
			F[t] += f[d][t];
	 	}
	}
	for(t=0;t<size_f_t;t++){
		for(d=0;d<size_f_d;d++){
			n[t] += (-(f[d][t]/F[t]) * log(f[d][t]/F[t])/log(2));
		}
	}
	return(0);
}
