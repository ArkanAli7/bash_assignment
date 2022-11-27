#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MIN 0
#define MAX 100
#define N_BINS 10

	

void hist(FILE *f, int nbins){
	int scanfreturn;
	int line_number=1;
	int grade;
	double pace;
	int right;
	int left;
	int *bins =malloc(sizeof(int)*(nbins+1));
	while(1){
		scanfreturn=fscanf(f,"%d",&grade);/*taking grades from file*/
		if(scanfreturn == EOF){     /*check errors*/
			break;
		}	
		else if(scanfreturn!=1){
			fprintf(stderr,"This is not a number: \%d\"\n",line_number);
			exit(1);
		}
		else if(grade>MAX || grade<MIN){/*check if grades in range*/
	fprintf(stderr,"not in our range , line number is: \%d\"\n",line_number);
	exit(1);
		}
		  /*filling the histogram*/
		int n = grade/(MAX/ nbins) ;
		if(n<nbins){
		bins[n]++;
		}
		else if(n == nbins){
		bins[n-1]++;
		}
		line_number++;
	}
	 pace= MAX / nbins; 	 
	 for(int i=0;i<nbins; i++) {
	 	left = pace*i;
	 	if(i<nbins-1 && i==0){
	 	   	right= ((i+1)*(pace-1));
	 	 }
	 	 else if((i>0) && (i<nbins-1)){
	 		 right= left+pace-1;
	 	 }
	 	else if(nbins==MAX && i==MAX-1){
	 		right=left;
	     fprintf(stdout,"%d-%d	%d\n",left,right,bins[i]);
	     fprintf(stdout,"%d-%d	%d\n",left+1,right+1,bins[i+1]);
	 		break;
	   	}	
	 	else right=MAX; 
	 	fprintf(stdout,"%d-%d	%d\n",left,right,bins[i]);
	}
		free(bins);
}
int main(int argc, char**argv){
	FILE *f;
	f=stdin;
	int nbins=N_BINS;
	for(int i=1 ; i<argc-1; i++)
	{
	if(!strcmp(argv[i],"-"))       
	  {
	  f=stdin;
	  }
	  else if(!strcmp(argv[i],"-n_bins"))
	  {
	  nbins= i<argc-1 ? atoi(argv[i+1]):N_BINS;
	  i++;
	  }
	  else
	  {
	  f=fopen(argv[i], "r");
	  }
	}
	
	if(!f)
	{
	fprintf(stderr,"Find not found: \%s\"\n",argv[1]);
	return 1;
	}
	hist(f,nbins);
	fclose(f);
	return 0;
}
