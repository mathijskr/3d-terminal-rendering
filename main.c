#include "main.h"

#define DIMENSIONS 3


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
	
	/* Quit loop if exit is true. */
	while(!EXIT){
		tb_clear();

		/* Draw the background. */
		for(int x = 0; x < tb_width(); x++){
			for(int y = 0; y < tb_height(); y++){
				tb_change_cell(x, y, ' ', BACKGROUND_COLOR,
				BACKGROUND_COLOR);
			}
		}

		/* Draw cube points. */
		for(int i = 0; i < CUBE_SIZE; i += DIMENSIONS) {
			int x = cube.points[i]; int y = cube.points[i + 1]; int z = cube.points[i + 2];
			vec_3d point = {x, y, z};
			draw3d(point, '.');
		}

		for(int i = 0; i < CUBE_CONNECTIONS_SIZE; i+=2) {
			int index1 = cube.connections[i] * DIMENSIONS;
			int index2 = cube.connections[i + 1] * DIMENSIONS;
			int x1 = cube.points[index1]; int y1 = cube.points[index1 + 1]; int z1 = cube.points[index1 + 2];
			int x2 = cube.points[index2]; int y2 = cube.points[index2 + 1]; int z2 = cube.points[index2 + 2];

			vec_3d point1 = {x1, y1, z1};
			vec_3d point2 = {x2, y2, z2};

			/* Draw cube skeleton. */
			drawLine(point1, point2);
		}

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

void draw3d(vec_3d point, char c)
{
	tb_change_cell(point.x + 2 * point.z, tb_height() - (20 + (point.y + point.z)), c, TB_GREEN, BACKGROUND_COLOR);
}

void drawLine(vec_3d point1, vec_3d point2)
{
	if(point2.x < point1.x)
		swap(&point2.x, &point1.x);

	if(point2.y < point1.y)
		swap(&point2.y, &point1.y);

	if(point2.z < point1.z)
		swap(&point2.z, &point1.z);

	if(point2.z == point1.z) {
		if(point2.x == point1.x) {
			/* Draw line between two y coordinates at the same x and z coordinates. */
			for(int line_y = point1.y + 1; line_y < point2.y; line_y++) {
				vec_3d point = {point1.x, line_y, point1.z};
				draw3d(point, '|');
			}
		} else if(point2.y == point1.y) {
			/* Draw line between two x coordinates at the same y and z coordinates. */
			for(int line_x = point1.x + 1; line_x < point2.x; line_x++) {
				vec_3d point = {line_x, point1.y, point1.z};
				draw3d(point, '-');
			}
		}
	} else {
		if(point2.x == point1.x && point2.y == point1.y) {
			/* Draw line between two z coordinates at the same x and y coordinates. */
			for(int line_z = point1.z + 1; line_z < point2.z; line_z++) {
				vec_3d point = {point1.x, point1.y, line_z};
				draw3d(point, '-');
			}
		}
	}
}

void swap(int *i1, int *i2)
{
	int temp = *i1;
	*i1 = *i2;
	*i2 = temp;
}
