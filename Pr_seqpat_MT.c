#include <stdio.h>

unsigned int fact();
unsigned int combis_seqpat();
unsigned int combis_seqpat2();
unsigned int combis_seqpat3();

int main(int argc, char **argv){
	unsigned int L;
	unsigned int l;
	unsigned int n;
	if(argc == 4){
		sscanf(argv[1],"%d",&L);
		sscanf(argv[2],"%d",&l);
		sscanf(argv[3],"%d",&n);
		printf("%d\n",combis_seqpat(L,l,n));
		printf("%d\n",combis_seqpat2(L,l,n));
		printf("%d\n",combis_seqpat3(L,l,n));
	}else if(argc == 2){
		sscanf(argv[1],"%d",&n);
		//fact(1,n);
		printf("L:10 l:3 n:%d\n",n);
		printf("fact(%d):%d\n",n,fact(1,n));
		printf("combis:%d\n",combis_seqpat(10,3,n));
		printf("combis:%d\n",combis_seqpat2(10,3,n));
		printf("combis:%d\n",combis_seqpat3(10,3,n));
				
	}
	return(0);
}

unsigned int combis_seqpat(int L, int l, int n){
	unsigned int b;
	unsigned int out;
	b = L - n*l +n;
	//out = fact(1,b)/fact(1,(b-n))/fact(1,n);
	out = fact(n+1,(L-n*l+n))/fact(1,L-n*l);
	return(out);
	//fact(n+1,block)/fact(block,n);
}

unsigned int combis_seqpat2(int L, int l, int n){
	unsigned int b;
	unsigned int out;
	b = L - n*l +n;
	out = fact(1,b)/fact(1,(b-n))/fact(1,n);
	//out = fact(n+1,(L-n*l+n))/fact(1,L-n*l);
	return(out);
	//fact(n+1,block)/fact(block,n);
}

unsigned int combis_seqpat3(int L, int l, int n){
	unsigned int b;
	unsigned int m;
	unsigned int tmp;
	unsigned int out;
	b = L - n*l +n;
	m = b - n;
	if(m < n){
		tmp = m;
		m = n;
		n = tmp;
	}
	out = fact(m+1,b)/fact(1,n);
	//out = fact(n+1,(L-n*l+n))/fact(1,L-n*l);
	return(out);
	//fact(n+1,block)/fact(block,n);
}

unsigned int fact(int i, int j){
	int k;
	unsigned int f = 1;
	for(k = i;k <= j;k++){
		f = f*k;
	}
	return(f);
}
