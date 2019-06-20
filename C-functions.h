int Function_Print_LinkTable(struct LinkTable *LT){
	int i,j;
	printf("Global.offset_SN:%d:\n",(*LT).offset);
	// tq: printf("Global.SN:%d:\n",(*LT).node_count);
	printf("Global.SN:%d:\n",(*LT).node_count);
	// tq: for(i=0;i<(*LT).node_count;i++){
	for(i=0;i<(*LT).node_count;i++){
		// tq: printf("Each[%d].:H=%s:",i,(*LT).head[i]);
		printf("Each[%d].:H=%s:",i,head(i));
		// tq: printf(":Pa=%d:",(*LT).parent[i]);
		printf(":Pa=%d:",parent(i));
		// printf(":Lv=%d:",(*LT).Lv[i]);	// SAK
		// tq: printf(":Lv=%d:",(*LT).level[i]);	// SAK
		printf(":Lv=%d:",level(i));	// SAK
		// tq: printf(":Cj=%d:",(*LT).conjugate[i]);
		printf(":Cj=%d:",conjugate(i));
		// tq: printf(":VC=%d:",(*LT).child_count[i]);
		printf(":VC=%d:",child_count(i));
		printf(":V");
		// tq: for(j=0;j<(*LT).child_count[i];j++){
		for(j=0;j<child_count(i);j++){
			// tq: printf(",%d",(*LT).children[i][j]);
			printf(",%d",child(i,j));
		}
		printf(":\n");
	}
	return(0);
}

/* SAK pending -> closed */
int Free_LinkTable(struct LinkTable *LT){	// SAK pending
	int i;
	for(i=0;i<(*LT).node_count;i++){
		free((*LT).head[i]);
		//free((*LT).parent);
		//free((*LT).Lv);
		//free((*LT).conjugate);
		//free((*LT).child_count);
		free((*LT).children[i]);
#ifdef MEM_DIMENSION_STR
		free((*LT).dimension_str[i]);
#endif
		free((*LT).value_poses[i]);
		free((*LT).values_str[i]);
	}

#ifdef MEM_SER
	free((*LT).ser);
#endif
	free((*LT).parent);
	// free((*LT).Lv);	// SAK
#ifdef MEM_LEVEL
	free((*LT).level);	// SAK
#endif
#ifdef MEM_CHILD_NO
	free((*LT).child_no);
#endif
	free((*LT).conjugate);
#ifdef MEM_LABEL_TYPE
	free((*LT).label_type);       // SAK rename   t -> tree, h -> head
#endif
#ifdef MEM_LABEL
	free((*LT).label);             // SAK rename
#endif
#ifdef MEM_INDICATOR_POS
	free((*LT).indicator_pos);     // SAK rename
#endif
#ifdef MEM_DIMENSION_STR
	free((*LT).dimension_str);   // SAK rename
#endif
#if MEM_VALUE_COUNT
	free((*LT).value_count);       // SAK rename
#endif
	free((*LT).value_poses);
	free((*LT).values_str);      // SAK rename
	free((*LT).child_count);
	free((*LT).head);
	free((*LT).children);
	free((*LT).ref_node);		// SAK
	free((*LT).extra_stat);		// SAK

	(*LT).offset = 0;
	(*LT).node_count = 0;
	(*LT).parent = NULL;
        // (*LT).Lv = NULL;     // SAK
        // (*LT).level = NULL;  // SAK
	(*LT).conjugate = NULL;
	(*LT).child_count = NULL;
	(*LT).head = NULL;
	(*LT).children = NULL;

	return(0);
}

struct LinkTable *Alloc_Link_V(struct LinkTable *LT){
	int size = (*LT).node_count;
	(*LT).head = realloc((*LT).head, sizeof(*(*LT).head) * (size + 1));
	if((*LT).head == NULL){
		perror("[Fail]:realloc@Alloc_Link_V.^\n");
		exit(1);
	}
#ifdef MEM_LEVEL
	(*LT).level = realloc((*LT).level, sizeof(*(*LT).level) * (size + 1));	// SAK
	if((*LT).level == NULL){							// SAK
		perror("[Fail]:realloc@Alloc_Link_V.^\n");				// SAK
		exit(1);								// SAK
	}										// SAK
#endif

#ifdef MEM_CHILD_NO
	(*LT).child_no = realloc((*LT).child_no, sizeof(*(*LT).child_no) * (size + 1));		// SAK
	if((*LT).child_no == NULL){							// SAK
		perror("[Fail]:realloc@Alloc_Link_V.^\n");			// SAK
		exit(1);							// SAK
	}									// SAK
#endif

