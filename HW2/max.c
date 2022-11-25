#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100
#define MIN 0

	

void max(FILE *f){
	int max=-1;
	int scanfreturn;
	int line_number=1;
	int gr;
	while(1){
		scanfreturn=fscanf(f,"%d",&gr);         /*taking grades from file*/
		if(scanfreturn == EOF){                   /*check error*/
			break;
		}	
		else if(scanfreturn!=1){
			fprintf(stderr,"This is not a number: \%d\"\n",line_number);
			exit(1);
		}
		else if(gr>MAX || gr<MIN){                         /*check if grades in range*/
			fprintf(stderr,"This is not in our range , line number is: \%d\"\n",line_number);
		}
		else if(gr>max){
		max=gr;
		}
		line_number++ ;
	}
	fprintf(stdout,"%d	",max);
}
int main(int argc, char**argv){
	FILE *f;
	if(argc == 1 || !strcmp("-",argv[1])){
		f=stdin;
	}	
	else{
		f=fopen(argv[1], "r" );
	}
	/*check error*/
	if(!f){
		fprintf(stderr,"File not found: \"%s\"\n", argv[1]);
		return 1; 
	}
	max(f);

	fclose(f);
}
