#ifndef DATASET
	#define _NTHREAD 512
	#define _NBLOCK 65535
#endif

#include<cuda.h>
#include<time.h>


// ----------KERNEL DECLARATION----------
__global__ void _AFFINE_KERNEL_0(char ,int* ,int ,int ,int ,int );

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
int main(int argc, char** argv)
{
    int N = 1000;
	int N_NODES = 100;
	int data = 1;
	//int _NTHREAD = 1, _NBLOCK = 1;
	char* readfile, *outfile;
	if(argc>1) _NTHREAD = atoi(argv[1]);
	if(argc>2) _NBLOCK = atoi(argv[2]);
	if(argc>3) data = atoi(argv[3]) + 1;
	if(argc>4) readfile = argv[4];
	int i,j;
	//srand(time(NULL));
	FILE* f;
	f = fopen(readfile, "r");
	j=0;
	char c;
	while(1){
		c = fgetc(f);
		if(c=='\n') { 
			j++;
			c = fgetc(f);
			if(c!='%') break;
		}
	}
	fscanf(f, "%d", &N_NODES);
	//printf("---------%d  ----------",N_NODES);
	fscanf(f, "%d", &N_NODES);
	fscanf(f, "%d", &N);
	if(2*N<_NTHREAD*_NBLOCK) {
		printf("%d\n",_NTHREAD*_NBLOCK);
		fclose(f);
		return 0;
	}
	struct timespec start, end, mid_start, mid_end;
	double runTime, pre_time, post_time, computeTime;
    int q[20],a[20];
    // PARALLELIZE IN CUDA START
    for(i=1;i<=10;i++)
    {
        q[i]=q[i+10]+10;
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
	int _SZ_q_0 = 20;

	#ifdef TIME
		clock_gettime(CLOCK_MONOTONIC, &start_0);
	#endif

	// ----------Allocating memory to Kernel Variable and copying them on device----------
	int *_DEV_q;
	cudaMalloc((void**) &_DEV_q_0, sizeof(int)*_SZ_q_0);
	cudaMemcpy(_DEV_q_0, q, sizeof(int)*_SZ_q_0, cudaMemcpyHostToDevice);

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

	int _CUDA_TILE_0;
	for(_CUDA_TILE_0=0;_CUDA_TILE_0<_NUM_TILE_0;_CUDA_TILE_0++)
	{
		// ----------KERNEL LAUNCH----------
		_AFFINE_KERNEL_0<<<_BLOCKS_0,_THREADS_0>>>(c_0, _DEV_q_0, _SZ_q_0, 0, 9, _CUDA_TILE_0);
		cudaDeviceSynchronize();
	}

	#ifdef TIME
		clock_gettime(CLOCK_MONOTONIC, &mid_end_0);
	#endif

	// ---------Copying Kernel variable from device to host----------
	cudaMemcpy(q, _DEV_q_0, sizeof(int)*_SZ_q_0, cudaMemcpyDeviceToHost);

	// ---------Releasing the memory allocated to kernel variable----------
	cudaFree(_DEV_q_0);

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
}

// ----------KERNEL DEFINITION----------


__global__ void _AFFINE_KERNEL_0(char c,int* q,int _SZ_q_0,int CUDA_L_i,int CUDA_U_i, int _CUDA_TILE_0)
{
	int i = gridDim.x*blockDim.x*_CUDA_TILE_0 + blockDim.x*blockIdx.x + threadIdx.x;
	if((CUDA_L_i<=i)&&(i<=CUDA_U_i)){
		q[1+i]=q[1+i+10]+10;
}}

