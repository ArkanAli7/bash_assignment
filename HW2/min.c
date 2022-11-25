#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MIN 0
#define MAX 100


void min(FILE *f){
	int min=101;
	int scanfreturn;
	int line_number=1;
	int gr;
	while(1){
		scanfreturn=fscanf(f,"%d",&gr);    /*taking grades from file*/
		if(scanfreturn == EOF){                /*check errors*/
			break;
		}	
		 if(scanfreturn!=1){
			fprintf(stderr,"This is not a number: \%d\"\n",line_number);
			exit(1);
		}
		else if(gr>MAX || gr<MIN){                                   /*check if grades in range*/
			fprintf(stderr,"This is not in our range , line number is: \%d\"\n",line_number);
		}
		else if(gr<min){
		min=gr;
		}
		line_number++;
	}
	fprintf(stdout,"%d	",min);
}
	
int main(int argc, char**argv){
	FILE *f;
	if(argc == 1 || !strcmp("-",argv[1])){
		f=stdin;
	}	
	else{
		f=fopen(argv[1], "r" );
	}
	/*check errors*/
	if(!f){
		fprintf(stderr,"File not found: \"%s\"\n", argv[1]);
		return 1; 
	}
	min(f);
	fclose(f);
}

