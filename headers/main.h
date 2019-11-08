#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdbool.h>

#include "termbox.h"

#include "cube.h"
#include "vector.h"
#include "matrix.h"

void drawCube();
void drawCubeSides();

void draw3d(vec_3d point, char c);
void drawLine(vec_3d point1, vec_3d point2);

void drawBackground();

void swap(int *i1, int *i2);

#define BACKGROUND_COLOR TB_BLACK

#endif
