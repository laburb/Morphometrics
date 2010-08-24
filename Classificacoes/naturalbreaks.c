/*
 * naturalbreaks.c
 *
 *  Created on: 23/08/2010
 *      Author: bruno
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#include "Header/naturalbreaks.h"

void getMinMax(double *data, int numdata, double *min, double *max) {
  int i;
  *min=DBL_MAX;
  *max=DBL_MIN;

  for (i=0; i<numdata ;i++) {
    if (*min > data[i])
      *min=data[i];
    if (*max < data[i])
      *max=data[i];
  }
}

//Baseado em uk.ac.leeds.ccg.geotools.classification.NaturalBreaks
int *NaturalBreaks(double *data,int numdata, int numclass) {
  int i,j,l,m;

  double **mat1=calloc(numdata + 1, sizeof(double *));
  double **mat2=calloc(numdata + 1, sizeof(double *));
  int *kclass=calloc(numclass, sizeof(int));

  for (i=0; i<numdata+1 ;i++) {
    mat1[i]=calloc(numclass+1, sizeof(double));
    mat2[i]=calloc(numclass+1, sizeof(double));
  }

  for (i = 1; i <= numclass; i++) {
      mat1[1][i] = 1;
      mat2[1][i] = 0;
      for (j = 2; j <= numdata; j++)
          mat2[j][i] = DBL_MAX;
  }

  double v = 0;
  for (l = 2; l <= numdata; l++) {
      double s1 = 0;
      double s2 = 0;
      double w = 0;
      for (m = 1; m <= l; m++) {
          int i3 = l - m + 1;
          double val = data[i3 -1];

          s2 += val * val;
          s1 += val;

          w++;
          v = s2 - (s1 * s1) / w;
          int i4 = i3 - 1;
          if (i4 != 0) {
              for (j = 2; j <= numclass; j++) {
                  if (mat2[l][j] >= (v + mat2[i4][j - 1])) {
                      mat1[l][j] = i3;
                      mat2[l][j] = v + mat2[i4][j - 1];
                  }
              }
          }
      }

      mat1[l][1] = 1;
      mat2[l][1] = v;
  }

  int k = numdata;

  kclass[numclass-1]=numdata-1;

  for (j = numclass; j >= 2; j--) {
    int id = (int) (mat1[k][j]) - 2;

    kclass[j - 2] = id;

    k = (int) mat1[k][j] - 1;
  }

  for (i=0; i<numdata+1 ;i++) {
    free(mat1[i]);
    free(mat2[i]);
  }

  free(mat1);
  free(mat2);

  return kclass;
}
