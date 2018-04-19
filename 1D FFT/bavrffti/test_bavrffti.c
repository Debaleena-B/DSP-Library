#include <stdio.h>
#include <math.h>
#include "dsp_lib.h"
#include <stdlib.h>
#include "error.h"
//#include <timexLib.h>

int main(void)
{
	FILE *inputFd, *outputFd;

	int err;
	long *vin;
	float *inp, *outp;
	/*	fft_vector *vin;*/
	int i = 0;

	inp = (float*)calloc(64*1024*2, sizeof(float));
	outp = (float*)calloc(64*1024, sizeof(float));

	inputFd = fopen("bavrfftf_out_new.txt", "r");

	for (i = 0; i < 128*1024; i++)
	{
		fscanf(inputFd, "%f", ((float*)inp+i));
		fseek(inputFd, 1, SEEK_CUR);		
	}
	fclose(inputFd);

	for (i = 0; i < 8; i++)
	{
		printf("inp[%d].re = %f\n", i, inp[i]);
	}
	bavfftwts(&vin, 64*1024, 0);
	
	for (i = 0; i < 8; i++)
	{
		printf("W[%d] = %f\n", i, ((fft_vector*)vin)->cplx_arr[i].real);
		printf("W[%d] = %f\n", i, ((fft_vector*)vin)->cplx_arr[i].im); 
	}

	bavcffti(inp, 2, outp, 1, 64*1024, vin);

	//rearrange_fft(inp, 64*1024);

	outputFd = fopen("fft_gap_ip.txt", "w+");
	for (i = 0; i < 64*1024; i++)
	{
		fprintf(outputFd, "%f\n", *((float*)outp+i));
	}
	fclose(outputFd);

	for (i = 0; i < 16; i++)
	{
		printf("inp[%d].re = %f\n", i, outp[i]);
	}
	
	free(((fft_vector*)vin)->real_arr);
	free(((fft_vector*)vin)->cplx_arr);
	free((fft_vector*)vin);
	exit(0);

}