	(*LT).conjugate = realloc((*LT).conjugate, sizeof(*(*LT).conjugate) * (size + 1));
	if((*LT).conjugate == NULL){
		perror("[Fail]:realloc@Alloc_Link_V.^\n");
		exit(1);
	}

#ifdef MEM_LABEL_TYPE
	(*LT).label_type = realloc((*LT).label_type, sizeof(*(*LT).label_type) * (size + 1));	// SAK
	if((*LT).label_type == NULL)							{	// SAK
		perror("[Fail]:realloc@Alloc_Link_V.\n");					// SAK
		exit(1);									// SAK
	}											// SAK
	(*LT).label_type[0] = ' ';								// SAK
#endif

#ifdef MEM_LABEL
	(*LT).label = realloc((*LT).label, sizeof(*(*LT).label) * (size + 1));			// SAK
	if((*LT).label == NULL)							{		// SAK
		perror("[Fail]:realloc@Alloc_Link_V.\n");					// SAK
		exit(1);									// SAK
	}											// SAK
#endif

#ifdef MEM_INDICATOR_POS
	(*LT).indicator_pos = realloc((*LT).indicator_pos, sizeof(*(*LT).indicator_pos) * (size + 1));	// SAK
	if((*LT).indicator_pos == NULL)							{	// SAK
		perror("[Fail]:realloc@Alloc_Link_V.\n");					// SAK
		exit(1);									// SAK
	}											// SAK
#endif

	(*LT).child_count = realloc((*LT).child_count, sizeof(*(*LT).child_count) * (size + 1));
	if((*LT).child_count == NULL){
		perror("[Fail]:realloc@Alloc_Link_V.\n");
		exit(1);
	}
        (*LT).child_count[0] = 0;

	(*LT).children = realloc((*LT).children, sizeof(*(*LT).children) * (size + 1));
	if((*LT).children == NULL){
		perror("[Fail]:realloc@Alloc_Link_V.\n");
		exit(1);
	}

	(*LT).children[(*LT).node_count] = NULL;

#ifdef MEM_DIMENSION_STR
	(*LT).dimension_str = realloc((*LT).dimension_str, sizeof(*(*LT).dimension_str) * (size + 1));	// SAK
	if((*LT).dimension_str == NULL){							// SAK
		perror("[Fail]:realloc@Alloc_Link_V.^\n");				// SAK
		exit(1);								// SAK
	}										// SAK
#endif

#ifdef MEM_VALUE_COUNT
	(*LT).value_count = realloc((*LT).value_count, sizeof(*(*LT).value_count) * (size + 1));		// SAK
	if((*LT).value_count == NULL){								// SAK
		perror("[Fail]:realloc@Alloc_Link_V.^\n");				// SAK
		exit(1);								// SAK
	}										// SAK
#endif

	(*LT).value_poses = realloc((*LT).value_poses, sizeof(*(*LT).value_poses) * (size + 1));	// SAK
	if((*LT).value_poses == NULL){									// SAK
		perror("[Fail]:realloc@Alloc_Link_V.\n");						// SAK
		exit(1);										// SAK
	}												// SAK
													// SAK
	(*LT).value_poses[(*LT).node_count] = NULL;							// SAK

	(*LT).values_str = realloc((*LT).values_str, sizeof(*(*LT).values_str) * (size + 1));	// SAK 
	if((*LT).values_str == NULL){							// SAK 
		perror("[Fail]:realloc@Alloc_Link_V.^\n");				// SAK 
		exit(1);								// SAK 
	}										// SAK

	(*LT).parent = realloc((*LT).parent, sizeof(*(*LT).parent) * (size + 1));
	if((*LT).parent == NULL){
		perror("[Fail]:realloc@Alloc_Link_V.\n");
		exit(1);
	}

	(*LT).ref_node = realloc((*LT).ref_node, sizeof(*(*LT).ref_node) * (size + 1));	// SAK
	if((*LT).ref_node == NULL){							// SAK
		perror("[Fail]:realloc@Alloc_Link_V.\n");				// SAK
		exit(1);								// SAK
	}										// SAK

	(*LT).extra_stat = realloc((*LT).extra_stat, sizeof(*(*LT).extra_stat) * (size + 1));	// SAK
	if((*LT).extra_stat == NULL){							// SAK
		perror("[Fail]:realloc@Alloc_Link_V.\n");				// SAK
		exit(1);								// SAK
	}										// SAK

	return(LT);
}

