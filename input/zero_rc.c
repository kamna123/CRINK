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

