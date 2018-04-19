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
extern int bhlbrt(float *rv1, float *rvo, long n);
extern void swap_2(float *in_2, int n_2);
extern int bavrfftf( float *cv1, long inc1, float *cout, long inco, long n, long *p);
extern void swap(CV_COMPLEX *in, CV_COMPLEX *out);
extern unsigned int reverseBits(unsigned int num, unsigned int n);
extern int rearrange_fft( float *inp, unsigned int n);
extern int bavfftwts(long **p, long m, long n);
extern int bavrffti( float *cv1, long inc1, float *cout, long inco, long n, long *p);
extern int bavfreewts(long **p);
extern int benvel(float *rv1, float *rvo, long n);
