#include<stdio.h>
#include<stdlib.h>
int main()
{
    int a[50],i,x[20],y[20],id[20],j,w[10];
int A[5][5][5];
int B[50][50];
int C[50][50];
int D[50][50];;
    
    for(i=0;i<50;i++)
    {
        a[i]=2*i;
    }
    
     for(i=5;i<=19;i++)
     {
        id[i]=i;
     }
  
    // PARALLELIZE IN CUDA START
for(i=0;i<50;i++){
	
		//A[B[i][j]][C[i][j]][D[i][j]] = (A[C[i][j]][D[i][j]][B[i][j]] + A[D[i][j]][B[i][j]][C[i][j]]) % 1000000007;
              A[a[i]]=A[a[i]]+10;
		
	}


// PARALLELIZE IN CUDA END
  // PARALLELIZE IN CUDA START
    for(i=0;i<46;i++)
    {
       a[i+10]=a[i+2];
     } 
    // PARALLELIZE IN CUDA END
    // PARALLELIZE IN CUDA START
     for ( i = 1; i <=10; i=i+1 )
  {
    w[i] =w[i+1] +3.14 /10;
  }
  // PARALLELIZE IN CUDA END
  // PARALLELIZE IN CUDA START
  for ( i = 1; i <=10; i=i+1 )
  {
    x[i] =x[i+1]+10;
  }
  // PARALLELIZE IN CUDA END
    return 0;
}

