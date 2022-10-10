/* Block type
 1	Node
 2	open tag
 4	close tag
 8	independent tag
 16	body
*/

struct Block {
	int ser;
	int Lv;
	int Bltype;
	int parent;
	char *str;
	int *next_Bl;
};

int set_Block_type(struct Block *Bl, int target_Bl, int type){
	return(0);
}

int create_top_Nd(struct Block *Bl){
	Bl[0].ser = 0;
	Bl[0].Lv = 0;
	return(0);
}
