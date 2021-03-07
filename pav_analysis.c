#include <math.h>
#include "pav_analysis.h"

float compute_power(const float *x, unsigned int N) {
    float inc = 0;

    for (int n=0; n<N; n++) {
        inc += x[n]*x[n];
    }
    
    float power = 10*log10((1/N)*inc);

    return power;
}

float compute_am(const float *x, unsigned int N) {
    float am = 0;

    for (int n=0; n<N; n++) {
        am += fabs(x[n]);
    }

    return am/N;
}

float compute_zcr(const float *x, unsigned int N, float fm) {
    float inc = 0;

    for (int n=1; n<N; n++) {
        if ((x[n]>0 && x[n-1]<0 || x[n]>0 && x[n-1]<0)){
            inc++;
        }
    }

    float zcr = (fm/2)*(1/(N-1))*inc;
    return zcr;
}