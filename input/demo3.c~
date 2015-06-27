#include<stdio.h>
#include<stdlib.h>
int main()
{
    int X[300][300],Y[300][300],i,j;
    for(i=0;i<150;i++)
    for(i=0;i<150;i++)
    {
        X[i][j]=i+j;
        Y[i][j]=i+j;
    }
    // PARALLELIZE IN CUDA START
    for(i=1;i<=80;i++)
    for(j=1;j<=90;j++)
    {
        X[3*i+5][2*j+4]=Y[2*i-2][j+2]+23;
        Y[3*i+4][3*j+4]=X[i-1][j+4];
    }
    // PARALLELIZE IN CUDA END
    return 0;
}

