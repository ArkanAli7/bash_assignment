#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MIN 0
#define MAX 100

void median(FILE* f) {

	int students=0;
	int grade;
	int hist[100]={0};
	int linenumber=1;
	int c=0;
	int scanfreturn=0;
	int mediangrade=0;
	int median=0;
	
	while(1){
	scanfreturn=fscanf(f,"%d",&grade);        /*taking grades from file*/
	if(scanfreturn == EOF){                       /*check errors*/
		break;
	}	
	else if(scanfreturn!=1){

		fprintf(stderr,"This is not a number: \%d\"\n",linenumber);
		exit(1);
	}
	else if(grade>MAX || grade<MIN){         /*check if grades in range*/

		fprintf(stderr,"This is not in our range , line number is: \%d\"\n",linenumber);
		
	}
	else
	{
	hist[grade]++;
	students++;
	}
	linenumber++;
	}
	median= (students+1)/2;
	for (int i = 0; i < 100; i++) {
		c += hist[i];
		if(c>=median){
			mediangrade=i;
			break;					
		}
	}
	fprintf(stdout,"%d	",mediangrade);

}

int main(int argc, char**argv){
	FILE *fd;
	if(argc == 1 || !strcmp("-",argv[1])){
		fd=stdin;
	}	
	else{
		fd=fopen(argv[1], "r" );
	}
	/*check errors*/
	if(!fd){
		fprintf(stderr,"File not found: \"%s\"\n", argv[1]);
		return 1 ;
	}
	median(fd);

	fclose(fd);
}
