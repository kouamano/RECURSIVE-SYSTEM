//structure
//// Conj-table
struct LinkTable {
	// global
	int offset_SN;
	int SN;
	// each node
	int *parent_SN;
	char **Head;
	int *Lv;
	int *Conj;
	int *LinkVC;
	int **LinkV;
};

