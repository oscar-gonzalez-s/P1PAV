#include <stdio.h>
#include "fic_wave.h"
#include <string.h>
#include <errno.h>

FILE *abre_wave(const char *ficWave, float *fm)
{
  FILE *fpWave;

  if ((fpWave = fopen(ficWave, "r")) == NULL)
    return NULL;
  if (fseek(fpWave, 44, SEEK_SET) < 0)
    return NULL;

  int nChannels;
  fseek(fpWave, 22, SEEK_SET);
  fread(&nChannels, 2, 1, fpWave);
  if (nChannels > 1)
  {
    printf("Error: Señal debe ser de un solo canal (mono)");
    return NULL;
  }

  int codif;
  fseek(fpWave, 16, SEEK_SET);
  fread(&codif, 4, 1, fpWave);
  if (codif != 16)
  {
    printf("Error: Señal no codificada con PCM Lineal de 16 bits");
    return NULL;
  }

  int frm;
  fseek(fpWave, 24, SEEK_SET);
  fread(&frm, 4, 1, fpWave);

  *fm = frm;

  return fpWave;
}

size_t lee_wave(void *x, size_t size, size_t nmemb, FILE *fpWave)
{
  return fread(x, size, nmemb, fpWave);
}

void cierra_wave(FILE *fpWave)
{
  fclose(fpWave);
}