#include<cuda.h>
#include<time.h>
__global__ void _AFFINE_KERNEL(int* ,int ,int* ,int ,int ,int ,int ,int ,int ,int ,int ,int ,int );

#include<stdio.h>
#include<stdlib.h>
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
	strcat(outfile, ".data_Higbie1_TD");
	FILE* fp;
	fp = fopen(outfile, "a");
    int M,I; 
    M=sqrt(2.0*N); 
    int XP1[M][M],XS3[N];  
    i=0;
    j=0;
    for (I = 0; I < N; I++) 
    {
        if((j<=M-1)&&(i<=M-1))
        {
            fscanf(f, "%d", &XP1[i][j++]);
            XS3[I]=XP1[i][j-1];
            if(j<M)    fscanf(f, "%d", &XP1[i][j++]);
            else if(i<M-1)
            {
                j=0;
                fscanf(f, "%d", &XP1[++i][j++]);
            }
        }
        else if((j==M)&&(i<M-1))
        {
            j=0;
            fscanf(f, "%d", &XP1[++i][j++]);
            XS3[I]=XP1[i][j-1];
            fscanf(f, "%d", &XP1[i][j++]);
        }
        else if(i==M-1)
		    fscanf(f, "%d", &XS3[I]);
	}
    clock_gettime(CLOCK_MONOTONIC, &start);
	int _SZ_XS3_1 = N;
	int _SZ_XP1_2 = M;
	int _SZ_XP1_1 = M;
	int *_DEV_XS3;
	cudaMalloc((void**) &_DEV_XS3, sizeof(int)*_SZ_XS3_1);
	cudaMemcpy(_DEV_XS3, XS3, sizeof(int)*_SZ_XS3_1, cudaMemcpyHostToDevice);
	int *_DEV_XP1;
	cudaMalloc((void**) &_DEV_XP1, sizeof(int)*_SZ_XP1_2*_SZ_XP1_1);
	cudaMemcpy(_DEV_XP1, XP1, sizeof(int)*_SZ_XP1_2*_SZ_XP1_1, cudaMemcpyHostToDevice);
	float _NUM_THREADS = M*M,_NUM_BLOCKS=1;
	int _NUM_TILE=1;
	dim3 _THREADS(512);
	dim3 _BLOCKS(1);
	if(_NUM_THREADS < _NTHREAD)
	{
		_THREADS.x=M;
		_THREADS.y=M;
	}
	else {
		_NUM_BLOCKS=_NUM_THREADS/256;
		_BLOCKS.x=_BLOCKS.y=ceil(sqrt(_NUM_BLOCKS));
		_THREADS.x=_THREADS.y=ceil(sqrt((M*M*1.0)/(_BLOCKS.x*_BLOCKS.y)));
		int temp=_NUM_BLOCKS;
		if(_NUM_BLOCKS>_NBLOCK)
			_NUM_TILE=(temp % _NBLOCK == 0)?(_NUM_BLOCKS/_NBLOCK):((_NUM_BLOCKS/_NBLOCK)+1);
	}
	int _CUDA_TILE;
	clock_gettime(CLOCK_MONOTONIC, &mid_start);
	for(i=0;i<20;i+=3)
	for(j=0;j<20;j+=4)
	for(_CUDA_TILE=0;_CUDA_TILE<_NUM_TILE;_CUDA_TILE++)
	{
		_AFFINE_KERNEL<<<_BLOCKS,_THREADS>>>(_DEV_XS3, _SZ_XS3_1, _DEV_XP1, _SZ_XP1_2, _SZ_XP1_1, 2, i, j, 0, 20, 0, 20, _CUDA_TILE);
	    cudaDeviceSynchronize();
	}
	clock_gettime(CLOCK_MONOTONIC, &mid_end);
	cudaMemcpy(XP1, _DEV_XP1, sizeof(int)*_SZ_XP1_2*_SZ_XP1_1, cudaMemcpyDeviceToHost);
	cudaFree(_DEV_XP1);
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



__global__ void _AFFINE_KERNEL(int* XS3,int _SZ_XS3_1,int* XP1,int _SZ_XP1_2,int _SZ_XP1_1,int phi_count, int CUDA_i, int CUDA_j, int CUDA_L_i,int CUDA_U_i, int CUDA_L_j,int CUDA_U_j, int _CUDA_TILE)
{
	int i = gridDim.x*blockDim.x*_CUDA_TILE + blockDim.x*blockIdx.x + threadIdx.x;
	int j = gridDim.y*blockDim.y*_CUDA_TILE + blockDim.y*blockIdx.y + threadIdx.y;
	if((CUDA_i<=i)&&(i<(CUDA_i+3))&&(i<CUDA_U_i)){
	if((CUDA_j<=j)&&(j<(CUDA_j+4))&&(j<CUDA_U_j)){
		XP1[i*_SZ_XP1_1+j]=XP1[(i+3)*_SZ_XP1_1+j+4]+XS3[i];
}}}

