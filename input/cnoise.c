#include<stdio.h>
#include<stdlib.h>
int main()
{
    int x[20];
    int w[20],i,j,k;
    for(i=0;i<20;i++)
    {
        x[i]=2*i;
        w[i]=2*i;
    }

    // PARALLELIZE IN CUDA START
    for( i=0; i<N; i++ ){
		x[i] = 2.0*fw[2*i];
	};
    // PARALLELIZE IN CUDA END
    
    return 0;
}

