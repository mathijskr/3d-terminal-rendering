#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdbool.h>

#include "termbox.h"

#include "cube.h"
#include "vector.h"
#include "matrix.h"

void drawCube(matrix_3x3 *proj);
void drawCubeSides(matrix_3x3 *proj);

void draw3d(vec_3d point, matrix_3x3 *proj, char c);
void drawLine(vec_3d point1, vec_3d point2, matrix_3x3 *proj);

void drawBackground();

int cmp_float(float *f1, float *f2);
void swap(float *i1, float *i2);

#define BACKGROUND_COLOR TB_BLACK

#endif
