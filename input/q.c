#include<stdio.h>
#include<stdlib.h>
int main()
{
    int x[20][20];
    int y[20][20];
    int a[20],i,j,k;
    int n=20;
    for(i=0;i<20;i++)
    for(j=0;j<20;j++)
    {
        x[i][j]=i+j;
        y[i][j]=2*i+j;
        a[i]=2*i;
    }
    
    for(i=3;i<=19;i++)
    for(j=5;j<=19;j++)
    {
       x[i][j]=y[i-3][j-5];
       y[i][j]=x[i-2][j-4];
       //y[2*i-3][3*j-5]=x[i][j];
       //x[3*i-2][2*j-4]=y[i][j];
     } 
    
    for(i=0;i<20;i++)
    for(j=0;j<20;j++)
        printf("%d\t%d\n",x[i][j],y[i][j]);
    return 0;
}

