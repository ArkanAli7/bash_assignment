#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MIN 0
#define MAX 100

	

void mean(FILE *f){
	int grade;
	double avrg=0;
	int scanfreturn;
	int line_number=1;
	int students=0;
	while(1){
		scanfreturn=fscanf(f,"%d",&grade);       /*taking the grades from file*/
		if(scanfreturn == EOF){                     /*check error*/
			break;
		}	
		else if(scanfreturn!=1){
			fprintf(stderr,"This is not a number: \%d\"\n",line_number);
			exit(1);
		}
		else if(grade>MAX || grade<MIN){                   /*check if grades in range*/
			fprintf(stderr,"This is not in our range , line number is: \%d\"\n",line_number);
		
		}
		else
		{
		students++;
		avrg+=grade;
		}
		line_number++;
		
	}
	fprintf(stdout,"%.2lf	",avrg/students);
}
int main(int argc, char**argv){
	FILE *fd;
	if(argc == 1 || !strcmp("-",argv[1])){
		fd=stdin;
	}	
	else{
		fd=fopen(argv[1], "r" );
	}
	/*check error*/
	if(!fd){
		fprintf(stderr,"File not found: \"%s\"\n", argv[1]);
		return 1; 
	}
	mean(fd);

	fclose(fd);
}

		
	
		
						
