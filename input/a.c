#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
int main()
{
    int x[10000],y[10000],i,a[10000];
    for(i=0;i<7900;i++)
    {
        x[i]=i;
        y[i]=2*i;
        a[i]=3*i;
    }
  
    for(i=5;i<=1900;i++)
    {
       x[i]=y[i-5];
       y[i]=x[i-4];
       //y[2*i-3][3*j-5]=x[i][j];
       //x[3*i-2][2*j-4]=y[i][j];
     } 
   
   // PARALLELIZE IN CUDA START
    for(i=0;i<8000;i++)
    {
     y[i+10]=a[i+4];
      x[i+4]=y[i+2];
       
     } 
     // PARALLELIZE IN CUDA END
     // PARALLELIZE IN CUDA START
    for(i=0;i<6000;i++)
    {
     y[a[i+2]]=y[a[i+4]]*1;
      x[i+2]=y[i+4];
       
     } 
     // PARALLELIZE IN CUDA END
   // PARALLELIZE IN CUDA START
    for(i=0;i<9000;i++)
    {
     y[i+2]=a[i+4];
      x[i+2]=y[i+4];
       
     } 
     // PARALLELIZE IN CUDA END
     
    
   
    return 0;
}

