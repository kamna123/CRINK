#include<stdio.h>
#include<stdlib.h>
int main()
{
    int px[20][20],i,j,l,dm28,dm25,dm22,dm27,dm23,dm24,dm26,c0;
    for(i=0;i<20;i++)
    for(j=0;j<20;j++)
    {
        px[i][j]=i+j;
    }
    dm22=1,dm23=2,dm24=3,dm24=4,dm25=5,dm26=6,dm
    // PARALLELIZE IN CUDA START
    for ( l=0 ; l<20 ; l++ ) {
        for ( i=0 ; i<20 ; i++ ) {
            px[i][0] = dm28*px[i][12] + dm27*px[i][11] + dm26*px[i][10] +
                       dm25*px[i][ 9] + dm24*px[i][ 8] + dm23*px[i][ 7] +
                       dm22*px[i][ 6] + c0*( px[i][ 4] + px[i][ 5]) + px[i][ 2];
        }
    }
    // PARALLELIZE IN CUDA END
    return 0;
}
