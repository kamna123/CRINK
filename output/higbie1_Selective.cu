#define _NTHREAD 512
#define _NBLOCK 65535
#include<cuda.h>

__global__ void _AFFINE_KERNEL(int* ,int ,int* ,int ,int ,int ,int ,int ,int ,int ,int ,int ,int );

#include<stdio.h>
#include<stdlib.h>
int main()
{
    int XP1[20][20],XS3[20],i,j,k;
    for(i=0;i<20;i++)
    for(j=0;j<20;j++)
    {
        XP1[i][j]=i+j;
        XS3[i]=2*i;
    }
	int _SZ_XS3_1 = 20;
	int _SZ_XP1_2 = 20;
	int _SZ_XP1_1 = 20;
	int *_DEV_XS3;
	cudaMalloc((void**) &_DEV_XS3, sizeof(int)*_SZ_XS3_1);
	cudaMemcpy(_DEV_XS3, XS3, sizeof(int)*_SZ_XS3_1, cudaMemcpyHostToDevice);
	int *_DEV_XP1;
	cudaMalloc((void**) &_DEV_XP1, sizeof(int)*_SZ_XP1_2*_SZ_XP1_1);
	cudaMemcpy(_DEV_XP1, XP1, sizeof(int)*_SZ_XP1_2*_SZ_XP1_1, cudaMemcpyHostToDevice);
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
	for(i=0;i<20;i+=3)
	for(_CUDA_TILE=0;_CUDA_TILE<_NUM_TILE;_CUDA_TILE++)
		_AFFINE_KERNEL<<<_BLOCKS,_THREADS>>>(_DEV_XS3, _SZ_XS3_1, _DEV_XP1, _SZ_XP1_2, _SZ_XP1_1, 2, i, j, 0, 20, 0, 20, _CUDA_TILE);
	cudaDeviceSynchronize();
	cudaMemcpy(XP1, _DEV_XP1, sizeof(int)*_SZ_XP1_2*_SZ_XP1_1, cudaMemcpyDeviceToHost);
    return 0;
}



__global__ void _AFFINE_KERNEL(int* XS3,int _SZ_XS3_1,int* XP1,int _SZ_XP1_2,int _SZ_XP1_1,int phi_count, int CUDA_i, int CUDA_j, int CUDA_L_i,int CUDA_U_i, int CUDA_L_j,int CUDA_U_j, int _CUDA_TILE)
{
	int i = gridDim.x*blockDim.x*_CUDA_TILE + blockDim.x*blockIdx.x + threadIdx.x;
	int j = gridDim.y*blockDim.y*_CUDA_TILE + blockDim.y*blockIdx.y + threadIdx.y;
	if((CUDA_i<=i)&&(i<(CUDA_i+3))&&(i<CUDA_U_i)){
	if((CUDA_L_j<=j)&&(j<CUDA_U_j)){
		XP1[i*_SZ_XP1_1+j]=XP1[(i+3)*_SZ_XP1_1+j+4]+XS3[i];
}}}

