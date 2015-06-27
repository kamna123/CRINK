#ifndef DATASET
	#define _NTHREAD 512
	#define _NBLOCK 65535
#endif

#include<cuda.h>
#include<time.h>


// ----------KERNEL DECLARATION----------
__global__ void _AFFINE_KERNEL_0(int* ,int ,int* ,int ,int ,int ,int );

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


	#ifdef DATASET
		char* outfile = (char*)malloc(sizeof(char)*(strlen(readfile)+50));
		strcpy(outfile, readfile);
		strcat(outfile, ".data");
		FILE* fp;
		fp = fopen(outfile, "a");
	#endif

	#ifdef TIME
		struct timespec start, end, mid_start, mid_end;
		double runTime, pre_time, post_time, computeTime;
	#endif
	int _SZ_w_0 = 20;
	int _SZ_x_0 = 20;

	#ifdef TIME
		clock_gettime(CLOCK_MONOTONIC, &start);
	#endif

	// ----------Allocating memory to Kernel Variable and copying them on device----------
	int *_DEV_w;
	cudaMalloc((void**) &_DEV_w_0, sizeof(int)*_SZ_w_0);
	cudaMemcpy(_DEV_w_0, w, sizeof(int)*_SZ_w_0, cudaMemcpyHostToDevice);
	int *_DEV_x;
	cudaMalloc((void**) &_DEV_x_0, sizeof(int)*_SZ_x_0);
	cudaMemcpy(_DEV_x_0, x, sizeof(int)*_SZ_x_0, cudaMemcpyHostToDevice);

	// ----------Tiling and declaring threads and blocks required for Kernel Execution----------
	int _NUM_THREADS_0 = 20;
	float _NUM_BLOCKS_0=1;
	int _NUM_TILE_0=1;
	dim3 _THREADS_0(512);
	dim3 _BLOCKS_0(1);
	if(_NUM_THREADS_0 < _NTHREAD)
	{
		_THREADS_0.x=_NUM_THREADS_0;
	}
	else {
		 _THREADS_0.x=_NTHREAD;
		_NUM_BLOCKS_0=(_NUM_THREADS_0 % _NTHREAD == 0)?(_NUM_THREADS_0/_NTHREAD):((_NUM_THREADS_0/_NTHREAD)+1);
		if(_NUM_BLOCKS_0<_NBLOCK)
			_BLOCKS_0.x=_NUM_BLOCKS_0;
		else {
			_BLOCKS_0.x=_NBLOCK;
			int temp_0=_NUM_BLOCKS_0;
			_NUM_TILE_0=(temp_0 % _NBLOCK == 0)?(_NUM_BLOCKS_0/_NBLOCK):((_NUM_BLOCKS_0/_NBLOCK)+1);
		}
	}

	#ifdef TIME
		clock_gettime(CLOCK_MONOTONIC, &mid_start);
	#endif

	int _CUDA_TILE_0;
	for(_CUDA_TILE_0=0;_CUDA_TILE_0<_NUM_TILE_0;_CUDA_TILE_0++)
	{
		// ----------KERNEL LAUNCH----------
		_AFFINE_KERNEL_0<<<_BLOCKS_0,_THREADS_0>>>(_DEV_w_0, _SZ_w_0, _DEV_x_0, _SZ_x_0, 0, 0, _CUDA_TILE_0);
		cudaDeviceSynchronize();
	}

	#ifdef TIME
		clock_gettime(CLOCK_MONOTONIC, &mid_end);
	#endif

	// ---------Copying Kernel variable from device to host----------

	// ---------Releasing the memory allocated to kernel variable----------

	#ifdef TIME
		clock_gettime(CLOCK_MONOTONIC, &end);
		pre_time = (double) ((((&mid_start)->tv_sec * 1000000000) + (&mid_start)->tv_nsec) - (((&start)->tv_sec * 1000000000) + (&start)->tv_nsec)) / 1000000000;
		post_time = (double) ((((&end)->tv_sec * 1000000000) + (&end)->tv_nsec) - (((&mid_end)->tv_sec * 1000000000) + (&mid_end)->tv_nsec)) / 1000000000;
		computeTime = (double) ((((&mid_end)->tv_sec * 1000000000) + (&mid_end)->tv_nsec) - (((&mid_start)->tv_sec * 1000000000) + (&mid_start)->tv_nsec)) / 1000000000;
		runTime = (double) ((((&end)->tv_sec * 1000000000) + (&end)->tv_nsec) - (((&start)->tv_sec * 1000000000) + (&start)->tv_nsec)) / 1000000000;
	#endif

	#ifdef DATASET
		fprintf(fp,"%d,%d,%d,%d,%d,%.14f,%.14f,%.14f,%.14f,%d\n",N,_NTHREAD*_NBLOCK,_THREADS_0.x,_BLOCKS_0.x,data,pre_time,computeTime,post_time,runTime,_CUDA_TILE_0);
		fclose(fp);
		fclose(f);
	#else
	#ifdef TIME
		printf("Runtime:%d\n",runTime);
	#endif
	#endif
}

// ----------KERNEL DEFINITION----------


__global__ void _AFFINE_KERNEL_0(int* w,int _SZ_w_0,int* x,int _SZ_x_0,int CUDA_L_i,int CUDA_U_i, int _CUDA_TILE_0)
{
	int i = gridDim.x*blockDim.x*_CUDA_TILE_0 + blockDim.x*blockIdx.x + threadIdx.x;
	if((CUDA_L_i<=i)&&(i<=CUDA_U_i)){
		x[i]=2.0*fw[2*i];
}}

