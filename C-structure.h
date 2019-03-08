//structure
//// Conj-table
struct LinkTable {
	// global
	int offset_SN;
	int SN;
	// each node
	int *parent_SN;
	int *Lv;
	char **Head;
	int *Conj;
	int *LinkVC;
	int **LinkV;
};

