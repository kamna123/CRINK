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
    /*int XP1[20][20],XS3[20],i,j,k;
    for(i=0;i<20;i++)
    for(j=0;j<20;j++)
    {
        XP1[i][j]=i+j;
        XS3[i]=2*i;
    }*/
    // PARALLELIZE IN CUDA START
    for(i=1;i<=20;i++)
    for(j=1;j<=20;j++)
    {
        XP1[i][j] = XP1[i+3][j+4]+XS3[i];
        }
    // PARALLELIZE IN CUDA END
    return 0;
}

