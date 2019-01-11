//structure
struct GraphV {
	int LVself;
	int NCself;
	int PCself;
	int NConj;
	int PConj;
	int Bopen;
	char *Head;
	int Bclose;
	int NextCount;
	struct GraphV **Next;
	int ParentCount;
	struct GraphV **Parent;
};

