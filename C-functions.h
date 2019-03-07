int Alloc_Link_V(struct LinkTable *LT, struct LinkHead *LH){
	/* alloc LinkTable */
	(*LT).LinkVC = realloc((*LT).LinkVC, sizeof(*(*LT).LinkVC) * ((*LT).SN + 1));
	if((*LT).LinkVC == NULL){
		perror("[Fail]:realloc@Add_Link_V.\n");
		exit(1);
	}
	(*LT).LinkV = realloc((*LT).LinkV, sizeof(*(*LT).LinkV) * ((*LT).SN + 1));
	if((*LT).LinkV == NULL){
		perror("[Fail]:realloc@Add_Link_V.\n");
		exit(1);
	}
	(*LT).LinkV[(*LT).SN] = NULL;

	/* alloc Head */
	(*LH).Head = realloc((*LH).Head, sizeof(*(*LH).Head) * ((*LT).SN + 1));
	if((*LH).Head == NULL){
		perror("[Fail]:realloc@Alloc_Link_V.^\n");
		exit(1);
	}
	(*LH).Lv = realloc((*LH).Lv, sizeof(*(*LH).Lv) * ((*LT).SN + 1));
	if((*LH).Lv == NULL){
		perror("[Fail]:realloc@Alloc_Link_V.^\n");
		exit(1);
	}
	(*LH).Conj = realloc((*LH).Conj, sizeof(*(*LH).Conj) * ((*LT).SN + 1));
	if((*LH).Conj == NULL){
		perror("[Fail]:realloc@Alloc_Link_V.^\n");
		exit(1);
	}

	return(0);
}

int Add_Link_V(struct LinkTable *LT, struct LinkHead *LH){
	/* alloc LinkTable */
	(*LT).LinkVC = realloc((*LT).LinkVC, sizeof(*(*LT).LinkVC) * ((*LT).SN + 2));
	if((*LT).LinkVC == NULL){
		perror("[Fail]:realloc@Add_Link_V.\n");
		exit(1);
	}
	(*LT).LinkV = realloc((*LT).LinkV, sizeof(*(*LT).LinkV) * ((*LT).SN + 2));
	if((*LT).LinkV == NULL){
		perror("[Fail]:realloc@Add_Link_V.\n");
		exit(1);
	}
	(*LT).LinkV[(*LT).SN] = NULL;

	/* alloc Head */
	(*LH).Head = realloc((*LH).Head, sizeof(*(*LH).Head) * ((*LT).SN + 2));
	if((*LH).Head == NULL){
		perror("[Fail]:realloc@Alloc_Link_V.^\n");
		exit(1);
	}
	(*LH).Lv = realloc((*LH).Lv, sizeof(*(*LH).Lv) * ((*LT).SN + 2));
	if((*LH).Lv == NULL){
		perror("[Fail]:realloc@Alloc_Link_V.^\n");
		exit(1);
	}
	(*LH).Conj = realloc((*LH).Conj, sizeof(*(*LH).Conj) * ((*LT).SN + 2));
	if((*LH).Conj == NULL){
		perror("[Fail]:realloc@Alloc_Link_V.^\n");
		exit(1);
	}

	(*LT).SN++;

	return(0);
}

int Create_Link(struct LinkTable *LT, struct LinkHead *LH){
	int stat;
	LT = malloc(sizeof(struct LinkTable) * 1);
	if(LT == NULL){
		perror("[Fail]:malloc@Create_Link.\n");
		exit(1);
	}
	(*LT).startSN = 0;
	(*LT).SN = 0;
	(*LT).LinkVC = NULL;
	(*LT).LinkV = NULL;

	LH = malloc(sizeof(struct LinkHead) * 1);
	if(LH == NULL){
		perror("[Fail]:malloc@Create_Link.\n");
		exit(1);
	}
	(*LH).Head = NULL;
	(*LH).Lv = NULL;
	(*LH).Conj = NULL;

	stat = Alloc_Link_V(LT,LH);
	return(stat);
}


int Add_Link_Memb(struct LinkTable *LT, struct LinkHead *LH, int parent_SN, int _SN){
	(*LT).LinkVC[parent_SN]++;
	(*LT).LinkV[parent_SN] = realloc((*LT).LinkV[parent_SN], sizeof(**(*LT).LinkV) * (*LT).LinkVC[_SN] );
	(*LT).LinkV[parent_SN][(*LT).LinkVC[parent_SN]] = _SN;
	return(0);
}
