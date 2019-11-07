#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdbool.h>

#include "termbox.h"

#include "cube.h"

void draw3d(int x, int y, int z, char c);
void drawLine(int x, int y, int z, int next_x, int next_y, int next_z);

void swap(int *i1, int *i2);

#define BACKGROUND_COLOR TB_BLACK

#endif
