int Function_Print_LinkTable(struct LinkTable *LT){
	int i,j;
	printf("Global.offset_SN:%d:\n",(*LT).offset_SN);
	printf("Global.SN:%d:\n",(*LT).SN);
	for(i=0;i<(*LT).SN;i++){
		printf("Each[%d].:H=%s:",i,(*LT).Head[i]);
		printf(":Pa=%d:",(*LT).parent_SN[i]);
		printf(":Lv=%d:",(*LT).Lv[i]);
		printf(":Cj=%d:",(*LT).Conj[i]);
		printf(":VC=%d:",(*LT).LinkVC[i]);
		printf(":V");
		for(j=0;j<(*LT).LinkVC[i];j++){
			printf(",%d",(*LT).LinkV[i][j]);
		}
		printf(":\n");
	}
	return(0);
}

int Free_LinkTable(struct LinkTable *LT, int _offset_SN){
	int i;
	for(i=0;i<(*LT).SN;i++){
		free((*LT).Head[i]);
		//free((*LT).parent_SN);
		//free((*LT).Lv);
		//free((*LT).Conj);
		//free((*LT).LinkVC);
		free((*LT).LinkV[i]);
	}

	free((*LT).parent_SN);
	free((*LT).Lv);
	free((*LT).Conj);
	free((*LT).LinkVC);
	free((*LT).Head);
	free((*LT).LinkV);

	(*LT).offset_SN = _offset_SN;
	(*LT).SN = 0;
	(*LT).parent_SN = NULL;
	(*LT).Lv = NULL;
	(*LT).Conj = NULL;
	(*LT).LinkVC = NULL;
	(*LT).Head = NULL;
	(*LT).LinkV = NULL;

	return(0);
}

struct LinkTable *Alloc_Link_V(struct LinkTable *LT){
	int size = (*LT).SN;
	(*LT).Head = realloc((*LT).Head, sizeof(*(*LT).Head) * (size + 1));
	if((*LT).Head == NULL){
		perror("[Fail]:realloc@Alloc_Link_V.^\n");
		exit(1);
	}
	(*LT).Lv = realloc((*LT).Lv, sizeof(*(*LT).Lv) * (size + 1));
	if((*LT).Lv == NULL){
		perror("[Fail]:realloc@Alloc_Link_V.^\n");
		exit(1);
	}
	(*LT).Conj = realloc((*LT).Conj, sizeof(*(*LT).Conj) * (size + 1));
	if((*LT).Conj == NULL){
		perror("[Fail]:realloc@Alloc_Link_V.^\n");
		exit(1);
	}

	(*LT).LinkVC = realloc((*LT).LinkVC, sizeof(*(*LT).LinkVC) * (size + 1));
	if((*LT).LinkVC == NULL){
		perror("[Fail]:realloc@Add_Link_V.\n");
		exit(1);
	}
	(*LT).LinkV = realloc((*LT).LinkV, sizeof(*(*LT).LinkV) * (size + 1));
	if((*LT).LinkV == NULL){
		perror("[Fail]:realloc@Add_Link_V.\n");
		exit(1);
	}
	(*LT).LinkV[(*LT).SN] = NULL;

	(*LT).parent_SN = realloc((*LT).parent_SN, sizeof(*(*LT).parent_SN) * (size + 1));
	if((*LT).parent_SN == NULL){
		perror("[Fail]:realloc@Add_Link_V.\n");
		exit(1);
	}

	return(LT);
}

int Add_Link_V(struct LinkTable *LT, int _parent_SN){
	int size = (*LT).SN;

	(*LT).Head = realloc((*LT).Head, sizeof(*(*LT).Head) * (size + 2));
	if((*LT).Head == NULL){
		perror("[Fail]:realloc@Alloc_Link_V.^\n");
		exit(1);
	}
	(*LT).Head[size+1] = NULL;

	(*LT).parent_SN = realloc((*LT).parent_SN, sizeof(*(*LT).parent_SN) * (size + 2));
	if((*LT).parent_SN == NULL){
		perror("[Fail]:realloc@Add_Link_V.\n");
		exit(1);
	}
	(*LT).parent_SN[size+1] = (*LT).SN;

	(*LT).Lv = realloc((*LT).Lv, sizeof(*(*LT).Lv) * (size + 2));
	if((*LT).Lv == NULL){
		perror("[Fail]:realloc@Alloc_Link_V.^\n");
		exit(1);
	}
	(*LT).Lv[size+1] = -1;

	(*LT).Conj = realloc((*LT).Conj, sizeof(*(*LT).Conj) * (size + 2));
	if((*LT).Conj == NULL){
		perror("[Fail]:realloc@Alloc_Link_V.^\n");
		exit(1);
	}
	(*LT).Conj[size+1] = 0;

	(*LT).LinkVC = realloc((*LT).LinkVC, sizeof(*(*LT).LinkVC) * (size + 2));
	if((*LT).LinkVC == NULL){
		perror("[Fail]:realloc@Add_Link_V.\n");
		exit(1);
	}
	(*LT).LinkVC[size+1] = 0;

	(*LT).LinkV = realloc((*LT).LinkV, sizeof(*(*LT).LinkV) * (size + 2));
	if((*LT).LinkV == NULL){
		perror("[Fail]:realloc@Add_Link_V.\n");
		exit(1);
	}
	(*LT).LinkV[size+1] = NULL;


	(*LT).SN++;

	return(0);
}

int Add_Link_Memb(struct LinkTable *LT, int parent_SN, int _SN){
	(*LT).LinkVC[parent_SN]++;
	(*LT).LinkV[parent_SN] = realloc((*LT).LinkV[parent_SN], sizeof(**(*LT).LinkV) * (*LT).LinkVC[parent_SN] );
	(*LT).LinkV[parent_SN][(*LT).LinkVC[parent_SN]] = _SN;
	return(0);
}

struct LinkTable *Create_LinkTable(struct LinkTable *LT, int _offset_SN){
	// under construction
	LT = malloc(sizeof(struct LinkTable) * 1);
	if(LT == NULL){
		perror("[Fail]:malloc@Create_Link.\n");
		exit(1);
	}
	if(((*LT).parent_SN = malloc(sizeof(int) * 1)) == NULL){
		perror("[Fail]:malloc@Create_LinkTable");
		exit(1);
	}
	if(((*LT).Lv = malloc(sizeof(int) * 1)) == NULL){
		perror("[Fail]:malloc@Create_LinkTable");
		exit(1);
	}



	(*LT).offset_SN = _offset_SN;
	(*LT).SN = 0;
	(*LT).parent_SN[0] = -1;
	(*LT).Lv[0] = 0;
	(*LT).Head = NULL;
	(*LT).Conj = NULL;
	(*LT).LinkVC = NULL;
	(*LT).LinkV = NULL;


	Alloc_Link_V(LT);

	return(LT);
}

