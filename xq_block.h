/* Block type */
int BType_Node = 1;
int BType_sTag = 2;
int BType_eTag = 4;
int BType_iTag = 8;
int BType_Body = 16;

/* structure */
struct Block {
	int ser;
	int Lv;
	int Bltype;
	int parent;
	char *str;
	int *next_Bl;
};

struct Block *alloc_Block(int size){
	struct Block *p;
	if((p = malloc(sizeof(struct Block) * size)) == NULL){
		perror("alloc_Block()\n");
		exit(1);
	}
	return(p);
}

int set_Block_type(struct Block *Bl, int target_Bl, int type){
	int rt = 0;
	if(((Bl[target_Bl].Bltype)&type) != type){
		Bl[target_Bl].Bltype += type;
		rt = type;
	}
	return(rt);
}

int create_top_Nd(struct Block *Bl){
	Bl[0].ser = 0;
	Bl[0].Lv = 0;
	return(0);
}
