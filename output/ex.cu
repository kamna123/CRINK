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
#ifndef DATASET
	#define _NTHREAD 512
	#define _NBLOCK 65535
#endif

#include<cuda.h>
#include<time.h>


// ----------KERNEL DECLARATION----------
__global__ void _AFFINE_KERNEL_2(int* ,int ,int* ,int ,int ,int ,int );

#define MIN(a,b) (((a)<(b))?(a):(b))
#include<cuda.h>
#ifndef DATASET
	#define _NTHREAD 512
	#define _NBLOCK 65535
#endif

#include<cuda.h>
#include<time.h>


// ----------KERNEL DECLARATION----------
__global__ void _AFFINE_KERNEL_3(int* ,int ,int* ,int ,int ,int ,int );

#define MIN(a,b) (((a)<(b))?(a):(b))
#include<cuda.h>
#include<stdio.h>
#include<stdlib.h>
int main()
{
    int a[50],i,x[20],y[20],id[20],j,w[10];
int A[5][5][5];
int B[50][50];
int C[50][50];
int D[50][50];;
    
    for(i=0;i<50;i++)
    {
        a[i]=2*i;
    }
    
     for(i=5;i<=19;i++)
     {
        id[i]=i;
     }
  
    // PARALLELIZE IN CUDA START
for(i=0;i<50;i++){
	
		//A[B[i][j]][C[i][j]][D[i][j]] = (A[C[i][j]][D[i][j]][B[i][j]] + A[D[i][j]][B[i][j]][C[i][j]]) % 1000000007;
              A[a[i]]=A[a[i]]+10;
		
	}


// PARALLELIZE IN CUDA END
  // PARALLELIZE IN CUDA START
    for(i=0;i<46;i++)
    {
       a[i+10]=a[i+2];
     } 
    // PARALLELIZE IN CUDA END
    // PARALLELIZE IN CUDA START
     for ( i = 1; i <=10; i=i+1 )
  {
    w[i] =w[i+1] +3.14 /10;
  }
  // PARALLELIZE IN CUDA END
 // PARALLELIZE IN CUDA START
  for ( i = 1; i <=10; i=i+1 )
  {
    x[i] =x[i+1]+10;
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
		struct timespec start_1, end_1, mid_start_1, mid_end_1;
		double runTime_1, pre_time_1, post_time_1, computeTime_1;
	#endif
	int _SZ_a_1 = 50;
	int _SZ_a_1 = 50;

	#ifdef TIME
		clock_gettime(CLOCK_MONOTONIC, &start_1);
	#endif

	// ----------Allocating memory to Kernel Variable and copying them on device----------
	int *_DEV_a_1;
	cudaMalloc((void**) &_DEV_a_1, sizeof(int)*_SZ_a_1);
	cudaMemcpy(_DEV_a_1, a, sizeof(int)*_SZ_a_1, cudaMemcpyHostToDevice);
	int *_DEV_a_1;
	cudaMalloc((void**) &_DEV_a_1, sizeof(int)*_SZ_a_1);
	cudaMemcpy(_DEV_a_1, a, sizeof(int)*_SZ_a_1, cudaMemcpyHostToDevice);

	// ----------Tiling and declaring threads and blocks required for Kernel Execution----------
	int _NUM_THREADS_1 = 50;
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
	int Phi_1[1]={1};
	int loopUpperLimits_1[1]={46};
	for(ID_1_1=1;ID_1_1<=46/1+1;ID_1_1++)
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
		_AFFINE_KERNEL_1<<<_BLOCKS_1,_THREADS_1>>>(_DEV_a_1, _SZ_a_1, _DEV_a_1, _SZ_a_1, START_1[0], MIN(START_1[0]+1, 46), _CUDA_TILE_1);
			cudaDeviceSynchronize();
		}
	}

	#ifdef TIME
		clock_gettime(CLOCK_MONOTONIC, &mid_end_1);
	#endif

	// ---------Copying Kernel variable from device to host----------
	cudaMemcpy(a, _DEV_a_1, sizeof(int)*_SZ_a_1, cudaMemcpyDeviceToHost);

	// ---------Releasing the memory allocated to kernel variable----------
	cudaFree(_DEV_a_1);

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
	int _SZ_a_2 = 50;
	int _SZ_w_2 = 10;

	#ifdef TIME
		clock_gettime(CLOCK_MONOTONIC, &start_2);
	#endif

	// ----------Allocating memory to Kernel Variable and copying them on device----------
	int *_DEV_a_2;
	cudaMalloc((void**) &_DEV_a_2, sizeof(int)*_SZ_a_2);
	cudaMemcpy(_DEV_a_2, a, sizeof(int)*_SZ_a_2, cudaMemcpyHostToDevice);
	int *_DEV_w_2;
	cudaMalloc((void**) &_DEV_w_2, sizeof(int)*_SZ_w_2);
	cudaMemcpy(_DEV_w_2, w, sizeof(int)*_SZ_w_2, cudaMemcpyHostToDevice);

	// ----------Tiling and declaring threads and blocks required for Kernel Execution----------
	int _NUM_THREADS_2 = 50;
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
	int Phi_2[1]={1};
	int loopUpperLimits_2[1]={9};
	for(ID_1_2=1;ID_1_2<=9/1+1;ID_1_2++)
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
		_AFFINE_KERNEL_2<<<_BLOCKS_2,_THREADS_2>>>(_DEV_a_2, _SZ_a_2, _DEV_w_2, _SZ_w_2, START_2[0], MIN(START_2[0]+1, 9), _CUDA_TILE_2);
			cudaDeviceSynchronize();
		}
	}

	#ifdef TIME
		clock_gettime(CLOCK_MONOTONIC, &mid_end_2);
	#endif

	// ---------Copying Kernel variable from device to host----------
	cudaMemcpy(w, _DEV_w_2, sizeof(int)*_SZ_w_2, cudaMemcpyDeviceToHost);

	// ---------Releasing the memory allocated to kernel variable----------
	cudaFree(_DEV_w_2);

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

	#ifdef DATASET
		char* outfile = (char*)malloc(sizeof(char)*(strlen(readfile)+50));
		strcpy(outfile, readfile);
		strcat(outfile, ".data");
		FILE* fp;
		fp = fopen(outfile, "a");
	#endif

	#ifdef TIME
		struct timespec start_3, end_3, mid_start_3, mid_end_3;
		double runTime_3, pre_time_3, post_time_3, computeTime_3;
	#endif
	int _SZ_a_3 = 50;
	int _SZ_x_3 = 20;

	#ifdef TIME
		clock_gettime(CLOCK_MONOTONIC, &start_3);
	#endif

	// ----------Allocating memory to Kernel Variable and copying them on device----------
	int *_DEV_a_3;
	cudaMalloc((void**) &_DEV_a_3, sizeof(int)*_SZ_a_3);
	cudaMemcpy(_DEV_a_3, a, sizeof(int)*_SZ_a_3, cudaMemcpyHostToDevice);
	int *_DEV_x_3;
	cudaMalloc((void**) &_DEV_x_3, sizeof(int)*_SZ_x_3);
	cudaMemcpy(_DEV_x_3, x, sizeof(int)*_SZ_x_3, cudaMemcpyHostToDevice);

	// ----------Tiling and declaring threads and blocks required for Kernel Execution----------
	int _NUM_THREADS_3 = 50;
	float _NUM_BLOCKS_3=1;
	int _NUM_TILE_3=1;
	dim3 _THREADS_3(512);
	dim3 _BLOCKS_3(1);
	if(_NUM_THREADS_3 < _NTHREAD)
	{
		_THREADS_3.x=_NUM_THREADS_3;
	}
	else {
		 _THREADS_3.x=_NTHREAD;
		_NUM_BLOCKS_3=(_NUM_THREADS_3 % _NTHREAD == 0)?(_NUM_THREADS_3/_NTHREAD):((_NUM_THREADS_3/_NTHREAD)+1);
		if(_NUM_BLOCKS_3<_NBLOCK)
			_BLOCKS_3.x=_NUM_BLOCKS_3;
		else {
			_BLOCKS_3.x=_NBLOCK;
			int temp_3=_NUM_BLOCKS_3;
			_NUM_TILE_3=(temp_3 % _NBLOCK == 0)?(_NUM_BLOCKS_3/_NBLOCK):((_NUM_BLOCKS_3/_NBLOCK)+1);
		}
	}

	#ifdef TIME
		clock_gettime(CLOCK_MONOTONIC, &mid_start_3);
	#endif

	int ID_1_3, ID_2_3, START_3[1];
	int _CUDA_TILE_3;
	int Phi_3[1]={1};
	int loopUpperLimits_3[1]={9};
	for(ID_1_3=1;ID_1_3<=9/1+1;ID_1_3++)
	{
		for(ID_2_3=0;ID_2_3<1;ID_2_3++)
		{
			if(Phi_3[ID_2_3]>=0)
				START_3[ID_2_3]=(ID_1_3-1)*Phi_3[ID_2_3];
			else
				START_3[ID_2_3]=loopUpperLimits_3[ID_2_3]+(ID_1_3-1)*Phi_3[ID_2_3];
		}
	for(_CUDA_TILE_3=0;_CUDA_TILE_3<_NUM_TILE_3;_CUDA_TILE_3++)
	{
		// ----------KERNEL LAUNCH----------
		_AFFINE_KERNEL_3<<<_BLOCKS_3,_THREADS_3>>>(_DEV_a_3, _SZ_a_3, _DEV_x_3, _SZ_x_3, START_3[0], MIN(START_3[0]+1, 9), _CUDA_TILE_3);
			cudaDeviceSynchronize();
		}
	}

	#ifdef TIME
		clock_gettime(CLOCK_MONOTONIC, &mid_end_3);
	#endif

	// ---------Copying Kernel variable from device to host----------
	cudaMemcpy(x, _DEV_x_3, sizeof(int)*_SZ_x_3, cudaMemcpyDeviceToHost);

	// ---------Releasing the memory allocated to kernel variable----------
	cudaFree(_DEV_x_3);

	#ifdef TIME
		clock_gettime(CLOCK_MONOTONIC, &end_3);
		pre_time_3 = (double) ((((&mid_start_3)->tv_sec * 1000000000) + (&mid_start_3)->tv_nsec) - (((&start_3)->tv_sec * 1000000000) + (&start_3)->tv_nsec)) / 1000000000;
		post_time_3 = (double) ((((&end_3)->tv_sec * 1000000000) + (&end_3)->tv_nsec) - (((&mid_end_3)->tv_sec * 1000000000) + (&mid_end_3)->tv_nsec)) / 1000000000;
		computeTime_3 = (double) ((((&mid_end_3)->tv_sec * 1000000000) + (&mid_end_3)->tv_nsec) - (((&mid_start_3)->tv_sec * 1000000000) + (&mid_start_3)->tv_nsec)) / 1000000000;
		runTime_3 = (double) ((((&end_3)->tv_sec * 1000000000) + (&end_3)->tv_nsec) - (((&start_3)->tv_sec * 1000000000) + (&start_3)->tv_nsec)) / 1000000000;
	#endif

	#ifdef DATASET
		fprintf(fp,"%d,%d,%d,%d,%d,%.14f,%.14f,%.14f,%.14f,%d\n",N,_NTHREAD*_NBLOCK,_THREADS_3.x,_BLOCKS_3.x,data,pre_time_3,computeTime_3,post_time_3,runTime_3,_CUDA_TILE_3);
		fclose(fp);
		fclose(f);
	#else
	#ifdef TIME
		printf("Runtime:%f\n",runTime_3);
	#endif
	#endif
}

