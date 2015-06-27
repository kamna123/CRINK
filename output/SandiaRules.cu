#define _NTHREAD 512
#define _NBLOCK 65535

__global__ void _AFFINE_KERNEL(int* ,int ,int* ,int ,int ,int ,int );

#define MIN(a,b) (((a)<(b))?(a):(b))
#include<cuda.h>
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
	int _SZ_w_1 = 20;
	int _SZ_x_1 = 20;
	int *_DEV_w;
	cudaMalloc((void**) &_DEV_w, sizeof(int)*_SZ_w_1);
	cudaMemcpy(_DEV_w, w, sizeof(int)*_SZ_w_1, cudaMemcpyHostToDevice);
	int *_DEV_x;
	cudaMalloc((void**) &_DEV_x, sizeof(int)*_SZ_x_1);
	cudaMemcpy(_DEV_x, x, sizeof(int)*_SZ_x_1, cudaMemcpyHostToDevice);
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
	int ID_1, ID_2, START[1];
	int _CUDA_TILE;
	int Phi[1]={19};
	int loopUpperLimits[1]={9};
	for(ID_1=1;ID_1<=9/19+1;ID_1++)
	{
		for(ID_2=0;ID_2<1;ID_2++)
		{
			if(Phi[ID_2]>=0)
				START[ID_2]=(ID_1-1)*Phi[ID_2];
			else
				START[ID_2]=loopUpperLimits[ID_2]+(ID_1-1)*Phi[ID_2];
		}
		for(_CUDA_TILE=0;_CUDA_TILE<_NUM_TILE;_CUDA_TILE++)
		{
			_AFFINE_KERNEL<<<_BLOCKS,_THREADS>>>(_DEV_w, _SZ_w_1, _DEV_x, _SZ_x_1, START[0], MIN(START[0]+19, 9), _CUDA_TILE);
			cudaDeviceSynchronize();
		}
	}
	cudaMemcpy(w, _DEV_w, sizeof(int)*_SZ_w_1, cudaMemcpyDeviceToHost);
	cudaMemcpy(x, _DEV_x, sizeof(int)*_SZ_x_1, cudaMemcpyDeviceToHost);
	cudaFree(_DEV_w);
	cudaFree(_DEV_x);
    
    return 0;
}



__global__ void _AFFINE_KERNEL(int* w,int _SZ_w_1,int* x,int _SZ_x_1,int CUDA_L_i,int CUDA_U_i, int _CUDA_TILE)
{
	int i = gridDim.x*blockDim.x*_CUDA_TILE + blockDim.x*blockIdx.x + threadIdx.x;
	if((CUDA_L_i<=i)&&(i<=CUDA_U_i)){
		x[1+i-1]=-x[20-1-i];
		w[1+i-1]=w[20-1-i];
}}

