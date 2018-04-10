/* edgeop.h */
struct edge {
	int *p;
	int *t;
};

struct edge_d {
	int *p;
	int *t;
	float *d;
};

struct edge_table{ /* node ID = position */
	int *size;
	int **next_pos;
	int **next_pos_used;
};
