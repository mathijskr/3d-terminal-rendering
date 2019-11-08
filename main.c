#include "main.h"

#define DIMENSIONS 3

int screen_ratio = 1.0f;


int main(int argv, char **argc)
{
	int code = tb_init();

	/* Check if termbox was initialized. */
	if(code < 0) {
		fprintf(stderr, "termbox init failed, code: %d\n", code);
		return -1;
	}

	tb_select_input_mode(TB_INPUT_ESC);
	tb_select_output_mode(TB_OUTPUT_NORMAL);
	tb_clear();

	struct tb_event ev;

	bool EXIT = false;

	matrix_3x3 proj = {	
			1.0f, 0.0f, 1.0f,
			0.0f, 1.0f, 1.0f,
			0.0f, 0.0f, 0.0f
	};

	
	/* Quit loop if exit is true. */
	while(!EXIT){
		tb_clear();
	
		drawBackground();
		drawCube(&proj);	

		/* Draw to screen. */
		tb_present();

		/* Update input with a timeout of n ms. */
		int input = tb_peek_event(&ev, 0);

		if(input == TB_INPUT_ESC)
			EXIT = true;
	}

	tb_shutdown();
	return 0;
}

void drawCube(matrix_3x3 *proj)
{
	/* Draw cube points. */
	for(int i = 0; i < CUBE_SIZE; i += DIMENSIONS) {
		int x = cube.points[i]; int y = cube.points[i + 1]; int z = cube.points[i + 2];
		vec_3d point = {x, y, z};
		draw3d(point, proj, '.');
	}

	drawCubeSides(proj);
}

void drawCubeSides(matrix_3x3 *proj)
{
	for(int i = 0; i < CUBE_CONNECTIONS_SIZE; i+=2) {
		int index1 = cube.connections[i] * DIMENSIONS;
		int index2 = cube.connections[i + 1] * DIMENSIONS;

		vec_3d point1 = { cube.points[index1], cube.points[index1 + 1], cube.points[index1 + 2] };
		vec_3d point2 = { cube.points[index2], cube.points[index2 + 1], cube.points[index2 + 2] };

		/* Draw cube skeleton. */
		drawLine(point1, point2, proj);
	}
}

void draw3d(vec_3d point, matrix_3x3 *proj, char c)
{
	vec_3d point_proj = matrix_muliply(proj, &point);

	tb_change_cell(point_proj.x, tb_height() - screen_ratio * (20.0f + point_proj.y), c, TB_GREEN, BACKGROUND_COLOR);
}

void drawLine(vec_3d point1, vec_3d point2, matrix_3x3 *proj)
{
	if(point2.x < point1.x)
		swap(&point2.x, &point1.x);

	if(point2.y < point1.y)
		swap(&point2.y, &point1.y);

	if(point2.z < point1.z)
		swap(&point2.z, &point1.z);

	if(cmp_float(&point2.z, &point1.z) == 0) {
		if(cmp_float(&point2.x, &point1.x) == 0) {
			/* Draw line between two y coordinates at the same x and z coordinates. */
			for(int line_y = point1.y + 1; line_y < point2.y; line_y++) {
				vec_3d point = {point1.x, line_y, point1.z};
				draw3d(point, proj, '|');
			}
		} else if(cmp_float(&point2.y, &point1.y) == 0) {
			/* Draw line between two x coordinates at the same y and z coordinates. */
			for(int line_x = point1.x + 1; line_x < point2.x; line_x++) {
				vec_3d point = {line_x, point1.y, point1.z};
				draw3d(point, proj, '-');
			}
		}
	} else {
		if(cmp_float(&point2.x, &point1.x) == 0 && cmp_float(&point2.y, &point1.y) == 0) {
			/* Draw line between two z coordinates at the same x and y coordinates. */
			for(int line_z = point1.z + 1; line_z < point2.z; line_z++) {
				vec_3d point = {point1.x, point1.y, line_z};
				draw3d(point, proj, '-');
			}
		}
	}
}

void drawBackground()
{
	for(int x = 0; x < tb_width(); x++){
		for(int y = 0; y < tb_height(); y++){
			tb_change_cell(x, y, ' ', BACKGROUND_COLOR,
			BACKGROUND_COLOR);
		}
	}
}

int cmp_float(float *f1, float *f2)
{
	float margin = 0.001f;

	if((*f1 - *f2) * (*f1 - *f2) < margin * margin)
		return 0;
	else
		return 1;
}

void swap(float *i1, float *i2)
{
	float temp = *i1;
	*i1 = *i2;
	*i2 = temp;
}
