__global__ void _AFFINE_KERNEL(int* ,int ,int ,int ,int ,int);

#define MIN(a,b) (((a)<(b))?(a):(b))
#include<cuda.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
int main(int argc, char** argv)
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
    outfile = (char*)malloc(sizeof(char)*(strlen(readfile)+10));
	strcpy(outfile, readfile);
	strcat(outfile, ".data");
	FILE* fp;
	fp = fopen(outfile, "a");
    int q[N],x;    
    for (i = 0; i < N; i++) 
        {
		    fscanf(f, "%d", &q[i]);
		    fscanf(f, "%d", &x);
	    }
    clock_gettime(CLOCK_MONOTONIC, &start);
	int _SZ_q_1 = N;
	int *_DEV_q;
	cudaMalloc((void**) &_DEV_q, sizeof(int)*_SZ_q_1);
	cudaMemcpy(_DEV_q, q, sizeof(int)*_SZ_q_1, cudaMemcpyHostToDevice);
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
	int Phi[1]={2};
	int loopUpperLimits[1]={N};
	clock_gettime(CLOCK_MONOTONIC, &mid_start);
	for(ID_1=1;ID_1<=N/2+1;ID_1++)
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
			_AFFINE_KERNEL<<<_BLOCKS,_THREADS>>>(_DEV_q, _SZ_q_1, START[0], MIN(START[0]+2, N), _CUDA_TILE, N);
			cudaDeviceSynchronize();
		}
	}
	clock_gettime(CLOCK_MONOTONIC, &mid_end);
	cudaMemcpy(q, _DEV_q, sizeof(int)*_SZ_q_1, cudaMemcpyDeviceToHost);
	cudaFree(_DEV_q);
    clock_gettime(CLOCK_MONOTONIC, &end);
	pre_time = (double) ((((&mid_start)->tv_sec * 1000000000) + (&mid_start)->tv_nsec) - (((&start)->tv_sec * 1000000000) + (&start)->tv_nsec)) / 1000000000;
	post_time = (double) ((((&end)->tv_sec * 1000000000) + (&end)->tv_nsec) - (((&mid_end)->tv_sec * 1000000000) + (&mid_end)->tv_nsec)) / 1000000000;
	computeTime = (double) ((((&mid_end)->tv_sec * 1000000000) + (&mid_end)->tv_nsec) - (((&mid_start)->tv_sec * 1000000000) + (&mid_start)->tv_nsec)) / 1000000000;
	
	runTime = (double) ((((&end)->tv_sec * 1000000000) + (&end)->tv_nsec) - (((&start)->tv_sec * 1000000000) + (&start)->tv_nsec)) / 1000000000;
	printf("********************************\n");
	fprintf(fp,"%d,%d,%d,%d,%d,%.14f,%.14f,%.14f,%.14f,%d\n",N,_NTHREAD*_NBLOCK,_THREADS.x,_BLOCKS.x,data,pre_time,computeTime,post_time,runTime,_CUDA_TILE);
	//fprintf(fp,"%d,%d,%.14f\n",N_EDGES,data,runTime);
	//fclose(fp);
	printf("RUN TIME: %.14f\n", runTime);

	fclose(fp);
	fclose(f);
    return 0;
}



__global__ void _AFFINE_KERNEL(int* q,int _SZ_q_1,int CUDA_L_i,int CUDA_U_i, int _CUDA_TILE, int N)
{
	int i = gridDim.x*blockDim.x*_CUDA_TILE + blockDim.x*blockIdx.x + threadIdx.x;
	if((CUDA_L_i<=i)&&(i<=CUDA_U_i)){
		q[N-i]=q[N-i+2];
}}