// ----------KERNEL DEFINITION----------


__global__ void _AFFINE_KERNEL_1(int* a,int _SZ_a_1,int* a,int _SZ_a_1,int CUDA_L_i_1,int CUDA_U_i_1, int _CUDA_TILE_1)
{
	int i = gridDim.x*blockDim.x*_CUDA_TILE_1 + blockDim.x*blockIdx.x + threadIdx.x;
	if((CUDA_L_i_1<=i)&&(i<=CUDA_U_i_1)){
		a[i+10]=a[i+2];
}}



// ----------KERNEL DEFINITION----------


__global__ void _AFFINE_KERNEL_2(int* a,int _SZ_a_2,int* w,int _SZ_w_2,int CUDA_L_i_2,int CUDA_U_i_2, int _CUDA_TILE_2)
{
	int i = gridDim.x*blockDim.x*_CUDA_TILE_2 + blockDim.x*blockIdx.x + threadIdx.x;
	if((CUDA_L_i_2<=i)&&(i<=CUDA_U_i_2)){
		w[1+i]=w[1+i+1]+3.14/10;
}}



// ----------KERNEL DEFINITION----------


__global__ void _AFFINE_KERNEL_3(int* a,int _SZ_a_3,int* x,int _SZ_x_3,int CUDA_L_i_3,int CUDA_U_i_3, int _CUDA_TILE_3)
{
	int i = gridDim.x*blockDim.x*_CUDA_TILE_3 + blockDim.x*blockIdx.x + threadIdx.x;
	if((CUDA_L_i_3<=i)&&(i<=CUDA_U_i_3)){
		x[1+i]=x[1+i+1]+10;
}}

