#include <altivec.h>
#include <stdio.h>
#include <stdlib.h>
#include "dsp_lib.h"

int av_fft_dif( vector float *pvf, vector float *pw, unsigned int n, unsigned int log_n );

int _bavfftwts_vec()
{                    
	vector float *twiddle;
	vector float *inp;
	long *vin;

	int i;
	fft_vector *fft;

	bavfftwts(&vin, 16, 0);

	for (i = 0; i < 16; i++)
	{
		printf("W[%d] = %f\n", i, ((fft_vector*)vin)->cplx_arr[i].real);
		printf("W[%d] = %f\n", i, ((fft_vector*)vin)->cplx_arr[i].im); 
	}

	float inp_f[32] = {2.1, 0, 3.0, 2.1, 1.3, 2.1, 4.2, 3.4, 0.9, 2.1, 3.2, 0.1, 1.0, 1.1, 2.3, 0.2, \
			12.1, 10, 13.0, 12.1, 11.3, 12.1, 14.2, 13.4, 10.9, 12.1, 13.2, 10.1, 11.0, 11.1, 12.3, 10.2};

	inp = (vector float*)vec_calloc(8, sizeof(vector float));
	inp[0] = (vector float){2.1, 0, 3.0, 2.1};
	inp[1] = (vector float){1.3, 2.1, 4.2, 3.4};
	inp[2] = (vector float){0.9, 2.1, 3.2, 0.1};
	inp[3] = (vector float){1.0, 1.1, 2.3, 0.2};
	inp[4] = (vector float){12.1, 10, 13.0, 12.1};
	inp[5] = (vector float){11.3, 12.1, 14.2, 13.4};
	inp[6] = (vector float){10.9, 12.1, 13.2, 10.1};
	inp[7] = (vector float){11.0, 11.1, 12.3, 10.2};

        float twiddle_f[32] = {1.000000, 0.000000, 0.923880, -0.382683, 0.707107, -0.707107, 0.382683, -0.923880, 0.000000, -1.000000, -0.382683, 
			-0.923880, -0.707107, -0.707107, -0.923880, -0.382683, -1.000000, 0.000000, -0.923880, 0.382683, -0.707107, 0.707107, 
			-0.382683, 0.923880, 0.000000, 1.000000, 0.382683, 0.923880, 0.707107, 0.707107, 0.923880, 0.382683}; 

	twiddle = (vector float*)vec_calloc(2, sizeof(vector float));
	twiddle[0] = (vector float){1, 0, 0.923880, -0.382683};
	twiddle[1] = (vector float){0.707107, -0.707107, 0.382683, -0.923880};
	/*
	timexInit();

	timexClear(); 1 output

	timex((FUNCPTR )av_fft_dif, (int)inp, (int)twiddle, 16, 4, 0, 0, 0, 0); 1 output
	 */

	/*	timexN(0, 0, 0, 0, 0, 0, 0, 0, 0);*/

	/*	av_fft_dif( (vector float *)inp_f, (vector float *)twiddle_f, 16, 4 );*/

	/*	bavcfftf( inp_f, 2, inp_f, 2, 16, vin);*/


	/*	av_fft_dif( inp, twiddle, 16, 4 );*/

	for (i = 0 ; i < 32; i++)
	{
		printf ("fft[%d] = %f\n", i, ((float *)inp)[i]);
	}

}

int main_bavcfftf(void)
{
	FILE *inputFd, *outputFd;

	int err;
	long *vin;
	float *inp, *outp;
	/*	fft_vector *vin;*/
	int i = 0;
	unsigned long startTime, endTime;
	float totalTime;

	printf("Start bmit2");
	inp =  (float*)calloc(64*1024*2, sizeof(float));
	outp = (float*)calloc(64*1024*2, sizeof(float));
	

	inputFd = fopen("input5_128.txt", "r");

	for (i = 0; i < 64*1024; i++)
	{
		fscanf(inputFd, "%f", ((float*)inp+i));
		fseek(inputFd, 1, SEEK_CUR);		
	}
	fclose(inputFd);

	for (i = 0; i < 8; i++)
	{
		printf("inp[%d] = %f\n", i, inp[i]);
	}
	
	printf("1\n");
	startTime = getTimebase();
	bavfftwts(&vin, 64*1024, 0);
	endTime = getTimebase();

	totalTime = ((endTime - startTime) / ((sysGetBusSpd()/4.0)*1000000));
	printf("totalTime for awts is %f sec\n", totalTime );
	
	for (i = 0; i < 8; i++)
	{
		printf("W[%d] = %f\n", i, ((fft_vector*)vin)->cplx_arr[i].real);
		printf("W[%d] = %f\n", i, ((fft_vector*)vin)->cplx_arr[i].im); 
	}

	 printf("\n");
	 
	startTime = getTimebase();
	
/*
	timexFunc(0, bavcfftf, inp, 2, inp, 2, 64*1024, vin, 0, 0);
		
	timexN(0, 0, 0, 0, 0, 0, 0, 0, 0);
*/
/*
	bavcfftf(inp, 2, outp, 2, 64*1024, vin);
	bavcfftf_C( inp, 2, inp, 2, 64*1024, vin);
*/
	bavrfftf(inp, 1, outp, 2, 64*1024, vin);

	endTime = getTimebase();

	totalTime = ((endTime - startTime) / ((sysGetBusSpd()/4.0)*1000000));
	printf("totalTime for fft is %f sec\n", totalTime );
	
	 printf("\n");
		
	rearrange_fft(inp, 64*1024);

	outputFd = fopen("bavrfftf_out_new.txt", "w+");
	for (i = 0; i < 64*1024; i++)
	{
		fprintf(outputFd, "%f\n", *((float*)inp+i));
	}
	fclose(outputFd);

	for (i = 0; i < 8; i++)
	{
		printf("inp[%d].re = %f\n", i, inp[i]);
	}
	printf("End bmit2");
	free(((fft_vector*)vin)->real_arr);
	free(((fft_vector*)vin)->cplx_arr);
	free((fft_vector*)vin);
	exit(0);

}

