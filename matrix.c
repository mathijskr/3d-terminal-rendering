#include "headers/matrix.h"

vec_3d matrix_muliply(matrix_3x3 *m1, vec_3d *v1)
{
	vec_3d result = { 
		m1->x1 * v1->x + m1->y1 * v1->y + m1->z1 * v1->z,
		m1->x2 * v1->x + m1->y2 * v1->y + m1->z2 * v1->z,
		m1->x3 * v1->x + m1->y3 * v1->y + m1->z3 * v1->z,
	};

	return result;
}
