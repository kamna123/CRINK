// NO DEPENDENCY case of SandiaRules.c
__global__ void _AFFINE_KERNEL(int* ,int ,int* ,int ,int ,int ,int );

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main(int argc, char** argv){
{
    int N = 1000;
	int N_NODES = 100;
	int data = 1;
	int _NTHREAD = 1, _NBLOCK = 1;
	char* readfile, *outfile;
	if(argc>1) _NTHREAD = atoi(argv[1]);
	if(argc>2) _NBLOCK = atoi(argv[2]);
	if(argc>3) data = atoi(argv[3]) + 1;
	if(argc>4) readfile = argv[4];
	int i,j;
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
	fscanf(f, "%d", &N_NODES);
	fscanf(f, "%d", &N);
	if(2*N<_NTHREAD*_NBLOCK) {
		printf("%d\n",_NTHREAD*_NBLOCK);
		fclose(f);
		return 0;
	}
	struct timespec start, end, mid_start, mid_end;
	double runTime, pre_time, post_time, computeTime;
    outfile = (char*)malloc(sizeof(char)*(strlen(readfile)+50));
	strcpy(outfile, readfile);
	strcat(outfile, ".data_Sandia_Ban_Simple");
	FILE* fp;
	fp = fopen(outfile, "a");
    int x[N],w[N];    
    for (i = 0; i < N; i++) 
        {
		    fscanf(f, "%d", &x[i]);
		    fscanf(f, "%d", &w[i]);
	    }
    clock_gettime(CLOCK_MONOTONIC, &start);
	int _SZ_w_1 = N;
	int _SZ_x_1 = N;
	int *_DEV_w;
	cudaMalloc((void**) &_DEV_w, sizeof(int)*_SZ_w_1);
	cudaMemcpy(_DEV_w, w, sizeof(int)*_SZ_w_1, cudaMemcpyHostToDevice);
	int *_DEV_x;
	cudaMalloc((void**) &_DEV_x, sizeof(int)*_SZ_x_1);
	cudaMemcpy(_DEV_x, x, sizeof(int)*_SZ_x_1, cudaMemcpyHostToDevice);
	int _NUM_THREADS = N,_NUM_BLOCKS=1;
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
	clock_gettime(CLOCK_MONOTONIC, &mid_start);
	for(_CUDA_TILE=0;_CUDA_TILE<_NUM_TILE;_CUDA_TILE++)
	{
		_AFFINE_KERNEL<<<_BLOCKS,_THREADS>>>(_DEV_w, _SZ_w_1, _DEV_x, _SZ_x_1, 0, N, _CUDA_TILE);
	    cudaDeviceSynchronize();
	    }
	clock_gettime(CLOCK_MONOTONIC, &mid_end);
	cudaMemcpy(w, _DEV_w, sizeof(int)*_SZ_w_1, cudaMemcpyDeviceToHost);
	cudaMemcpy(x, _DEV_x, sizeof(int)*_SZ_x_1, cudaMemcpyDeviceToHost);
    cudaFree(_DEV_w);
    cudaFree(_DEV_x);
    clock_gettime(CLOCK_MONOTONIC, &end);
	pre_time = (double) ((((&mid_start)->tv_sec * 1000000000) + (&mid_start)->tv_nsec) - (((&start)->tv_sec * 1000000000) + (&start)->tv_nsec)) / 1000000000;
	post_time = (double) ((((&end)->tv_sec * 1000000000) + (&end)->tv_nsec) - (((&mid_end)->tv_sec * 1000000000) + (&mid_end)->tv_nsec)) / 1000000000;
	computeTime = (double) ((((&mid_end)->tv_sec * 1000000000) + (&mid_end)->tv_nsec) - (((&mid_start)->tv_sec * 1000000000) + (&mid_start)->tv_nsec)) / 1000000000;
	
	runTime = (double) ((((&end)->tv_sec * 1000000000) + (&end)->tv_nsec) - (((&start)->tv_sec * 1000000000) + (&start)->tv_nsec)) / 1000000000;
	printf("********************************\n");
	fprintf(fp,"%d,%d,%d,%d,%d,%.14f,%.14f,%.14f,%.14f,%d\n",N,_NTHREAD*_NBLOCK,_THREADS.x,_BLOCKS.x,data,pre_time,computeTime,post_time,runTime,_CUDA_TILE);
	printf("RUN TIME: %.14f\n", runTime);

	fclose(fp);
	fclose(f);
    return 0;
}



__global__ void _AFFINE_KERNEL(int* w,int _SZ_w_1,int* x,int _SZ_x_1,int CUDA_L_i,int CUDA_U_i, int _CUDA_TILE)
{
	int i = gridDim.x*blockDim.x*_CUDA_TILE + blockDim.x*blockIdx.x + threadIdx.x;
	if((CUDA_L_i<=i)&&(i<=CUDA_U_i)){
		x[1+i-1]=-x[CUDA_U_i-1-i];
		w[1+i-1]=w[CUDA_U_i-1-i];
}}

