#define _NTHREAD 512
#define _NBLOCK 65535
#include<cuda.h>

__global__ void _AFFINE_KERNEL(int* ,int ,int ,int ,int ,int ,int );

#include<stdio.h>
#include<stdlib.h>
int main()
{
    int a[50],i;
    for(i=0;i<50;i++)
    {
        a[i]=2*i;
    }
	int _SZ_a_1 = 50;
	int *_DEV_a;
	cudaMalloc((void**) &_DEV_a, sizeof(int)*_SZ_a_1);
	cudaMemcpy(_DEV_a, a, sizeof(int)*_SZ_a_1, cudaMemcpyHostToDevice);
	float _NUM_THREADS = 50,_NUM_BLOCKS=1;
	int _NUM_TILE=1;
	dim3 _THREADS(512);
	dim3 _BLOCKS(1);
	if(_NUM_THREADS < _NTHREAD)
	{
		_THREADS.x=_NUM_THREADS;
	}
	else {
		 _THREADS.x=_NTHREAD;
		_NUM_BLOCKS=_NUM_THREADS/512;
		if(_NUM_BLOCKS<_NBLOCK)
			_BLOCKS.x=_NUM_BLOCKS;
		else {
			_BLOCKS.x=_NBLOCK;
			int temp=_NUM_BLOCKS;
			_NUM_TILE=(temp % _NBLOCK == 0)?(_NUM_BLOCKS/_NBLOCK):((_NUM_BLOCKS/_NBLOCK)+1);
		}
	}
	int _CUDA_TILE;
	for(i=0;i<46;i+=8)
	for(_CUDA_TILE=0;_CUDA_TILE<_NUM_TILE;_CUDA_TILE++)
		_AFFINE_KERNEL<<<_BLOCKS,_THREADS>>>(_DEV_a, _SZ_a_1, 1, i, 0, 46, _CUDA_TILE);
	cudaDeviceSynchronize();
	cudaMemcpy(a, _DEV_a, sizeof(int)*_SZ_a_1, cudaMemcpyDeviceToHost);
    return 0;
}



__global__ void _AFFINE_KERNEL(int* a,int _SZ_a_1,int phi_count, int CUDA_i, int CUDA_L_i,int CUDA_U_i, int _CUDA_TILE)
{
	int i = gridDim.x*blockDim.x*_CUDA_TILE + blockDim.x*blockIdx.x + threadIdx.x;
	if((CUDA_i<=i)&&(i<(CUDA_i+8))&&(i<CUDA_U_i)){
		a[i+10]=a[i+2];
}}

