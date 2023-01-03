struct Nd *alloc_Nd_arr(int size){
        struct Nd *p;
        if((p = malloc(sizeof(struct Nd) * size)) == NULL){
                perror("alloc_Nd_arr()\n");
                exit(1);
        }
        return(p);
}
void set_Nd(struct options *opt, struct Nd *node, int idx, int CjT, int NdT, int Lv, int Pa, char *buff){
        //buff
        int len = 0;
        len = strlen(buff);
        node[idx].head = alloc_BUFF(len + 1);
	if(node[idx].head == NULL){
		perror("alloc:head");
		exit(1);
	}
        strcpy(node[idx].head,buff);
        //Lv
	node[idx].Lv = Lv;
	//Pa
	node[idx].Pa = Pa;
}
void print_NdStat(struct options *opt, struct Nd *node, int idx){
}
