#ifndef MATRIX_H
#define MATRIX_H

#include "vector.h"

typedef struct matrix_3x3 matrix_3x3;

struct matrix_3x3
{
	int x1, y1, z1;
	int x2, y2, z2;
	int x3, y3, z3;
};

vec_3d matrix_muliply(matrix_3x3 *m1, vec_3d *v1);

#endif
