#define _NTHREAD 512
#define _NBLOCK 65535
#include<cuda.h>

__global__ void _AFFINE_KERNEL(int* ,int ,int* ,int ,int ,int ,int ,int ,int );

#include<stdio.h>
#include<stdlib.h>
int main()
{
    int block[20],quadrant[20],i,j,k;
    for(i=0;i<20;i++)
    {
        block[i]=2*i;
        quadrant[i]=3*i;
    }
	int _SZ_quadrant_1 = 20;
	int _SZ_block_1 = 20;
	int *_DEV_quadrant;
	cudaMalloc((void**) &_DEV_quadrant, sizeof(int)*_SZ_quadrant_1);
	cudaMemcpy(_DEV_quadrant, quadrant, sizeof(int)*_SZ_quadrant_1, cudaMemcpyHostToDevice);
	int *_DEV_block;
	cudaMalloc((void**) &_DEV_block, sizeof(int)*_SZ_block_1);
	cudaMemcpy(_DEV_block, block, sizeof(int)*_SZ_block_1, cudaMemcpyHostToDevice);
	int _NUM_THREADS = 20;
	float _NUM_BLOCKS=1;
	int _NUM_TILE=1;
	dim3 _THREADS(512);
	dim3 _BLOCKS(1);
	if(_NUM_THREADS < _NTHREAD)
	{
		_THREADS.x=_NUM_THREADS;
	}
	else {
		 _THREADS.x=_NTHREAD;
		_NUM_BLOCKS=(_NUM_THREADS % _NTHREAD == 0)?(_NUM_THREADS/_NTHREAD):((_NUM_THREADS/_NTHREAD)+1);
		if(_NUM_BLOCKS<_NBLOCK)
			_BLOCKS.x=_NUM_BLOCKS;
		else {
			_BLOCKS.x=_NBLOCK;
			int temp=_NUM_BLOCKS;
			_NUM_TILE=(temp % _NBLOCK == 0)?(_NUM_BLOCKS/_NBLOCK):((_NUM_BLOCKS/_NBLOCK)+1);
		}
	}
	int _CUDA_TILE;
	for(i=0;i<20;i+=15)
	for(_CUDA_TILE=0;_CUDA_TILE<_NUM_TILE;_CUDA_TILE++)
	{		_AFFINE_KERNEL<<<_BLOCKS,_THREADS>>>(_DEV_quadrant, _SZ_quadrant_1, _DEV_block, _SZ_block_1, 1, i, 0, 20, _CUDA_TILE);
		cudaDeviceSynchronize();
	}	cudaMemcpy(block, _DEV_block, sizeof(int)*_SZ_block_1, cudaMemcpyDeviceToHost);
	cudaFree(_DEV_block);
}



__global__ void _AFFINE_KERNEL(int* quadrant,int _SZ_quadrant_1,int* block,int _SZ_block_1,int phi_count, int CUDA_i, int CUDA_L_i,int CUDA_U_i, int _CUDA_TILE)
{
	int i = gridDim.x*blockDim.x*_CUDA_TILE + blockDim.x*blockIdx.x + threadIdx.x;
	if((CUDA_i<=i)&&(i<(CUDA_i+15))&&(i<CUDA_U_i)){
		block[15+i]=block[i];
		quadrant[15+i]=0;
}}

