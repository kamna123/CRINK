#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
    char *outfile;
    char readfile[5]="mtx";
    outfile = (char*)malloc(sizeof(char)*(strlen(readfile)+10));
	strcat(outfile, "in2_");
	strcat(outfile, readfile);
	strcat(outfile, ".data");
	printf("%s\n",outfile);
    return 0;
}
