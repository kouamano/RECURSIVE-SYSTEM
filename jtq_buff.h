char *alloc_BUFF(int size){
	char *p;
	if((p = malloc(sizeof(char) * (size+1))) == NULL){
		perror("alloc buff");
		exit(1);
	}
	return p;
}
