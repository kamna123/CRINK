#ifndef DATASET
	#define _NTHREAD 512
	#define _NBLOCK 65535
#endif

#include<cuda.h>
#include<time.h>


// ----------KERNEL DECLARATION----------
__global__ void _AFFINE_KERNEL_0(int* ,int ,int* ,int ,int ,int ,int );

#define MIN(a,b) (((a)<(b))?(a):(b))
#include<cuda.h>
#ifndef DATASET
	#define _NTHREAD 512
	#define _NBLOCK 65535
#endif

#include<cuda.h>
#include<time.h>


// ----------KERNEL DECLARATION----------
__global__ void _AFFINE_KERNEL_1(int* ,int ,int* ,int ,int ,int ,int );

#define MIN(a,b) (((a)<(b))?(a):(b))
#include<cuda.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
int main()
{
    int x[20],y[20],i,j,k;
     // PARALLELIZE IN CUDA START
    for(i=0;i<20;i++)
    {
        x[i]=28*i;
    }
     // PARALLELIZE IN CUDA END
   // PARALLELIZE IN CUDA START
    for(i=5;i<=19;i++)
    {
       x[i]=y[i-5];
       y[i]=x[i-4];
       //y[2*i-3][3*j-5]=x[i][j];
       //x[3*i-2][2*j-4]=y[i][j];
     } 
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
		struct timespec start_0, end_0, mid_start_0, mid_end_0;
		double runTime_0, pre_time_0, post_time_0, computeTime_0;
	#endif
	int _SZ_y_0 = 20;
	int _SZ_x_0 = 20;

	#ifdef TIME
		clock_gettime(CLOCK_MONOTONIC, &start_0);
	#endif

	// ----------Allocating memory to Kernel Variable and copying them on device----------
	int *_DEV_y_0;
	cudaMalloc((void**) &_DEV_y_0, sizeof(int)*_SZ_y_0);
	cudaMemcpy(_DEV_y_0, y, sizeof(int)*_SZ_y_0, cudaMemcpyHostToDevice);
	int *_DEV_x_0;
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
		clock_gettime(CLOCK_MONOTONIC, &mid_start_0);
	#endif

	int ID_1_0, ID_2_0, START_0[1];
	int _CUDA_TILE_0;
	int Phi_0[1]={4};
	int loopUpperLimits_0[1]={20};
	for(ID_1_0=1;ID_1_0<=20/4+1;ID_1_0++)
	{
		for(ID_2_0=0;ID_2_0<1;ID_2_0++)
		{
			if(Phi_0[ID_2_0]>=0)
				START_0[ID_2_0]=(ID_1_0-1)*Phi_0[ID_2_0];
			else
				START_0[ID_2_0]=loopUpperLimits_0[ID_2_0]+(ID_1_0-1)*Phi_0[ID_2_0];
		}
	for(_CUDA_TILE_0=0;_CUDA_TILE_0<_NUM_TILE_0;_CUDA_TILE_0++)
	{
		// ----------KERNEL LAUNCH----------
		_AFFINE_KERNEL_0<<<_BLOCKS_0,_THREADS_0>>>(_DEV_y_0, _SZ_y_0, _DEV_x_0, _SZ_x_0, START_0[0], MIN(START_0[0]+4, 20), _CUDA_TILE_0);
			cudaDeviceSynchronize();
		}
	}

	#ifdef TIME
		clock_gettime(CLOCK_MONOTONIC, &mid_end_0);
	#endif

	// ---------Copying Kernel variable from device to host----------

	// ---------Releasing the memory allocated to kernel variable----------

	#ifdef TIME
		clock_gettime(CLOCK_MONOTONIC, &end_0);
		pre_time_0 = (double) ((((&mid_start_0)->tv_sec * 1000000000) + (&mid_start_0)->tv_nsec) - (((&start_0)->tv_sec * 1000000000) + (&start_0)->tv_nsec)) / 1000000000;
		post_time_0 = (double) ((((&end_0)->tv_sec * 1000000000) + (&end_0)->tv_nsec) - (((&mid_end_0)->tv_sec * 1000000000) + (&mid_end_0)->tv_nsec)) / 1000000000;
		computeTime_0 = (double) ((((&mid_end_0)->tv_sec * 1000000000) + (&mid_end_0)->tv_nsec) - (((&mid_start_0)->tv_sec * 1000000000) + (&mid_start_0)->tv_nsec)) / 1000000000;
		runTime_0 = (double) ((((&end_0)->tv_sec * 1000000000) + (&end_0)->tv_nsec) - (((&start_0)->tv_sec * 1000000000) + (&start_0)->tv_nsec)) / 1000000000;
	#endif

	#ifdef DATASET
		fprintf(fp,"%d,%d,%d,%d,%d,%.14f,%.14f,%.14f,%.14f,%d\n",N,_NTHREAD*_NBLOCK,_THREADS_0.x,_BLOCKS_0.x,data,pre_time_0,computeTime_0,post_time_0,runTime_0,_CUDA_TILE_0);
		fclose(fp);
		fclose(f);
	#else
	#ifdef TIME
		printf("Runtime:%f\n",runTime_0);
	#endif
	#endif

	#ifdef DATASET
		char* outfile = (char*)malloc(sizeof(char)*(strlen(readfile)+50));
		strcpy(outfile, readfile);
		strcat(outfile, ".data");
		FILE* fp;
		fp = fopen(outfile, "a");
	#endif

	#ifdef TIME
		struct timespec start_1, end_1, mid_start_1, mid_end_1;
		double runTime_1, pre_time_1, post_time_1, computeTime_1;
	#endif
	int _SZ_y_1 = 20;
	int _SZ_x_1 = 20;

	#ifdef TIME
		clock_gettime(CLOCK_MONOTONIC, &start_1);
	#endif

	// ----------Allocating memory to Kernel Variable and copying them on device----------
	int *_DEV_y_1;
	cudaMalloc((void**) &_DEV_y_1, sizeof(int)*_SZ_y_1);
	cudaMemcpy(_DEV_y_1, y, sizeof(int)*_SZ_y_1, cudaMemcpyHostToDevice);
	int *_DEV_x_1;
	cudaMalloc((void**) &_DEV_x_1, sizeof(int)*_SZ_x_1);
	cudaMemcpy(_DEV_x_1, x, sizeof(int)*_SZ_x_1, cudaMemcpyHostToDevice);

	// ----------Tiling and declaring threads and blocks required for Kernel Execution----------
	int _NUM_THREADS_1 = 20;
	float _NUM_BLOCKS_1=1;
	int _NUM_TILE_1=1;
	dim3 _THREADS_1(512);
	dim3 _BLOCKS_1(1);
	if(_NUM_THREADS_1 < _NTHREAD)
	{
		_THREADS_1.x=_NUM_THREADS_1;
	}
	else {
		 _THREADS_1.x=_NTHREAD;
		_NUM_BLOCKS_1=(_NUM_THREADS_1 % _NTHREAD == 0)?(_NUM_THREADS_1/_NTHREAD):((_NUM_THREADS_1/_NTHREAD)+1);
		if(_NUM_BLOCKS_1<_NBLOCK)
			_BLOCKS_1.x=_NUM_BLOCKS_1;
		else {
			_BLOCKS_1.x=_NBLOCK;
			int temp_1=_NUM_BLOCKS_1;
			_NUM_TILE_1=(temp_1 % _NBLOCK == 0)?(_NUM_BLOCKS_1/_NBLOCK):((_NUM_BLOCKS_1/_NBLOCK)+1);
		}
	}

	#ifdef TIME
		clock_gettime(CLOCK_MONOTONIC, &mid_start_1);
	#endif

	int ID_1_1, ID_2_1, START_1[1];
	int _CUDA_TILE_1;
	int Phi_1[1]={4};
	int loopUpperLimits_1[1]={14};
	for(ID_1_1=1;ID_1_1<=14/4+1;ID_1_1++)
	{
		for(ID_2_1=0;ID_2_1<1;ID_2_1++)
		{
			if(Phi_1[ID_2_1]>=0)
				START_1[ID_2_1]=(ID_1_1-1)*Phi_1[ID_2_1];
			else
				START_1[ID_2_1]=loopUpperLimits_1[ID_2_1]+(ID_1_1-1)*Phi_1[ID_2_1];
		}
	for(_CUDA_TILE_1=0;_CUDA_TILE_1<_NUM_TILE_1;_CUDA_TILE_1++)
	{
		// ----------KERNEL LAUNCH----------
		_AFFINE_KERNEL_1<<<_BLOCKS_1,_THREADS_1>>>(_DEV_y_1, _SZ_y_1, _DEV_x_1, _SZ_x_1, START_1[0], MIN(START_1[0]+4, 14), _CUDA_TILE_1);
			cudaDeviceSynchronize();
		}
	}

	#ifdef TIME
		clock_gettime(CLOCK_MONOTONIC, &mid_end_1);
	#endif

	// ---------Copying Kernel variable from device to host----------
	cudaMemcpy(y, _DEV_y_1, sizeof(int)*_SZ_y_1, cudaMemcpyDeviceToHost);
	cudaMemcpy(x, _DEV_x_1, sizeof(int)*_SZ_x_1, cudaMemcpyDeviceToHost);

	// ---------Releasing the memory allocated to kernel variable----------
	cudaFree(_DEV_y_1);
	cudaFree(_DEV_x_1);

	#ifdef TIME
		clock_gettime(CLOCK_MONOTONIC, &end_1);
		pre_time_1 = (double) ((((&mid_start_1)->tv_sec * 1000000000) + (&mid_start_1)->tv_nsec) - (((&start_1)->tv_sec * 1000000000) + (&start_1)->tv_nsec)) / 1000000000;
		post_time_1 = (double) ((((&end_1)->tv_sec * 1000000000) + (&end_1)->tv_nsec) - (((&mid_end_1)->tv_sec * 1000000000) + (&mid_end_1)->tv_nsec)) / 1000000000;
		computeTime_1 = (double) ((((&mid_end_1)->tv_sec * 1000000000) + (&mid_end_1)->tv_nsec) - (((&mid_start_1)->tv_sec * 1000000000) + (&mid_start_1)->tv_nsec)) / 1000000000;
		runTime_1 = (double) ((((&end_1)->tv_sec * 1000000000) + (&end_1)->tv_nsec) - (((&start_1)->tv_sec * 1000000000) + (&start_1)->tv_nsec)) / 1000000000;
	#endif

	#ifdef DATASET
		fprintf(fp,"%d,%d,%d,%d,%d,%.14f,%.14f,%.14f,%.14f,%d\n",N,_NTHREAD*_NBLOCK,_THREADS_1.x,_BLOCKS_1.x,data,pre_time_1,computeTime_1,post_time_1,runTime_1,_CUDA_TILE_1);
		fclose(fp);
		fclose(f);
	#else
	#ifdef TIME
		printf("Runtime:%f\n",runTime_1);
	#endif
	#endif
}

// ----------KERNEL DEFINITION----------


__global__ void _AFFINE_KERNEL_0(int* y,int _SZ_y_0,int* x,int _SZ_x_0,int CUDA_L_i_0,int CUDA_U_i_0, int _CUDA_TILE_0)
{
	int i = gridDim.x*blockDim.x*_CUDA_TILE_0 + blockDim.x*blockIdx.x + threadIdx.x;
	if((CUDA_L_i_0<=i)&&(i<=CUDA_U_i_0)){
		x[i]=28*i;
}}



// ----------KERNEL DEFINITION----------


__global__ void _AFFINE_KERNEL_1(int* y,int _SZ_y_1,int* x,int _SZ_x_1,int CUDA_L_i_1,int CUDA_U_i_1, int _CUDA_TILE_1)
{
	int i = gridDim.x*blockDim.x*_CUDA_TILE_1 + blockDim.x*blockIdx.x + threadIdx.x;
	if((CUDA_L_i_1<=i)&&(i<=CUDA_U_i_1)){
		x[5+i]=y[5+i-5];
		y[5+i]=x[5+i-4];
}}

