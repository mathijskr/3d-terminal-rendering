#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdbool.h>

#include "termbox.h"

#include "cube.h"
#include "vector.h"
#include "matrix.h"

void drawCube(matrix_3x3 *trans, float *points, int points_size, int *connections, int connections_size);
void drawCubeSides(matrix_3x3 *trans, float *points, int points_size, int *connections, int connections_size);

void draw3d(vec_3d point, matrix_3x3 *trans, char c);
void drawLine(vec_3d point1, vec_3d point2, matrix_3x3 *trans);

void drawText(int x, int y, char *text, int text_size, int color, int back_color);
void drawBackground();

int cmp_float(float *f1, float *f2);
void swap(float *i1, float *i2);

#define BACKGROUND_COLOR TB_BLACK

#define CONTROL_ROTATE_X 'x'
#define CONTROL_ROTATE_Y 'y'
#define CONTROL_ROTATE_Z 'z'

#define CONTROL_INC_SIZE '+'
#define CONTROL_DEC_SIZE '-'

#endif
