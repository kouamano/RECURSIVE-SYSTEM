//structure
struct List {
	int ID;
	int LVself;
	int NCself;
	int ACself;
	int Val;
	char *Head;
	struct List *(*function)();
	int NextCount;
	struct List **Next;
	int ArgCount;
	struct List **Arg;
	struct List *Parent;
};

