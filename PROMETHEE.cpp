// Spathoulas Dimitris 4/2/2023-5/2/2023
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>
#define nn 20 // criteria + first 
#define k 4 // upper constant
#define mm 15 // lower alternatives

int n,m,i,j,x;
int v=0;
FILE *fptr;
char name[k];
double max=-1.0;
struct upper {
	double weights[nn];
	int type[nn];
	double q[nn];
	double p[nn];
	
};
struct upper a[k];
int point;
struct lower {
	double div[mm][mm]; // mallon 2d mporei kai 1d me mm*mm kai div[j*mm+i] alla siga
	double pref[mm][mm];
	double weighted[mm][mm]; // mporo na to kano kateyueian gia ogko kai xrono apo ton pano pinaka
	
};
struct lower b[nn];

double alts[mm][mm];
double sum[mm][mm];
double f_p[mm];
double f_m[mm];
double f_net[mm];
double check=0.0;
int main() {
	
	// SCANNER
	do {
	printf("Please enter number of alternatives: ");
	scanf("%d",&m); }
	while (!(m<15) );
	do {
	printf("Please enter number of criteria: ");
	scanf("%d",&n); }
	while (!(n<20) );
	
	// FILE OPEN
		printf("\nWrite name (and destination) of txt file containing weights, type of criteria and values: ");
	scanf("%s",&name);
	
	fptr=fopen(name,"r");

		if (fptr==NULL) {
			printf("\nFile couldnt be found! \n");	
		}
	// TXT VALUES INPUT
		else {
			// UPPER KAKO ALLA LEITOYRGEI 
			// UA MPOROYSA NA KANO TON ANASTROFO APO TO TXT KAI NA EXO N GRAMMES KAI 5 STEILES GIA NA DIAVAZONTAI KALYTERA EDO
				for (j=0;j<n;j++)
				fscanf(fptr,"%lf",&a[0].weights[j]);
				for (j=0;j<n;j++)
				fscanf(fptr,"%d",&a[1].type[j]);
				for (j=0;j<n;j++)
				fscanf(fptr,"%lf",&a[2].q[j]);
				for (j=0;j<n;j++)
				fscanf(fptr,"%lf",&a[3].p[j]);
					
			// LOWER
			for (i=0;i<m;i++)
				for (j=0;j<n;j++)
					fscanf(fptr,"%lf",&alts[i][j]); v = 1;
		}
	fclose(fptr);
	
	// MAIN CODE
	if (v==1) {
		v=0;
	// 1ST STEP : DIV MATRIXES hardest one :)
	for(j=0;j<n;j++) {
		if (a[1].type[j]==1) {
			for(x=0;x<m;x++)
			for(i=0;i<m;i++) {
				b[j].div[x][i]=alts[x][j]-alts[i][j];
			}
		}
		
		if (a[1].type[j]==0) {
			for(x=0;x<m;x++)
			for(i=0;i<m;i++) {
				b[j].div[x][i]=(-1.0*(alts[x][j]-alts[i][j])); 
			}
		}
	
	}
		
		
	// 2ND STEP : PREF
	for(j=0;j<n;j++) {
		for(i=0;i<m;i++) 
			for(x=0;x<m;x++) {
				if (b[j].div[i][x]<=a[2].q[j]) {
					b[j].pref[i][x]=0.0;
				}
				
				if ((b[j].div[i][x]>a[2].q[j])&&(b[j].div[i][x]<=a[3].p[j])) { // H ELSE SAN TRITO
					b[j].pref[i][x]=(b[j].div[i][x]-a[2].q[j])/(a[3].p[j]-a[2].q[j]);
				}
				
				if (b[j].div[i][x]>a[3].p[j]) {
					b[j].pref[i][x]=1.0;
				}
			}
	}
	
			
	// STEP 3 : WEIGHTS
	for(j=0;j<n;j++) 
			for(i=0;i<m;i++) 
				for(x=0;x<m;x++) 
					b[j].weighted[i][x]=a[0].weights[j]*b[j].pref[i][x]; // mporei na ginei kateyueian pano
				

	// STEP 4 : AWP
	for(j=0;j<n;j++) // EDO EOS N GIA OLA
		for(i=0;i<m;i++)
			for(x=0;x<m;x++)
				sum[i][x]+=b[j].weighted[i][x];
				
	
	// STEP 5 : F+ F-
	for(i=0;i<m;i++) {
		for(x=0;x<m;x++) { 
			f_p[i]+=sum[i][x]; f_m[i]+=sum[x][i]; }
		f_p[i]=(f_p[i]/(m-1.0)); f_m[i]=(f_m[i]/(m-1.0)); }
		

	// STEP 6 : F NET AND SAVE TO SAME FILE
		printf("\n\n\n");
		for(i=0;i<m;i++) {
			f_net[i]=f_p[i]-f_m[i];
			printf("%5.4lf  ",f_net[i]); check+=f_net[i]; }
			printf("\n\n check=%5.3lf",check);
			
	fptr=fopen(name,"a");

		if (fptr==NULL) {
			printf("\nFile couldnt be found! \n");	
		}
	// TXT NET OUTPUTS
		else {
			fprintf(fptr,"\n\nF_net for each of the %d alternatives\n",m);
			for(i=0;i<m;i++){
				fprintf(fptr,"%6.5lf     ",f_net[i]); if (max<f_net[i]) { max=f_net[i]; point=i; }
			}
			fprintf(fptr,"\nSum of F_net is %5.5lf \n\nBest Alternative is : %3d ",check,point+1);
			
		}
		fclose(fptr);
	printf("\n\nAnswers are on the same file");
}
}

	
/*	for(i=0;i<m;i++) {
			for(x=0;x<m;x++) {
				printf("%5.2lf  ",b[0].weighted[i][x]);
			} printf("\n"); } */
	/*	for (x=0;x<3;x++)
		for (i=0;i<m;i++) {
			for(j=0;j<m;j++) {
				printf("%5.2lf   ",b[2].div[i][j]); }
			printf("\n\n"); 
		} */
	
/*	for (j=0;j<n;j++) {
		printf("%5.2lf  ",a[3].p[j]);
		}
	
	printf("\n\n");
	
	for (i=0;i<m;i++) {
		for(j=0;j<n;j++) {
			printf("%5.2lf   ",alts[i][j]); }
		printf("\n\n"); } */
		
			/*	for(i=0;i<m;i++) {
			for(x=0;x<m;x++) {
				printf("%5.2lf  ",sum[i][x]);
			} printf("\n"); } */
			
		/*	 for(i=0;i<m;i++) {
			for(x=0;x<m;x++) {
				printf("%5.2lf  ",b[2].pref[i][x]);
			} printf("\n"); }  */
		
			/*	for (i=0;i<m;i++) {
			printf("%5.3lf  ",f_p[i]);
		}
		printf("\n\n");
		for (i=0;i<m;i++) {
			printf("%5.3lf  ",f_m[i]);
		} */
