#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define CODON_MASK0 1
#define CODON_MASK1 8
#define CODON_MASK2 64
#define S_S_MASK 512
#define RES_MASK 2048

int NtoAA_print();	//return length of residue sequence
int from_arg();
int from_stdin();
int seek_atg_from_stdin();
int seek_atgandstop_loop_from_stdin();
static int stat;	//assigned to 0 ~~ 13bit
static char c;
static int code;

int main(int argc, char **argv){
	char seq[4096];
	char opt[16][1024];
	int opt_n;
	unsigned int head;
	if(argc == 1){
		from_stdin(0);
		fprintf(stderr,"status=%d\n",stat);
	}else if(argc == 2){
		sscanf(argv[1],"%s",opt[0]);
		if(strcmp(opt[0],"-t") == 0){
			//write test code here
		}else if(strcmp(opt[0],"-M") == 0){
			head = seek_atg_from_stdin(0);
			from_stdin(0);
			printf("head = %d base(s)\n",head);
			fprintf(stderr,"status=%d\n",stat);

		}else if(strcmp(opt[0],"-MS") == 0){
			head = seek_atgandstop_loop_from_stdin(0);
			if(stat != 0 ){
				printf("%d\n",stat/RES_MASK);
			}else{
				printf("\n");
			}
			fprintf(stderr,"status = %d\n",stat);

		}else{	//for directing string_var to arg
			sscanf(argv[1],"%s",seq);
			from_arg(0,seq);
			fprintf(stderr,"status = %d\n",stat);
		}
	}else if(argc == 3){
		sscanf(argv[1],"%s",opt[0]);
		if(strcmp(opt[0],"-O") == 0){
			sscanf(argv[2],"%d",&opt_n);
			from_stdin(opt_n);
			fprintf(stderr,"status=%d\n",stat);
		}else{
			printf("option(s): -O\n");
			exit(0);
		}
	}else if(argc == 4){
		sscanf(argv[1],"%s",opt[0]);
		if(strcmp(opt[0],"-O") == 0){
			sscanf(argv[2],"%d",&opt_n);
			sscanf(argv[3],"%s",seq);
			from_arg(opt_n,seq);
			fprintf(stderr,"status=%d\n",stat);
		}else{
			printf("options: -O -M or -MS\n");
			exit(0);
		}
	}else{
		printf("usage: NtoP [-M] [-MS] [-O n] sequense\n");
		exit(0);
	}
	return(0);
}	//end main

int seek_atgandstop_loop_from_stdin(){	//for option `-MS'
	char str[4];
	int i = 0;
	int head;
	/*
	for(j=0;j<skip;j++){
		scanf("%c",&c);
	}
	*/
	first:
	head = seek_atg_from_stdin(1);
	i = 0;
	while(scanf("%c",&c) != EOF){
		if((c != '\n')&&(c != ' ')){
			*(str+i) = c;
			i++;
			if(i == 3){
				*(str+3) = '\0';
				stat = NtoAA_print(str);
				if((stat == 192)||(stat == 193)||(stat == 200)){
					i = 0;
					goto first;
				}
				i = 0;
			}
		}
	}
	*(str+i) = '\0';
	stat = NtoAA_print(str);
	if((stat == 192)||(stat == 193)||(stat == 200)){
		printf("OK%d",head);
	}
	return(head);
}

int seek_atg_from_stdin(int printhead){	//return length of head to M
	int flag=0;	//flag == 7 for atg: a=4, t=2, g=1(but not use)
	unsigned int i=0;
	while(scanf("%c",&c) != EOF){
		if((c != '\n')&&(c != ' ')){
			i++;
		}
		if((c == 'a')||(c == 'A')){
			flag = 4;
		}else if( ((flag == 4)&&(c == 't'))||((flag == 4)&&(c == 'T')) ){
			flag = flag+2;
		}else if( ((flag == 6)&&(c == 'g'))||((flag == 6)&&(c == 'G')) ){
			if(printhead != 0){
				printf("%d",i-3);
			}
			printf("M");
			break;
		}else{
			flag = 0;
		}
	}
	return(i-3);
}	//seek_atg_from_stdin