int av_fft_dif( vector float *pvf, vector float *pw, unsigned int n, unsigned int log_n )
{
	const vector float vcfzero = (vector float){ 0., 0., 0., 0.};
	const vector float vcfnegeven = (vector float){-0., 0.,-0., 0.};
	const vector float vcfnegodd = (vector float){ 0.,-0., 0.,-0.};
	const vector float vcppnn = (vector float){ 1., 1.,-1.,-1.};
	const vector float vcpnnp = (vector float){ 1.,-1.,-1., 1.};
	const vector unsigned char vcprm1032 = (vector unsigned char){ 4,5,6,7, 0,1,2,3, 12,13,14,15, 8,9,10,11 };
	const vector unsigned char vcprm0022 = (vector unsigned char){ 0,1,2,3, 0,1,2,3, 8,9,10,11, 8,9,10,11 };
	const vector unsigned char vcprm1133 = (vector unsigned char){ 4,5,6,7, 4,5,6,7, 12,13,14,15, 12,13,14,15 };
	const vector unsigned char vcprm2301 = (vector unsigned char){ 8,9,10,11,12,13,14,15, 0,1,2,3,4,5,6,7 };
	const vector unsigned char vcprm0101 = (vector unsigned char){ 0,1,2,3,4,5,6,7, 0,1,2,3,4,5,6,7 };
	const vector unsigned char vcprm3232 = (vector unsigned char){ 12,13,14,15,8,9,10,11, 12,13,14,15,8,9,10,11 };
	const vector unsigned char vcaiarbibr = (vector unsigned char){ 4,5,6,7, 0,1,2,3, 20,21,22,23, 16,17,18,19 };
	const vector unsigned char vcaraibrbi = (vector unsigned char){ 0,1,2,3,4,5,6,7, 16,17,18,19,20,21,22,23 };
	vector float vtf10,vtf11,vtf12,vtf13,vtf14,vtf15,
	vtf20,vtf21,vtf22,vtf23,vtf24,vtf25,
	vtf31,vtf32,vtf33,vtf34,vtf35,
	vtf41,vtf42,vtf43,vtf44,vtf45,
	vtfw0,vtfw1,vtfw2,vtfw3;
	unsigned int pa,pb,qa,qb,stride,edirts,iw;
	unsigned int stage,block,j; 
	stride = n/2; /* in stage 0 stride = n/2 */
	for( j=0; j<stride/4; j++ ) {
		vtfw1 = vec_perm( pw[j], pw[j], vcprm1032 );
		vtfw2 = vec_xor( vtfw1, vcfnegeven );
		vtfw3 = vec_xor( vtfw1, vcfnegodd );
		vtf10 = vec_add( pvf[j], pvf[n/4+j] );
		vtf11 = vec_sub( pvf[j], pvf[n/4+j] );
		pvf[j] = vtf10;
		vtf20 = vec_add( pvf[n/8+j], pvf[n/8+n/4+j] );
		vtf21 = vec_sub( pvf[n/8+j], pvf[n/8+n/4+j] );
		pvf[n/8+j] = vtf20;
		vtf12 = vec_perm( vtf11, vtf11, vcprm0022 );
		vtf12 = vec_madd( vtf12, pw[j], vcfzero );
		vtf13 = vec_perm( vtf11, vtf11, vcprm1133 );
		pvf[n/4+j] = vec_madd( vtfw2, vtf13, vtf12 );
		vtf22 = vec_perm( vtf21, vtf21, vcprm1133 );
		vtf22 = vec_madd( vtf22, pw[j], vcfzero ); 
		vtf23 = vec_perm( vtf21, vtf21, vcprm0022 ); 
		pvf[n/4+n/8+j] = vec_madd( vtfw3, vtf23, vtf22 );
	}
	stride = n/4; /* in stage 1 stride = n/4 */
	edirts = 1;
	for( stage=1; stage<log_n-2; stage++ ) {
		for( block=0; block<n/2; block+=stride ) {
			pa = block;
			pb = block + stride/4;
			qa = block + stride/2;
			qb = block + stride/4 + stride/2;
			iw = 0;
			for( j=0; j<stride/4; j++ ) {
				vtfw0 = vec_perm( pw[j*2*edirts],
						pw[j*2*edirts+edirts],
						vcaraibrbi );
				vtfw1 = vec_perm( pw[j*2*edirts],
						pw[j*2*edirts+edirts],
						vcaiarbibr );
				vtfw2 = vec_xor( vtfw1, vcfnegeven );
				vtfw3 = vec_xor( vtfw1, vcfnegodd );
				vtf10 = vec_add( pvf[pa+j], pvf[qa+j] );
				vtf11 = vec_sub( pvf[pa+j], pvf[qa+j] );
				pvf[pa+j] = vtf10;
				vtf20 = vec_add( pvf[pb+j], pvf[qb+j] );
				vtf21 = vec_sub( pvf[pb+j], pvf[qb+j] );
				pvf[pb+j] = vtf20;
				vtf12 = vec_perm( vtf11, vtf11, vcprm0022 );
				vtf12 = vec_madd( vtf12, vtfw0, vcfzero );
				vtf13 = vec_perm( vtf11, vtf11, vcprm1133 );
				pvf[qa+j] = vec_madd( vtfw2, vtf13, vtf12 );
				vtf22 = vec_perm( vtf21, vtf21, vcprm1133 );
				vtf22 = vec_madd( vtf22, vtfw0, vcfzero ); 
				vtf23 = vec_perm( vtf21, vtf21, vcprm0022 ); 
				pvf[qb+j] = vec_madd( vtfw3, vtf23, vtf22 ); 
			}

		}
		stride = stride >> 1;
		edirts = edirts << 1;
	}
	for( block=0; block<n/2; block+=8 ) { 
		vtf13 = vec_sub( pvf[block ], pvf[block+1] );
		vtf11 = vec_add( pvf[block ], pvf[block+1] );
		vtf23 = vec_sub( pvf[block+2], pvf[block+3] );
		vtf21 = vec_add( pvf[block+2], pvf[block+3] );

		/*This block makes sure N > 8 or at least 16*/
		vtf33 = vec_sub( pvf[block+4], pvf[block+5] );
		vtf31 = vec_add( pvf[block+4], pvf[block+5] );
		vtf43 = vec_sub( pvf[block+6], pvf[block+7] );
		vtf41 = vec_add( pvf[block+6], pvf[block+7] );
		/*This block makes sure N > 8 or at least 16*/

		vtf15 = vec_perm( vtf13, vtf13, vcprm3232 );
		vtf14 = vec_perm( vtf13, vtf13, vcprm0101 );
		vtf12 = vec_perm( vtf11, vtf11, vcprm2301 );
		vtf25 = vec_perm( vtf23, vtf23, vcprm3232 );
		vtf24 = vec_perm( vtf23, vtf23, vcprm0101 );
		vtf22 = vec_perm( vtf21, vtf21, vcprm2301 );

		/*This block corresponding to the blocks which make sure N is atleat 16*/
		vtf35 = vec_perm( vtf33, vtf33, vcprm3232 );
		vtf34 = vec_perm( vtf33, vtf33, vcprm0101 );
		vtf32 = vec_perm( vtf31, vtf31, vcprm2301 );
		vtf45 = vec_perm( vtf43, vtf43, vcprm3232 );
		vtf44 = vec_perm( vtf43, vtf43, vcprm0101 );
		vtf42 = vec_perm( vtf41, vtf41, vcprm2301 );
		/*This block corresponding to the blocks which make sure N is atleat 16*/

		pvf[block] = vec_madd( vtf11, vcppnn, vtf12 );
		pvf[block+1] = vec_madd( vtf15, vcpnnp, vtf14 );
		pvf[block+2] = vec_madd( vtf21, vcppnn, vtf22 );
		pvf[block+3] = vec_madd( vtf25, vcpnnp, vtf24 );

		/*This block corresponding to the blocks which make sure N is atleat 16*/
		pvf[block+4] = vec_madd( vtf31, vcppnn, vtf32 );
		pvf[block+5] = vec_madd( vtf35, vcpnnp, vtf34 );
		pvf[block+6] = vec_madd( vtf41, vcppnn, vtf42 );
		pvf[block+7] = vec_madd( vtf45, vcpnnp, vtf44 );
		/*This block corresponding to the blocks which make sure N is atleat 16*/

	}
	return 0;
}
