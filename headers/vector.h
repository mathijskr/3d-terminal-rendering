#ifndef VECTOR_H
#define VECTOR_H

typedef struct vec_2d vec_2d;

struct vec_2d
{
	float x, y;
};

typedef struct vec_3d vec_3d;

struct vec_3d
{
	float x, y, z;
};

vec_3d vec_3d_add(vec_3d *vec1, vec_3d *vec2)
{
	vec_3d result = { vec1->x + vec2->x, vec1->y + vec2->y, vec1->z + vec2->z };
	return result;
}

#endif
