struct Nd *alloc_Nd_arr(int size){
        struct Nd *p;
        if((p = malloc(sizeof(struct Nd) * size)) == NULL){
                perror("alloc_Nd_arr()\n");
                exit(1);
        }
        return(p);
}

struct Nd *create_Nd(struct options *opt, struct Nd *node, int type, int lv, int pa, char *buff){
	return(node);
}

void set_Nd(struct options *opt, struct Nd *node, int CjT, int NdT, int Lv, int Pa, char *buff){
        //buff
        int len = 0;
        len = strlen(buff);
        (*node).head = alloc_BUFF(len + 1);
        strcpy((*node).head,buff);
        //other attribution
}