int from_stdin(int skip){ //return "status" ..length of residue
	char str[4];
	int i = 0;
	int j;
	for(j=0;j<skip;j++){
		scanf("%c",&c);
	}
	while(scanf("%c",&c) != EOF){
		if((c != '\n')&&(c != ' ')){
			*(str+i) = c;
			i++;
			if(i == 3){
				*(str+3) = '\0';
				stat = NtoAA_print(str);
				i = 0;
			}
		}
	}
	*(str+i) = '\0';
	stat = NtoAA_print(str);
	printf("\n");
	return(0);
}	//from_stdin

int from_arg(int skip, char *arg){	//return status
	char str[4];
	int len;
	int i,j;
	len = strlen(arg);
	i = 0;
	for(j=skip;j<len;j++){
		if((arg[j] != '\n')&&(arg[j] != ' ')){
			if(i == 3){
				*(str+3) = '\0';
				stat = NtoAA_print(str);
				i = 0;
			}
			*(str+i) = arg[j];
			i++;
		}
	}
	*(str+i) = '\0';
	stat = NtoAA_print(str);
	printf("\n");
	return(0);
}	//from_arg

int NtoAA_print(char *tri){	//return status (len)
	//int code;
	int len;
	/* lower || UPPER */
	/* ann || ANN */
	if((strcmp(tri,"aaa") == 0)||(strcmp(tri,"AAA") == 0)){
		printf("K");
		code = 0;
		return(0);
	}else if((strcmp(tri,"aag") == 0)||(strcmp(tri,"AAG") == 0)){
		printf("K");
		code = 1;
		return(1);
	}else if((strcmp(tri,"aat") == 0)||(strcmp(tri,"AAT") == 0)){
		printf("N");
		code = 3;
		return(3);
	}else if((strcmp(tri,"aac") == 0)||(strcmp(tri,"AAC") == 0)){
		printf("N");
		code = 2;
		return(2);

	}else if((strcmp(tri,"aga") == 0)||(strcmp(tri,"AGA") == 0)){
		printf("R");
		code = 8;
		return(8);
	}else if((strcmp(tri,"agg") == 0)||(strcmp(tri,"AGG") == 0)){
		printf("R");
		code = 9;
		return(9);
	}else if((strcmp(tri,"agt") == 0)||(strcmp(tri,"AGT") == 0)){
		printf("S");
		code = 11;
		return(11);
	}else if((strcmp(tri,"agc") == 0)||(strcmp(tri,"AGC") == 0)){
		printf("S");
		code = 11;
		return(10);

	}else if((strcmp(tri,"ata") == 0)||(strcmp(tri,"ATA") == 0)){
		printf("I");
		code = 24;
		return(24);
	}else if((strcmp(tri,"atg") == 0)||(strcmp(tri,"ATG") == 0)){
		printf("M");
		code = 25;
		return(25);
	}else if((strcmp(tri,"att") == 0)||(strcmp(tri,"ATT") == 0)){
		printf("I");
		code = 27;
		return(27);
	}else if((strcmp(tri,"atc") == 0)||(strcmp(tri,"ATC") == 0)){
		printf("I");
		code = 26;
		return(26);

	}else if((strcmp(tri,"aca") == 0)||(strcmp(tri,"ACA") == 0)){
		printf("T");
		code = 16;
		return(16);
	}else if((strcmp(tri,"acg") == 0)||(strcmp(tri,"ACG") == 0)){
		printf("T");
		code = 17;
		return(17);
	}else if((strcmp(tri,"act") == 0)||(strcmp(tri,"ACT") == 0)){
		printf("T");
		code = 19;
		return(19);
	}else if((strcmp(tri,"acc") == 0)||(strcmp(tri,"ACC") == 0)){
		printf("T");
		code = 18;
		return(18);
	}else if((strcmp(tri,"acn") == 0)||(strcmp(tri,"ACN") == 0)){
		printf("T");
		code = 23;
		return(23);
	/* gnn || GNN */
	}else if((strcmp(tri,"gaa") == 0)||(strcmp(tri,"GAA") == 0)){
		printf("E");
		code = 64;
		return(64);
	}else if((strcmp(tri,"gag") == 0)||(strcmp(tri,"GAG") == 0)){
		printf("E");
		code = 65;
		return(65);
	}else if((strcmp(tri,"gat") == 0)||(strcmp(tri,"GAT") == 0)){
		printf("D");
		code = 67;
		return(67);
	}else if((strcmp(tri,"gac") == 0)||(strcmp(tri,"GAC") == 0)){
		printf("D");
		code = 66;
		return(66);

	}else if((strcmp(tri,"gta") == 0)||(strcmp(tri,"GTA") == 0)){
		printf("V");
		code = 88;
		return(88);
	}else if((strcmp(tri,"gtg") == 0)||(strcmp(tri,"GTG") == 0)){
		printf("V");
		code = 89;
		return(89);
	}else if((strcmp(tri,"gtt") == 0)||(strcmp(tri,"GTT") == 0)){
		printf("V");
		code = 91;
		return(91);
	}else if((strcmp(tri,"gtc") == 0)||(strcmp(tri,"GTC") == 0)){
		printf("V");
		code = 90;
		return(90);
	}else if((strcmp(tri,"gtn") == 0)||(strcmp(tri,"GTN") == 0)){
		printf("V");
		code = 95;
		return(95);

	}else if((strcmp(tri,"gga") == 0)||(strcmp(tri,"GGA") == 0)){
		printf("G");
		code = 72;
		return(72);
	}else if((strcmp(tri,"ggg") == 0)||(strcmp(tri,"GGG") == 0)){
		printf("G");
		code = 73;
		return(73);
	}else if((strcmp(tri,"ggt") == 0)||(strcmp(tri,"GGT") == 0)){
		printf("G");
		code = 75;
		return(75);
	}else if((strcmp(tri,"ggc") == 0)||(strcmp(tri,"GGC") == 0)){
		printf("G");
		code = 74;
		return(74);
	}else if((strcmp(tri,"ggn") == 0)||(strcmp(tri,"GGN") == 0)){
		printf("G");
		code = 79;
		return(79);

	}else if((strcmp(tri,"gca") == 0)||(strcmp(tri,"GCA") == 0)){
		printf("A");
		code = 80;
		return(80);
	}else if((strcmp(tri,"gcg") == 0)||(strcmp(tri,"GCG") == 0)){
		printf("A");
		code = 81;
		return(81);
	}else if((strcmp(tri,"gct") == 0)||(strcmp(tri,"GCT") == 0)){
		printf("A");
		code = 83;
		return(83);
	}else if((strcmp(tri,"gcc") == 0)||(strcmp(tri,"GCC") == 0)){
		printf("A");
		code = 82;
		return(82);
	}else if((strcmp(tri,"gcn") == 0)||(strcmp(tri,"GCN") == 0)){
		printf("A");
		code = 87;
		return(87);
	/* tnn || TNN */
	}else if((strcmp(tri,"taa") == 0)||(strcmp(tri,"TAA") == 0)){
		printf("*");
		code = 192;
		return(192);
	}else if((strcmp(tri,"tag") == 0)||(strcmp(tri,"TAG") == 0)){
		printf("*");
		code = 193;
		return(193);
	}else if((strcmp(tri,"tat") == 0)||(strcmp(tri,"TAT") == 0)){
		printf("Y");
		code = 195;
		return(195);
	}else if((strcmp(tri,"tac") == 0)||(strcmp(tri,"TAC") == 0)){
		printf("Y");
		code = 194;
		return(194);

	}else if((strcmp(tri,"tga") == 0)||(strcmp(tri,"TGA") == 0)){
		printf("*");
		code = 200;
		return(200);
	}else if((strcmp(tri,"tgg") == 0)||(strcmp(tri,"TGG") == 0)){
		printf("W");
		code = 201;
		return(201);
	}else if((strcmp(tri,"tgt") == 0)||(strcmp(tri,"TGT") == 0)){
		printf("C");
		code = 203;
		return(203);
	}else if((strcmp(tri,"tgc") == 0)||(strcmp(tri,"TGC") == 0)){
		printf("C");
		code = 202;
		return(202);

	}else if((strcmp(tri,"tta") == 0)||(strcmp(tri,"TTA") == 0)){
		printf("L");
		code = 216;
		return(216);
	}else if((strcmp(tri,"ttg") == 0)||(strcmp(tri,"TTG") == 0)){
		printf("L");
		code = 217;
		return(217);
	}else if((strcmp(tri,"ttt") == 0)||(strcmp(tri,"TTT") == 0)){
		printf("F");
		code = 219;
		return(219);
	}else if((strcmp(tri,"ttc") == 0)||(strcmp(tri,"TTC") == 0)){
		printf("F");
		code = 218;
		return(218);

	}else if((strcmp(tri,"tca") == 0)||(strcmp(tri,"TCA") == 0)){
		printf("S");
		code = 208;
		return(208);
	}else if((strcmp(tri,"tcg") == 0)||(strcmp(tri,"TCG") == 0)){
		printf("S");
		code = 209;
		return(209);
	}else if((strcmp(tri,"tct") == 0)||(strcmp(tri,"TCT") == 0)){
		printf("S");
		code = 211;
		return(211);
	}else if((strcmp(tri,"tcc") == 0)||(strcmp(tri,"TCC") == 0)){
		printf("S");
		code = 210;
		return(210);
	}else if((strcmp(tri,"tcn") == 0)||(strcmp(tri,"TCN") == 0)){
		printf("S");
		code = 215;
		return(215);
	/* cnn || CNN */
	}else if((strcmp(tri,"caa") == 0)||(strcmp(tri,"CAA") == 0)){
		printf("Q");
		code = 128;
		return(128);
	}else if((strcmp(tri,"cag") == 0)||(strcmp(tri,"CAG") == 0)){
		printf("Q");
		code = 129;
		return(129);
	}else if((strcmp(tri,"cat") == 0)||(strcmp(tri,"CAT") == 0)){
		printf("H");
		code = 131;
		return(131);
	}else if((strcmp(tri,"cac") == 0)||(strcmp(tri,"CAC") == 0)){
		printf("H");
		code = 130;
		return(130);

	}else if((strcmp(tri,"cta") == 0)||(strcmp(tri,"CTA") == 0)){
		printf("L");
		code = 152;
		return(152);
	}else if((strcmp(tri,"ctg") == 0)||(strcmp(tri,"CTG") == 0)){
		printf("L");
		code = 153;
		return(153);
	}else if((strcmp(tri,"ctt") == 0)||(strcmp(tri,"CTT") == 0)){
		printf("L");
		code = 155;
		return(155);
	}else if((strcmp(tri,"ctc") == 0)||(strcmp(tri,"CTC") == 0)){
		printf("L");
		code = 154;
		return(154);
	}else if((strcmp(tri,"ctn") == 0)||(strcmp(tri,"CTN") == 0)){
		printf("L");
		code = 159;
		return(159);

	}else if((strcmp(tri,"cga") == 0)||(strcmp(tri,"CGA") == 0)){
		printf("R");
		code = 136;
		return(136);
	}else if((strcmp(tri,"cgg") == 0)||(strcmp(tri,"CGG") == 0)){
		printf("R");
		code = 137;
		return(137);
	}else if((strcmp(tri,"cgt") == 0)||(strcmp(tri,"CGT") == 0)){
		printf("R");
		code = 139;
		return(139);
	}else if((strcmp(tri,"cgc") == 0)||(strcmp(tri,"CGC") == 0)){
		printf("R");
		code = 138;
		return(138);
	}else if((strcmp(tri,"cgn") == 0)||(strcmp(tri,"CGN") == 0)){
		printf("R");
		code = 143;
		return(143);

	}else if((strcmp(tri,"cca") == 0)||(strcmp(tri,"CCA") == 0)){
		printf("P");
	 	code = 144;
		return(144);
	}else if((strcmp(tri,"ccg") == 0)||(strcmp(tri,"CCG") == 0)){
		printf("P");
		code = 145;
		return(145);
	}else if((strcmp(tri,"cct") == 0)||(strcmp(tri,"CCT") == 0)){
		printf("P");
		code = 147;
		return(147);
	}else if((strcmp(tri,"ccc") == 0)||(strcmp(tri,"CCC") == 0)){
		printf("P");
		code = 146;
		return(146);
	}else if((strcmp(tri,"ccn") == 0)||(strcmp(tri,"CCN") == 0)){
		printf("P");
		code = 151;
		return(151);

	}else {
		len = strlen(tri);
		return(len*RES_MASK);
	}
	return(len*RES_MASK);
}
