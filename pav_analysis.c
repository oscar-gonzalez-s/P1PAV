#include <math.h>
#include "pav_analysis.h"

double PI = 3.14159265358979323846;

float compute_power(const float *x, unsigned int N) {
  float inc = 0;

  for (int n=0; n<N; n++) {
    inc += x[n]*x[n];
  }

  return 10*log10(inc/N);
}

float compute_windowed_power(const float *x, unsigned int N, unsigned int fm) {
  float Tlong = fm * 0.02;
  float Tdes = fm * 0.01;
  float inc = 0,  w = 0;
  int count = 0, start = 0, n = 0;

  while (n < N) {
    start = count * Tdes;
    
    for (n = start; n < (start + Tlong); n++) {
      w = Hamming(n - start, Tlong);
      if (w && n < N) {
        inc += (x[n]*w)*(x[n]*w)/(w*w);
      }
    }
    count++;
  }
  
  return 10*log10(inc);
}

float Hamming(int n, int N) {
  if (n >= 0 && n < N) {
    return 0.54 - 0.46 * cos((2*PI*n)/(N-1));
  }
  return 0;
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
    if (x[n]*x[n-1] < 0 || (x[n] == 0 && x[n-1] != 0))
      inc++;
  }

  return (fm/2)*inc/(N-1);
}