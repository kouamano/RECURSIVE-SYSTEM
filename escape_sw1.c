if(C == '\\' && ESC == 0){
	ESC = 1;
}else if(C == '\\' && ESC == 1){
	ESC = 0;
}else{
	ESC = 0;
}
