// Spathoulas Dimitris 28-29/12/2022®

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>
#define k 32
char m[k];
char name[k];
FILE *fptr=NULL;
int ans;
int n;
int i,j;
double sum_1[9]={0.0};
double sum_2[9]={0.0};
double aw[9]={0.0};
double bo=0.0;

int main() {
	printf("Enter number of variables-criteria: ");
	while ((n<2)||(n>=10)) {
		scanf("%d",&n);
		if ((n<2)||(n>=10)) {
		printf("Criteria must be more than 1 and less than 10\n"); printf("Enter number of variables: "); }
	}
	
double *a=(double *)malloc(sizeof(double)*n*n);
double *b=(double *)malloc(sizeof(double)*n*n);

	printf("Enter units of perference for each criteria\n");
	for(i=0;i<n;i++) {
		for(j=0;j<n;j++) {
		if (i==j) {
			a[(i*n)+j]=1;
		}	
		if (j>i) {
			printf("criteria %2d to criteria %2d: ",i+1,j+1);
			scanf("%lf",&a[(i*n)+j]);
		}
		a[(j*n)+i]=1/a[(i*n)+j];
		printf("\n");
		}	
	}
	for(i=0;i<n;i++) {
		for(j=0;j<n;j++) {
			printf("%3.3lf ",a[(i*n)+j]); b[(i*n)+j]=a[(i*n)+j];  } printf("\n"); } 
	
	i=0;
	j=0;
	while (j<n) {
		for(i=0;i<n;i++) 
			sum_1[j]+=a[(i*n)+j];
		for(i=0;i<n;i++) {
			a[(i*n)+j]=((a[(i*n)+j]/sum_1[j])*1.0); }
		j++; printf("\n");
	}
	printf("\n\nWeights are: \n");
	for (i=0;i<n;i++) {
		for(j=0;j<n;j++) {
			sum_2[i]+=a[(i*n)+j]; }	
		sum_2[i]=sum_2[i]/(1.0*n);	
		printf("weight[crit_%d]= %5.5lf \n",i,(sum_2[i])*100.0); 
		}

	
		for(i=0;i<n;i++) 
			for(j=0;j<n;j++) 
				aw[i]+=b[(i*n)+j]*sum_2[j];
		
		for(i=0;i<n;i++) {
			aw[i]=aw[i]/sum_2[i]; printf("aw[%d]= %3.2lf \n",i,aw[i]);
			bo+=aw[i]; }
		bo=bo/n;
		
		printf("Lamda max is %4.4lf ",bo);
		
		printf("\n\nCreate a NEW file for data: ");
		scanf("%s",m);
		sprintf(name,"%s.txt",m);
		fptr=fopen(name,"w");

		if (fptr==NULL) {
			printf("\nfile couldnt be created! \n");	
		}
	
		else {
			for(i=0;i<n;i++) {
				fprintf(fptr,"crit_%d    ",i+1);
			}
			fprintf(fptr,"\n");
			for(i=0;i<n;i++)
			fprintf(fptr,"%3.3lf    ",sum_2[i]);
			printf("\nA txt file named %s is saved in this path, containing the weights of each criteria. ",name);
			fprintf(fptr,"\n");
			fprintf(fptr,"\nCL is : %3.3lf ",((bo-n)/(n-1.0)));
		} 
	fclose(fptr);
			
	
	
return 0;

}





