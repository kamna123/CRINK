#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
int main()
{
    int a[20],i,j,k;
    int n=20;
    for(i=0;i<20;i++)
    {
        a[i]=2*i;
    }
   // PARALLELIZE IN CUDA START
    for(i=18;i>0;i--)
    {
       a[i+1]=a[i-1];
       //y[2*i-3][3*j-5]=x[i][j];
       //x[3*i-2][2*j-4]=y[i][j];
     } 
    // PARALLELIZE IN CUDA END
    return 0;
}

}