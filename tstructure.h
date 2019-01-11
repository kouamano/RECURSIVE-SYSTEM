//structure
struct Tree {
	int LVself;
	int NCself;
	int Conj;
	int Bopen;
	char *Head;
	int Bclose;
	int NextCount;
	struct Tree **Next;
	struct Tree *Parent;
};

