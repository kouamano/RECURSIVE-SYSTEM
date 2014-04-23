int strncmpi(const char *s1, const char *s2, size_t n){
	int i;
	for(i=0;i<n;i++){
		if(toupper(s1[i]) < toupper(s2[i])){
			return(-1);
		}else if(toupper(s1[i]) > toupper(s2[i])){
			return(1);
		}else{
			;
		}
	}
	return(0);
}