int Add_Link_V(struct LinkTable *LT, NODE _parent){
	// int size = (*LT).SN;		SAK pending -> close
	int size = (*LT).node_count;		// SAK
	// int bulk = (*opt).bulk_size;		// SAK pending
	int bulk = 1000000;

	if((*LT).node_count % bulk == 0) {
#ifdef MEM_SER
	(*LT).ser = realloc((*LT).ser, sizeof(*(*LT).ser) * (size + bulk));	// SAK
	if((*LT).ser == NULL){							// SAK
		perror("[Fail]:realloc@Add_Link_V.^\n");			// SAK
		exit(1);							// SAK
	}									// SAK
	(*LT).ser[size] = 0;							// SAK
#endif

	(*LT).head = realloc((*LT).head, sizeof(*(*LT).head) * (size + bulk));
	if((*LT).head == NULL){
		perror("[Fail]:realloc@Add_Link_V.^\n");
		exit(1);
	}
	(*LT).head[size] = NULL;

	(*LT).parent = realloc((*LT).parent, sizeof(*(*LT).parent) * (size + bulk));
	if((*LT).parent == NULL){
		perror("[Fail]:realloc@Add_Link_V.\n");
		exit(1);
	}
	(*LT).parent[size] = (*LT).node_count;

#ifdef MEM_LEVEL
	(*LT).level = realloc((*LT).level, sizeof(*(*LT).level) * (size + bulk));	// SAK
	if((*LT).level == NULL){							// SAK
		perror("[Fail]:realloc@Add_Link_V.^\n");				// SAK
		exit(1);								// SAK
	}										// SAK
	(*LT).level[size] = -1;							// SAK
#endif

#ifdef MEM_CHILD_NO
	(*LT).child_no = realloc((*LT).child_no, sizeof(*(*LT).child_no) * (size + bulk));	// SAK
	if((*LT).child_no == NULL){							// SAK
		perror("[Fail]:realloc@Add_Link_V.^\n");				// SAK
		exit(1);								// SAK
	}										// SAK
	(*LT).child_no[size] = 1;							// SAK
#endif

	(*LT).conjugate = realloc((*LT).conjugate, sizeof(*(*LT).conjugate) * (size + bulk));
	if((*LT).conjugate == NULL){
		perror("[Fail]:realloc@AddLink_V.^\n");
		exit(1);
	}
	(*LT).conjugate[size] = 0;

#ifdef MEM_LABEL_TYPE
	(*LT).label_type = realloc((*LT).label_type, sizeof(*(*LT).label_type) * (size + bulk));	// SAK
	if((*LT).label_type == NULL){								// SAK
		perror("[Fail]:realloc@Add_Link_V.\n");						// SAK
		exit(1);									// SAK
	}											// SAK
	(*LT).label_type[size] = ' ';								// SAK
#endif

#ifdef MEM_LABEL
	(*LT).label = realloc((*LT).label, sizeof(*(*LT).label) * (size + bulk));			// SAK
	if((*LT).label == NULL){								// SAK
		perror("[Fail]:realloc@Add_Link_V.\n");						// SAK
		exit(1);									// SAK
	}											// SAK
	(*LT).label[size] = 0;								// SAK
#endif

#ifdef MEM_INDICATOR_POS
	(*LT).indicator_pos = realloc((*LT).indicator_pos, sizeof(*(*LT).indicator_pos) * (size + bulk));	// SAK
	if((*LT).indicator_pos == NULL){								// SAK
		perror("[Fail]:realloc@Add_Link_V.\n");						// SAK
		exit(1);									// SAK
	}											// SAK
	(*LT).indicator_pos[size] = 0;								// SAK
#endif

	(*LT).child_count = realloc((*LT).child_count, sizeof(*(*LT).child_count) * (size + bulk));
	if((*LT).child_count == NULL){
		perror("[Fail]:realloc@Add_Link_V.\n");
		exit(1);
	}
	(*LT).child_count[size] = 0;

	(*LT).children = realloc((*LT).children, sizeof(*(*LT).children) * (size + bulk));
	if((*LT).children == NULL){
		perror("[Fail]:realloc@Add_Link_V.\n");
		exit(1);
	}
	(*LT).children[size] = NULL;

#ifdef MEM_DIMENSION_STR
	(*LT).dimension_str = realloc((*LT).dimension_str, sizeof(*(*LT).dimension_str) * (size + bulk));		// SAK
	if((*LT).dimension_str == NULL){							// SAK
		perror("[Fail]:realloc@Add_Link_V.^\n");				// SAK
		exit(1);								// SAK
	}										// SAK
	(*LT).dimension_str[size] = NULL;							// SAK
#endif

#ifdef MEM_VALUE_COUNT
	(*LT).value_count = realloc((*LT).value_count, sizeof(*(*LT).value_count) * (size + bulk));		// SAK
	if((*LT).value_count == NULL){								// SAK
		perror("[Fail]:realloc@Add_Link_V.\n");					// SAK
		exit(1);								// SAK
	}										// SAK
	(*LT).value_count[size] = 0;								// SAK
#endif

	(*LT).value_poses = realloc((*LT).value_poses, sizeof(*(*LT).value_poses) * (size + bulk));	// SAK
	if((*LT).value_poses == NULL){									// SAK
		perror("[Fail]:realloc@Add_Link_V.\n");							// SAK
		exit(1);										// SAK
	}												// SAK
	(*LT).value_poses[size] = NULL;									// SAK

	(*LT).values_str = realloc((*LT).values_str, sizeof(*(*LT).values_str) * (size + bulk));		// SAK
	if((*LT).values_str == NULL){							// SAK
		perror("[Fail]:realloc@Add_Link_V.^\n");				// SAK
		exit(1);								// SAK
	}										// SAK
	(*LT).values_str[size] = NULL;							// SAK

	(*LT).ref_node = realloc((*LT).ref_node, sizeof(*(*LT).ref_node) * (size + bulk));	// SAK
	if((*LT).ref_node == NULL){							// SAK
		perror("[Fail]:realloc@Add_Link_V.\n");					// SAK
		exit(1);								// SAK
	}										// SAK
	(*LT).ref_node[size] = NO_NODE;							// SAK

	(*LT).extra_stat = realloc((*LT).extra_stat, sizeof(*(*LT).extra_stat) * (size + bulk));	// SAK
	if((*LT).extra_stat == NULL){							// SAK
		perror("[Fail]:realloc@Add_Link_V.\n");					// SAK
		exit(1);								// SAK
	}										// SAK
	(*LT).extra_stat[size] = 0;							// SAK

	}

	(*LT).node_count++;

	// return(0);									// SAK
	return(size);									// SAK
}

