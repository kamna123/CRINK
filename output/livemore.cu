#define _NTHREAD 512
#define _NBLOCK 65535

__global__ void _AFFINE_KERNEL(int ,int ,int ,int ,int ,int ,int ,int ,int* ,int ,int ,int ,int ,int ,int ,int );

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
	int _SZ_px_2 = 20;
	int _SZ_px_1 = 20;
	int *_DEV_px;
	cudaMalloc((void**) &_DEV_px, sizeof(int)*_SZ_px_2*_SZ_px_1);
	cudaMemcpy(_DEV_px, px, sizeof(int)*_SZ_px_2*_SZ_px_1, cudaMemcpyHostToDevice);
	int _NUM_THREADS = 400;
	float _NUM_BLOCKS=1;
	int _NUM_TILE=1;
	dim3 _THREADS(512);
	dim3 _BLOCKS(1);
	if(_NUM_THREADS < _NTHREAD)
	{
		_THREADS.x=20;
		_THREADS.y=20;
	}
	else {
		_NUM_BLOCKS=(_NUM_THREADS*1.0)/256;
		_BLOCKS.x=_BLOCKS.y=ceil(sqrt(_NUM_BLOCKS));
		_THREADS.x=_THREADS.y=ceil(sqrt(400.0/(_BLOCKS.x*_BLOCKS.y)));
		int temp=_NUM_BLOCKS;
		if(_NUM_BLOCKS>_NBLOCK)
			_NUM_TILE=(temp % _NBLOCK == 0)?(_NUM_BLOCKS/_NBLOCK):((_NUM_BLOCKS/_NBLOCK)+1);
	}
	int _CUDA_TILE;
	for(_CUDA_TILE=0;_CUDA_TILE<_NUM_TILE;_CUDA_TILE++)
	{		_AFFINE_KERNEL<<<_BLOCKS,_THREADS>>>(c0, dm22, dm23, dm24, dm25, dm26, dm27, dm28, _DEV_px, _SZ_px_2, _SZ_px_1, 0, 20, 0, 20, _CUDA_TILE);
		cudaDeviceSynchronize();
	}
	cudaMemcpy(px, _DEV_px, sizeof(int)*_SZ_px_2*_SZ_px_1, cudaMemcpyDeviceToHost);
	cudaFree(_DEV_px);
    return 0;
}


__global__ void _AFFINE_KERNEL(int c0,int dm22,int dm23,int dm24,int dm25,int dm26,int dm27,int dm28,int* px,int _SZ_px_2,int _SZ_px_1,int CUDA_L_l,int CUDA_U_l, int CUDA_L_i,int CUDA_U_i, int _CUDA_TILE)
{
	int l = gridDim.x*blockDim.x*_CUDA_TILE + blockDim.x*blockIdx.x + threadIdx.x;
	int i = gridDim.y*blockDim.y*_CUDA_TILE + blockDim.y*blockIdx.y + threadIdx.y;
	if((CUDA_L_l<=l)&&(l<=CUDA_U_l)){
	if((CUDA_L_i<=i)&&(i<=CUDA_U_i)){
		px[i*_SZ_px_1+0]=dm28*px[i*_SZ_px_1+12]+dm27*px[i*_SZ_px_1+11]+dm26*px[i*_SZ_px_1+10]+dm25*px[i*_SZ_px_1+9]+dm24*px[i*_SZ_px_1+8]+dm23*px[i*_SZ_px_1+7]+dm22*px[i*_SZ_px_1+6]+c0*(px[i*_SZ_px_1+4]+px[i*_SZ_px_1+5])+px[i*_SZ_px_1+2];
}}}

