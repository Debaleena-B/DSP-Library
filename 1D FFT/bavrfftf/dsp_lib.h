#ifndef __DSP_LIB_H__
#define	__DSP_LIB_H__

#define SUCCESS 0
#define FAILURE -1
#define PI 3.14159265

typedef struct{
	float real;
	float im;
}CV_COMPLEX;

typedef struct{
	CV_COMPLEX *cplx_arr;
	CV_COMPLEX *real_arr;
	long c_size;
	long r_size;
}fft_vector;

extern int bavfftwts(long **p, long m, long n);
#endif