int Add_Link_Memb(struct LinkTable *LT, NODE _parent, int _node_count){
	(*LT).child_count[_parent]++;
	(*LT).children[_parent] = realloc((*LT).children[_parent], sizeof(**(*LT).children) * (*LT).child_count[_parent] );
	(*LT).children[_parent][(*LT).child_count[_parent] -1] = _node_count;	// **SAK**
	return(0);
}

struct LinkTable *Create_LinkTable(int _offset){
	// under construction
	struct LinkTable *LT;
	LT = malloc(sizeof(struct LinkTable) * 1);
	if(LT == NULL){
		perror("[Fail]:malloc@Create_LinkTable.\n");
		exit(1);
	}
/* SAK
	if(((*LT).parent = malloc(sizeof(int) * 1)) == NULL){
		perror("[Fail]:malloc@Create_LinkTable");
		exit(1);
	}
	if(((*LT).Lv = malloc(sizeof(int) * 1)) == NULL){
		perror("[Fail]:malloc@Create_LinkTable");
		exit(1);
	}
*/

	(*LT).offset = _offset;
	(*LT).node_count = 0;
#ifdef MEM_SER
	(*LT).ser = NULL;		// SAK
#endif
	// (*LT).parent[0] = -1;	// SAK
	(*LT).parent = NULL;		// SAK
#ifdef MEM_LEVEL
	// (*LT).Lv[0] = 0;		// SAK
	(*LT).level = NULL;		// SAK
#endif
#ifdef MEM_CHILD_NO
	(*LT).child_no = NULL;		// SAK
#endif
	(*LT).head = NULL;
	(*LT).conjugate = NULL;
#ifdef MEM_LABEL_TYPE
	(*LT).label_type = NULL;		// SAK
#endif
#ifdef MEM_LABEL
	(*LT).label = NULL;		// SAK
#endif
#ifdef MEM_INDICATOR_POS
	(*LT).indicator_pos = NULL;	// SAK
#endif
#ifdef MEM_DIMENSION_STR
	(*LT).dimension_str = NULL;		// SAK
#endif
#ifdef MEM_VALUE_COUNT
	(*LT).value_count = NULL;		// SAK
#endif
	(*LT).values_str = NULL;		// SAK
	(*LT).child_count = NULL;
	(*LT).children = NULL;
	(*LT).ref_node = NULL;		// SAK


	// Alloc_Link_V(LT);		// SAK pending 不?

	return(LT);
}

