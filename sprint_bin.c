int sprint_bin(int bin, char str[33], int len){
	char buff[32+1];
	int i;
	buff[32] = '\0';
	for(i = 0; i < 32; i++){
		if(i != 0 && bin == 0 && i >= len){
			break;
			//buff[(32-1)-i] = '0';
		}
		if(bin % 2 == 0){
			buff[(32-1)-i] = '0';
		}else{
			buff[(32-1)-i] = '1';
		}
		bin = bin / 2;
	}
	//printf("%s", buff+(32-1)-i+1);
	sprintf(str, "%s", buff+(32-1)-i+1);
	return(i);
}
