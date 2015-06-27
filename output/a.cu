#ifndef DATASET
	#define _NTHREAD 512
	#define _NBLOCK 65535
#endif

#include<cuda.h>
#include<time.h>


// ----------KERNEL DECLARATION----------
__global__ void _AFFINE_KERNEL_0(int* ,int ,int* ,int ,int* ,int ,int ,int ,int );

#define MIN(a,b) (((a)<(b))?(a):(b))
#include<cuda.h>
#ifndef DATASET
	#define _NTHREAD 512
	#define _NBLOCK 65535
#endif

#include<cuda.h>
#include<time.h>


// ----------KERNEL DECLARATION----------
__global__ void _AFFINE_KERNEL_2(int* ,int ,int* ,int ,int* ,int ,int ,int ,int );

#define MIN(a,b) (((a)<(b))?(a):(b))
#include<cuda.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
int main()
{
    int x[10000],y[10000],i,a[10000];
    for(i=0;i<7900;i++)
    {
        x[i]=i;
        y[i]=2*i;
        a[i]=3*i;
    }
  
    for(i=5;i<=1900;i++)
    {
       x[i]=y[i-5];
       y[i]=x[i-4];
       //y[2*i-3][3*j-5]=x[i][j];
       //x[3*i-2][2*j-4]=y[i][j];
     } 
   
   // PARALLELIZE IN CUDA START
    for(i=0;i<8000;i++)
    {
     y[i+10]=a[i+4];
      x[i+4]=y[i+2];
       
     } 
     // PARALLELIZE IN CUDA END
     // PARALLELIZE IN CUDA START
    for(i=0;i<6000;i++)
    {
     y[a[i+2]]=y[a[i+4]]*1;
      x[i+2]=y[i+4];
       
     } 
     // PARALLELIZE IN CUDA END
  // PARALLELIZE IN CUDA START
    for(i=0;i<9000;i++)
    {
     y[i+2]=a[i+4];
      x[i+2]=y[i+4];
       
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
	int _SZ_x_0 = 10000;
	int _SZ_a_0 = 10000;
	int _SZ_y_0 = 10000;

	#ifdef TIME
		clock_gettime(CLOCK_MONOTONIC, &start_0);
	#endif

	// ----------Allocating memory to Kernel Variable and copying them on device----------
	int *_DEV_x_0;
	cudaMalloc((void**) &_DEV_x_0, sizeof(int)*_SZ_x_0);
	cudaMemcpy(_DEV_x_0, x, sizeof(int)*_SZ_x_0, cudaMemcpyHostToDevice);
	int *_DEV_a_0;
	cudaMalloc((void**) &_DEV_a_0, sizeof(int)*_SZ_a_0);
	cudaMemcpy(_DEV_a_0, a, sizeof(int)*_SZ_a_0, cudaMemcpyHostToDevice);
	int *_DEV_y_0;
	cudaMalloc((void**) &_DEV_y_0, sizeof(int)*_SZ_y_0);
	cudaMemcpy(_DEV_y_0, y, sizeof(int)*_SZ_y_0, cudaMemcpyHostToDevice);

	// ----------Tiling and declaring threads and blocks required for Kernel Execution----------
	int _NUM_THREADS_0 = 10000;
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
	int Phi_0[1]={2};
	int loopUpperLimits_0[1]={8000};
	for(ID_1_0=1;ID_1_0<=8000/2+1;ID_1_0++)
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
		_AFFINE_KERNEL_0<<<_BLOCKS_0,_THREADS_0>>>(_DEV_x_0, _SZ_x_0, _DEV_a_0, _SZ_a_0, _DEV_y_0, _SZ_y_0, START_0[0], MIN(START_0[0]+2, 8000), _CUDA_TILE_0);
			cudaDeviceSynchronize();
		}
	}

	#ifdef TIME
		clock_gettime(CLOCK_MONOTONIC, &mid_end_0);
	#endif

	// ---------Copying Kernel variable from device to host----------
	cudaMemcpy(y, _DEV_y_0, sizeof(int)*_SZ_y_0, cudaMemcpyDeviceToHost);

	// ---------Releasing the memory allocated to kernel variable----------
	cudaFree(_DEV_y_0);

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
		struct timespec start_2, end_2, mid_start_2, mid_end_2;
		double runTime_2, pre_time_2, post_time_2, computeTime_2;
	#endif
	int _SZ_x_2 = 10000;
	int _SZ_a_2 = 10000;
	int _SZ_y_2 = 10000;

	#ifdef TIME
		clock_gettime(CLOCK_MONOTONIC, &start_2);
	#endif

	// ----------Allocating memory to Kernel Variable and copying them on device----------
	int *_DEV_x_2;
	cudaMalloc((void**) &_DEV_x_2, sizeof(int)*_SZ_x_2);
	cudaMemcpy(_DEV_x_2, x, sizeof(int)*_SZ_x_2, cudaMemcpyHostToDevice);
	int *_DEV_a_2;
	cudaMalloc((void**) &_DEV_a_2, sizeof(int)*_SZ_a_2);
	cudaMemcpy(_DEV_a_2, a, sizeof(int)*_SZ_a_2, cudaMemcpyHostToDevice);
	int *_DEV_y_2;
	cudaMalloc((void**) &_DEV_y_2, sizeof(int)*_SZ_y_2);
	cudaMemcpy(_DEV_y_2, y, sizeof(int)*_SZ_y_2, cudaMemcpyHostToDevice);

	// ----------Tiling and declaring threads and blocks required for Kernel Execution----------
	int _NUM_THREADS_2 = 10000;
	float _NUM_BLOCKS_2=1;
	int _NUM_TILE_2=1;
	dim3 _THREADS_2(512);
	dim3 _BLOCKS_2(1);
	if(_NUM_THREADS_2 < _NTHREAD)
	{
		_THREADS_2.x=_NUM_THREADS_2;
	}
	else {
		 _THREADS_2.x=_NTHREAD;
		_NUM_BLOCKS_2=(_NUM_THREADS_2 % _NTHREAD == 0)?(_NUM_THREADS_2/_NTHREAD):((_NUM_THREADS_2/_NTHREAD)+1);
		if(_NUM_BLOCKS_2<_NBLOCK)
			_BLOCKS_2.x=_NUM_BLOCKS_2;
		else {
			_BLOCKS_2.x=_NBLOCK;
			int temp_2=_NUM_BLOCKS_2;
			_NUM_TILE_2=(temp_2 % _NBLOCK == 0)?(_NUM_BLOCKS_2/_NBLOCK):((_NUM_BLOCKS_2/_NBLOCK)+1);
		}
	}

	#ifdef TIME
		clock_gettime(CLOCK_MONOTONIC, &mid_start_2);
	#endif

	int ID_1_2, ID_2_2, START_2[1];
	int _CUDA_TILE_2;
	int Phi_2[1]={2};
	int loopUpperLimits_2[1]={9000};
	for(ID_1_2=1;ID_1_2<=9000/2+1;ID_1_2++)
	{
		for(ID_2_2=0;ID_2_2<1;ID_2_2++)
		{
			if(Phi_2[ID_2_2]>=0)
				START_2[ID_2_2]=(ID_1_2-1)*Phi_2[ID_2_2];
			else
				START_2[ID_2_2]=loopUpperLimits_2[ID_2_2]+(ID_1_2-1)*Phi_2[ID_2_2];
		}
	for(_CUDA_TILE_2=0;_CUDA_TILE_2<_NUM_TILE_2;_CUDA_TILE_2++)
	{
		// ----------KERNEL LAUNCH----------
		_AFFINE_KERNEL_2<<<_BLOCKS_2,_THREADS_2>>>(_DEV_x_2, _SZ_x_2, _DEV_a_2, _SZ_a_2, _DEV_y_2, _SZ_y_2, START_2[0], MIN(START_2[0]+2, 9000), _CUDA_TILE_2);
			cudaDeviceSynchronize();
		}
	}

	#ifdef TIME
		clock_gettime(CLOCK_MONOTONIC, &mid_end_2);
	#endif

	// ---------Copying Kernel variable from device to host----------
	cudaMemcpy(y, _DEV_y_2, sizeof(int)*_SZ_y_2, cudaMemcpyDeviceToHost);

	// ---------Releasing the memory allocated to kernel variable----------
	cudaFree(_DEV_y_2);

	#ifdef TIME
		clock_gettime(CLOCK_MONOTONIC, &end_2);
		pre_time_2 = (double) ((((&mid_start_2)->tv_sec * 1000000000) + (&mid_start_2)->tv_nsec) - (((&start_2)->tv_sec * 1000000000) + (&start_2)->tv_nsec)) / 1000000000;
		post_time_2 = (double) ((((&end_2)->tv_sec * 1000000000) + (&end_2)->tv_nsec) - (((&mid_end_2)->tv_sec * 1000000000) + (&mid_end_2)->tv_nsec)) / 1000000000;
		computeTime_2 = (double) ((((&mid_end_2)->tv_sec * 1000000000) + (&mid_end_2)->tv_nsec) - (((&mid_start_2)->tv_sec * 1000000000) + (&mid_start_2)->tv_nsec)) / 1000000000;
		runTime_2 = (double) ((((&end_2)->tv_sec * 1000000000) + (&end_2)->tv_nsec) - (((&start_2)->tv_sec * 1000000000) + (&start_2)->tv_nsec)) / 1000000000;
	#endif

	#ifdef DATASET
		fprintf(fp,"%d,%d,%d,%d,%d,%.14f,%.14f,%.14f,%.14f,%d\n",N,_NTHREAD*_NBLOCK,_THREADS_2.x,_BLOCKS_2.x,data,pre_time_2,computeTime_2,post_time_2,runTime_2,_CUDA_TILE_2);
		fclose(fp);
		fclose(f);
	#else
	#ifdef TIME
		printf("Runtime:%f\n",runTime_2);
	#endif
	#endif
}

// ----------KERNEL DEFINITION----------


__global__ void _AFFINE_KERNEL_0(int* x,int _SZ_x_0,int* a,int _SZ_a_0,int* y,int _SZ_y_0,int CUDA_L_i_0,int CUDA_U_i_0, int _CUDA_TILE_0)
{
	int i = gridDim.x*blockDim.x*_CUDA_TILE_0 + blockDim.x*blockIdx.x + threadIdx.x;
	if((CUDA_L_i_0<=i)&&(i<=CUDA_U_i_0)){
		y[i+10]=a[i+4];
		x[i+4]=y[i+2];
}}



// ----------KERNEL DEFINITION----------


__global__ void _AFFINE_KERNEL_2(int* x,int _SZ_x_2,int* a,int _SZ_a_2,int* y,int _SZ_y_2,int CUDA_L_i_2,int CUDA_U_i_2, int _CUDA_TILE_2)
{
	int i = gridDim.x*blockDim.x*_CUDA_TILE_2 + blockDim.x*blockIdx.x + threadIdx.x;
	if((CUDA_L_i_2<=i)&&(i<=CUDA_U_i_2)){
		y[i+2]=a[i+4];
		x[i+2]=y[i+4];
}}

