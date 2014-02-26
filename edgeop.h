/* edgeop.h */
struct edge {
	int *p;
	int *t;
};

struct RNG_table{ /* node ID = position */
	int *size;
	int **next_pos;
	int *used;
};
