#include <stdio.h>
int main(){
int i;
int j;
int k;
int A[5][5][5];
int B[50][50];
int C[50][50];
int D[50][50];
int count = 0;
for(i=0;i<50;i++){
	for(j=0;j<50;j++){
		B[i][j] = rand()%5;
		C[i][j] = rand()%5;
		D[i][j] = rand()%5;
		
	}
}
// cdhf!@#$%^&*()_+
//fndkf/fdmkfd
//fdlfm
/*
fetf
der
*/
for(i=0;i<5;i++)
for(j=0;j<5;j++)
for(k=0;k<5;k++)
A[i][j][k] = 1;
// PARALLELIZE IN CUDA START
for(i=0;i<50;i++){
	for(j=49;j>=0;j--){
		A[B[i][j]][C[i][j]][D[i][j]] = (A[C[i][j]][D[i][j]][B[i][j]] + A[D[i][j]][B[i][j]][C[i][j]]) % 1000000007;
		
	}
}

// PARALLELIZE IN CUDA END

for(i=0;i<5;i++){
	for(j=0;j<5;j++){
		for(k=0;k<5;k++)
			printf("%d ",A[i][j][k]);
	printf("\n");

	}
}
	printf("%d %d",i,j);
}
// f;lg,lfgnvjfgcdf
/****cdgfgf**/
/*
fe vfdg
fewft
fegf
cdklf
*/
