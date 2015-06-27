#define _NTHREAD 512
#define _NBLOCK 65535
#include<cuda.h>

__global__ void _AFFINE_KERNEL(int* ,int ,int ,int* ,int ,int ,int ,int ,int ,int ,int ,int ,int ,int );

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
	int _SZ_y_2 = 20;
	int _SZ_y_1 = 20;
	int _SZ_x_2 = 20;
	int _SZ_x_1 = 20;
	int *_DEV_y;
	cudaMalloc((void**) &_DEV_y, sizeof(int)*_SZ_y_2*_SZ_y_1);
	cudaMemcpy(_DEV_y, y, sizeof(int)*_SZ_y_2*_SZ_y_1, cudaMemcpyHostToDevice);
	int *_DEV_x;
	cudaMalloc((void**) &_DEV_x, sizeof(int)*_SZ_x_2*_SZ_x_1);
	cudaMemcpy(_DEV_x, x, sizeof(int)*_SZ_x_2*_SZ_x_1, cudaMemcpyHostToDevice);
	float _NUM_THREADS = 400,_NUM_BLOCKS=1;
	int _NUM_TILE=1;
	dim3 _THREADS(512);
	dim3 _BLOCKS(1);
	if(_NUM_THREADS < _NTHREAD)
	{
		_THREADS.x=20;
		_THREADS.y=20;
	}
	else {
		_NUM_BLOCKS=_NUM_THREADS/256;
		_BLOCKS.x=_BLOCKS.y=ceil(sqrt(_NUM_BLOCKS));
		_THREADS.x=_THREADS.y=ceil(sqrt(400.0/(_BLOCKS.x*_BLOCKS.y)));
		int temp=_NUM_BLOCKS;
		if(_NUM_BLOCKS>_NBLOCK)
			_NUM_TILE=(temp % _NBLOCK == 0)?(_NUM_BLOCKS/_NBLOCK):((_NUM_BLOCKS/_NBLOCK)+1);
	}
	int _CUDA_TILE;
	for(i=0;i<=20;i+=3)
	for(j=0;j<=15;j+=2)
	for(_CUDA_TILE=0;_CUDA_TILE<_NUM_TILE;_CUDA_TILE++)
		_AFFINE_KERNEL<<<_BLOCKS,_THREADS>>>(_DEV_y, _SZ_y_2, _SZ_y_1, _DEV_x, _SZ_x_2, _SZ_x_1, 2, i, j, 0, 20, 0, 15, _CUDA_TILE);
	cudaDeviceSynchronize();
	cudaMemcpy(y, _DEV_y, sizeof(int)*_SZ_y_2*_SZ_y_1, cudaMemcpyDeviceToHost);
	cudaMemcpy(x, _DEV_x, sizeof(int)*_SZ_x_2*_SZ_x_1, cudaMemcpyDeviceToHost);
    for(i=0;i<20;i++)
    for(j=0;j<20;j++)
        printf("%d\t%d\n",x[i][j],y[i][j]);
    return 0;
}



__global__ void _AFFINE_KERNEL(int* y,int _SZ_y_2,int _SZ_y_1,int* x,int _SZ_x_2,int _SZ_x_1,int phi_count, int CUDA_i, int CUDA_j, int CUDA_L_i,int CUDA_U_i, int CUDA_L_j,int CUDA_U_j, int _CUDA_TILE)
{
	int i = gridDim.x*blockDim.x*_CUDA_TILE + blockDim.x*blockIdx.x + threadIdx.x;
	int j = gridDim.y*blockDim.y*_CUDA_TILE + blockDim.y*blockIdx.y + threadIdx.y;
	if((CUDA_i<=i)&&(i<(CUDA_i+3))&&(i<=CUDA_U_i)){
	if((CUDA_j<=j)&&(j<(CUDA_j+2))&&(j<=CUDA_U_j)){
		x[(3+i+5)*_SZ_x_1+5+j+1]=y[(3+i-1)*_SZ_y_1+5+j-2]+x[(3+i)*_SZ_x_1+5+j-1];
		y[(3+i+2)*_SZ_y_1+5+j+2]=x[(3+i+2)*_SZ_x_1+5+j-1];
}}}

