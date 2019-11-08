#include "headers/matrix.h"

vec_3d multiply_matrix_3x3_vec3(matrix_3x3 *m1, vec_3d *v1)
{
	vec_3d result = { 
		m1->x1 * v1->x + m1->y1 * v1->y + m1->z1 * v1->z,
		m1->x2 * v1->x + m1->y2 * v1->y + m1->z2 * v1->z,
		m1->x3 * v1->x + m1->y3 * v1->y + m1->z3 * v1->z,
	};

	return result;
}

matrix_3x3 multiply_matrix_3x3_3x3(matrix_3x3 *m1, matrix_3x3 *m2)
{
	matrix_3x3 result = {
		m1->x1 * m2->x1 + m1->y1 * m2->x2 + m1->z1 * m2->x3, m1->x1 * m2->y1 + m1->y1 * m2->y2 + m1->z1 * m2->y3, m1->x1 * m2->z1 + m1->y1 * m2->z2 + m1->z1 * m2->z3,
		m1->x2 * m2->x1 + m1->y2 * m2->x2 + m1->z2 * m2->x3, m1->x2 * m2->y1 + m1->y2 * m2->y2 + m1->z2 * m2->y3, m1->x2 * m2->z1 + m1->y2 * m2->z2 + m1->z2 * m2->z3,
		m1->x3 * m2->x1 + m1->y3 * m2->x2 + m1->z3 * m2->x3, m1->x3 * m2->y1 + m1->y3 * m2->y2 + m1->z3 * m2->y3, m1->x3 * m2->z1 + m1->y3 * m2->z2 + m1->z3 * m2->z3
	};

	return result;
}

matrix_3x3 multiply_matrix_3x3_scalar(matrix_3x3 *m, float scalar)
{
	matrix_3x3 result = {
		m->x1 * scalar, m->y1 * scalar, m->z1 * scalar,
		m->x2 * scalar, m->y2 * scalar, m->z2 * scalar,
		m->x3 * scalar, m->y3 * scalar, m->z3 * scalar
	};

	return result;
}

matrix_3x3 rotate_matrix(float angle)
{
	float cos_angle = cos(angle);
	float sin_angle = sin(angle);

	matrix_3x3 result = {
		cos_angle, -sin_angle, 0.0f,
		sin_angle, cos_angle, 0.0f,
		0.0f, 0.0f, 1.0f
	};

	return result;
}
