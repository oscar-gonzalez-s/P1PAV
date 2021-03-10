#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "pav_analysis.h"
#include "fic_wave.h"

int main(int argc, char *argv[]) {
  float durTrm = 0.010;
  float fm;
  int N;
  int trm;
  float *x;
  short *buffer;
  char *txtFileName;
  FILE *fpWave;
  FILE *tablaResultado;

  if (argc != 2 && argc != 3) {
    fprintf(stderr, "Empleo: %s inputfile [outputfile]\n", argv[0]);
    return -1;
  }

  if ((fpWave = abre_wave(argv[1], &fm)) == NULL) {
    fprintf(stderr, "Error al abrir %s (%s)\n", argv[1], strerror(errno));
    return -1;
  }

  N = durTrm * fm;
  if ((buffer = malloc(N * sizeof(*buffer))) == 0 || (x = malloc(N * sizeof(*x))) == 0) {
    fprintf(stderr, "Error al ubicar los vectores (%s)\n", strerror(errno));
    return -1;
  }

  txtFileName = argv[2];
  tablaResultado = fopen(txtFileName, "w");
  if (tablaResultado == NULL) {
    fprintf(stderr, "Error al abrir el archivo (%s)\n", strerror(errno));
    return -1;
  }

  trm = 0;
  while (lee_wave(buffer, sizeof(*buffer), N, fpWave) == N) {
    for (int n = 0; n < N; n++)
      x[n] = buffer[n] / (float)(1 << 15);
    printf("%d\t%f\t%f\t%f\n", trm, compute_windowed_power(x, N, fm), compute_am(x, N), compute_zcr(x, N, fm));
    fprintf(tablaResultado, "%d\t%f\t%f\t%f\n", trm, compute_windowed_power(x, N, fm), compute_am(x, N), compute_zcr(x, N, fm));
    trm += 1;
  }
  fclose(tablaResultado);
  cierra_wave(fpWave);
  free(buffer);
  free(x);

  return 0;
}