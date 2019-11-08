#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <math.h>

#include "vector.h"

typedef struct matrix_3x3 matrix_3x3;

struct matrix_3x3
{
	float x1, y1, z1;
	float x2, y2, z2;
	float x3, y3, z3;
};

vec_3d multiply_matrix_3x3_vec3(matrix_3x3 *m1, vec_3d *v1);
matrix_3x3 multiply_matrix_3x3_3x3(matrix_3x3 *m1, matrix_3x3 *m2);
matrix_3x3 multiply_matrix_3x3_scalar(matrix_3x3 *m, float scalar);

matrix_3x3 rotate_x_matrix(float angle);
matrix_3x3 rotate_y_matrix(float angle);
matrix_3x3 rotate_z_matrix(float angle);

#endif
