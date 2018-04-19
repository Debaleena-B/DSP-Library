#include <stdio.h>
#include <stdlib.h>
#include "error.h"
#include "dsp_lib.h"
#include <math.h>
void main(void)
{

	float *rvin1, *rvout1;
	int err;
	int i;
	FILE *inputFd, *outputFd;
    	float myvariable;
   	int  openFlags;

	printf("Start bhlbrt\n");

	rvin1 = (float*)calloc(64*1024, sizeof(float));
	
	rvout1 = (float*)calloc(64*1024, sizeof(float));
	
	/*inputFd = fopen("/home/snehal/snehal/phase-2/bblkman_bench_file/input15_64.txt", "r");
	for (i = 0; i < 64*1024; i++)
	{
		fscanf(inputFd, "%f", ((float*)rvin1+i));
		fseek(inputFd, 1, SEEK_CUR);		
	}
	fclose(inputFd);*/
	
	for(i = 0; i < 8; i++)
	{	
		rvin1[i] = i + 1;
	}

	for (i = 0; i < 8; i++)
	{
		printf("vector[%d]=%f\n", i, rvin1[i]);
	}
	
	err = benvel(rvin1, rvout1, 8);

	outputFd = fopen("bhlbrt_output.txt", "w+");

	for (i = 0;i < 8; i++)
	{
		fprintf(outputFd, "%f\n", *((float*)rvout1+i));
		
	}
	fclose(outputFd);
				
	for (i = 0; i < 8; i++)

	{
		printf("vector[%d]=%f\n", i, rvout1[i]);
	}

	free(rvin1);

	free(rvout1);

	printf("bhlbrt\n");

}
