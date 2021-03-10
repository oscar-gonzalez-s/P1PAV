#ifndef PAV_ANALYSIS_H
#define PAV_ANALYSIS_H

float compute_power(const float *x, unsigned int N);
float compute_windowed_power(const float *x, unsigned int N, unsigned int fm);
float Hamming(int n, int N);
float compute_am(const float *x, unsigned int N);
float compute_zcr(const float *x, unsigned int N, float fm);

#endif          /* PAV_ANALYSIS_H       */