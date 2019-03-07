//structure
//// Conj-table
struct LinkTable {
	// global
	int startSN;
	int SN;
	// each node
	char **Head;
	int *Lv;
	int *Conj;
	int *LinkVC;
	int **LinkV;
	int *parent_SN;
};

