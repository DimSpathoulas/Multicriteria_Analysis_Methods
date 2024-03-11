// Spathoulas Dimitris 29-1/1/2023®

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>
#define k 128
#define mm 500
#define nn 15
double min=pow(10,10);
double max=-1;
int i,j;
FILE *fptr;
char name[k];
double sum_1[mm+2];
double sum_2[mm+2];
double S_1[nn];
double S_2[nn];
double CL[nn];
int rank[nn];
double ideal[nn];
double a_ideal[nn];
struct alts {
	double crit[nn];
	int type[nn];
	double var[nn];
	double normalized[nn];
	double weighted[nn];
	double id[nn];
	double aid[nn];
};
struct alts A[mm];
int BEST;
int SEC=0;
int m;
int n;
double P;
int main (){
	
	do {
	printf("Please enter number of alternatives: ");
	scanf("%d",&m); }
	while (!(m<2000) );
	do {
	printf("Please enter number of criteria: ");
	scanf("%d",&n); }
	while (!(n<20) );
	do {
	printf("Please enter number of P (double): ");
	scanf("%lf",&P); }
	while (!(P>0.0) );
	m=m+2;
	
	printf("\nWrite name (and destination) of txt file containing weights, type of criteria and values: ");
	scanf("%s",&name);
	
	fptr=fopen(name,"r");

		if (fptr==NULL) {
			printf("\nFile couldnt be found! \n");	
		}
	
		else {
			
			for(j=0;j<n;j++) {
				fscanf(fptr,"%d",&A[0].type[j]); }
			for (j=0;j<n;j++) 
				fscanf(fptr,"%lf",&A[1].crit[j]);
			
			
			for(i=2;i<m;i++) {
				for(j=0;j<n;j++)
					fscanf(fptr,"%lf",&A[i].var[j]);
			}
			
		} 
	fclose(fptr);
	
	for(j=0;j<n;j++) {
		
		for (i=2;i<m;i++)
			if (A[i].var[j] > max ) max=A[i].var[j];
				
		if (A[0].type[j]==1) {		
			for (i=2;i<m;i++) {
				A[i].normalized[j]=A[i].var[j]/max;
			}
		}
		
		if (A[0].type[j]==0) {
			for (i=2;i<m;i++) {
				A[i].normalized[j]=(1.0-(A[i].var[j]/max));
			}	
		}
		
			max=-1;
	}
		
			
	for(j=0;j<n;j++){
		for(i=2;i<m;i++)
			A[i].weighted[j]=A[i].normalized[j]*A[1].crit[j];
	}
		
	for (j=0;j<n;j++) {
		for(i=2;i<m;i++) {
			if (A[i].weighted[j]>max) {
				ideal[j]=A[i].weighted[j]; max=A[i].weighted[j]; }
			if (A[i].weighted[j]<min) {
				a_ideal[j]=A[i].weighted[j]; min=A[i].weighted[j]; }
 		}
 		min=pow(10,10);
		max=-1;
	}
	
	for(j=0;j<n;j++) {
		for(i=2;i<m;i++) {
			A[i].id[j]=pow(fabs(A[i].weighted[j]-ideal[j]),P);
			A[i].aid[j]=pow(fabs(A[i].weighted[j]-a_ideal[j]),P);
		}
	}
	
	for(j=0;j<n;j++) {
		ideal[j]=0.0;
		a_ideal[j]=0.0; }
		
	for(i=2;i<m;i++) {
		for(j=0;j<n;j++) {
			sum_1[i]+=A[i].id[j];
			sum_2[i]+=A[i].aid[j]; 
		}
		
		S_1[i]=pow(sum_1[i],(1.0/P));
		S_2[i]=pow(sum_2[i],(1.0/P));
	}
	
	for(i=2;i<m;i++) {
		CL[i]=S_2[i]/(S_1[i]+S_2[i]);
	}

	for(i=2;i<m;i++) {
		if (max<CL[i]) {
			BEST=i-1; max=CL[i];
		}
	}
	for (i=2;i<m;i++) {
		if ( (fabs(max-CL[i])<0.001) && (BEST+1!=i) ) {
			SEC=i-1;
		}	
	}
	
	printf("\n\nBest Alternative(s) is (are):  %2d , ",BEST);
	if (SEC>0) printf("%2d",SEC);
	

return 0;
}


// left for help
/*	for (j=0;j<n;j++) 
		printf("%2d           ",A[0].type[j]);
	printf("\n");
	for (j=0;j<n;j++) 
		printf("%4.4lf       ",A[1].crit[j]);
	printf("\n\n");
	
	for (i=2;i<m;i++) {
		for(j=0;j<n;j++)
			printf("%3.3lf     ",A[i].var[j]);
		printf("\n"); }  */


/*		printf("\n\n");
	for (i=2;i<m;i++) {
		for(j=0;j<n;j++)
			printf("%4.4lf  ",A[i].id[j]);	
		printf("\n");
	}
	
	printf("\n\n");
	for (i=2;i<m;i++) {
		for(j=0;j<n;j++)
			printf("%4.4lf  ",A[i].aid[j]);	
		printf("\n");
	} */
	
		
/*	printf("\n\n");
	for (i=2;i<m;i++) {
		printf("%4.4lf  ",S_1[i]);
	}
	printf("\n\n");
	for (i=2;i<m;i++) {
		printf("%4.4lf  ",S_2[i]);
	} */
