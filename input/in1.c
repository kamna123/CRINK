#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
int main()
{
    int x[20],y[20],i,j,k;
     // PARALLELIZE IN CUDA START
    for(i=0;i<20;i++)
    {
        x[i]=28*i;
    }
     // PARALLELIZE IN CUDA END
    // PARALLELIZE IN CUDA START
    for(i=5;i<=19;i++)
    {
       x[i]=y[i-5];
       y[i]=x[i-4];
       //y[2*i-3][3*j-5]=x[i][j];
       //x[3*i-2][2*j-4]=y[i][j];
     } 
    // PARALLELIZE IN CUDA END
    return 0;
}

