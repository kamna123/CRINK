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
    int a[20],i,j,k;
    int n=20;
    for(i=0;i<20;i++)
    {
        a[i]=2*i;
    }
    clock_gettime(CLOCK_MONOTONIC, &start);
    // PARALLELIZE IN CUDA START
    for(i=18;i>0;i--)
    {
       a[i+1]=a[i-1];
       //y[2*i-3][3*j-5]=x[i][j];
       //x[3*i-2][2*j-4]=y[i][j];
     } 
    // PARALLELIZE IN CUDA END
    clock_gettime(CLOCK_MONOTONIC, &end);
	pre_time = (double) ((((&mid_start)->tv_sec * 1000000000) + (&mid_start)->tv_nsec) - (((&start)->tv_sec * 1000000000) + (&start)->tv_nsec)) / 1000000000;
	post_time = (double) ((((&end)->tv_sec * 1000000000) + (&end)->tv_nsec) - (((&mid_end)->tv_sec * 1000000000) + (&mid_end)->tv_nsec)) / 1000000000;
	computeTime = (double) ((((&mid_end)->tv_sec * 1000000000) + (&mid_end)->tv_nsec) - (((&mid_start)->tv_sec * 1000000000) + (&mid_start)->tv_nsec)) / 1000000000;
	
	runTime = (double) ((((&end)->tv_sec * 1000000000) + (&end)->tv_nsec) - (((&start)->tv_sec * 1000000000) + (&start)->tv_nsec)) / 1000000000;
	printf("********************************\n");
	fprintf(fp,"%d,%d,%d,%.14f,%.14f,%.14f,%.14f,%d\n",N,_NTHREAD*_NBLOCK,data,pre_time,computeTime,post_time,runTime,_CUDA_TILE);
	//fprintf(fp,"%d,%d,%.14f\n",N_EDGES,data,runTime);
	//fclose(fp);
	printf("RUN TIME: %.14f\n", runTime);

	fclose(fp);
	fclose(f);
    return 0;
}

