#ifndef MATRIX_H
#define MATRIX_H

#include "vector.h"

typedef struct matrix_3x3 matrix_3x3;

struct matrix_3x3
{
	float x1, y1, z1;
	float x2, y2, z2;
	float x3, y3, z3;
};

vec_3d matrix_muliply(matrix_3x3 *m1, vec_3d *v1);

#endif
