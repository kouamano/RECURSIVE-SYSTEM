/* edgeop.h */
struct edge {
	int *p;
	int *t;
};

struct RNG_tbl{ /* node ID = position */
	int *size;
	int **next_pos;
	int *useed;
};
