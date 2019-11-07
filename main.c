#include "main.h"

#define DIMENSIONS 3

#define CUBE_SIZE 28
#define CUBE_CONNECTIONS_SIZE 24

void draw3d_on_2d(int x, int y, int z, char c);
void drawLine(int x, int y, int z, int next_x, int next_y, int next_z);

void swap(int *i1, int *i2);


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

	int cube[CUBE_SIZE] = {
	/*	x   y   z   */
		0,  0,  0,	/* Front side */
		20, 0,  0,
		20, 10, 0,
		0,  10, 0,

		0,  0,  5,	/* Back side */
		20, 0,  5,
		20, 10, 5,
		0,  10, 5,
	};

	int cube_connections[CUBE_CONNECTIONS_SIZE] = {
	/*	point1	point2	*/
		0,	1,	/* Front side */
		1,	2,
		2,	3,
		3,	0,

		4,	5,	/* Back side */	
		5, 	6,
		6,	7,
		7,	4,

		0,	4,	/* Connecting back and front */
		1,	5,
		2,	6,
		3,	7
	};

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
			int x = cube[i]; int y = cube[i + 1]; int z = cube[i + 2];
			draw3d_on_2d(x, y, z, '.');
		}

		for(int i = 0; i < CUBE_CONNECTIONS_SIZE; i+=2) {
			int index1 = cube_connections[i] * DIMENSIONS;
			int index2 = cube_connections[i + 1] * DIMENSIONS;
			int x1 = cube[index1]; int y1 = cube[index1 + 1]; int z1 = cube[index1 + 2];
			int x2 = cube[index2]; int y2 = cube[index2 + 1]; int z2 = cube[index2 + 2];

			/* Draw cube skeleton. */
			drawLine(x1, y1, z1, x2, y2, z2);
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

void draw3d_on_2d(int x, int y, int z, char c)
{
	tb_change_cell(x + 2 * z, tb_height() - (20 + (y + z)), c, TB_GREEN, BACKGROUND_COLOR);
}

void drawLine(int x, int y, int z, int next_x, int next_y, int next_z)
{
	if(next_x < x)
		swap(&next_x, &x);

	if(next_y < y)
		swap(&next_y, &y);

	if(next_z < z)
		swap(&next_z, &z);

	if(next_z == z) {
		if(next_x == x) {
			for(int line_y = y + 1; line_y < next_y; line_y++) {
				draw3d_on_2d(x, line_y, z, '|');
			}
		} else if(next_y == y) {
			for(int line_x = x + 1; line_x < next_x; line_x++) {
				draw3d_on_2d(line_x, y, z, '-');
			}
		}
	} else {
		if(next_x == x && next_y == y) {
			for(int line_z = z + 1; line_z < next_z; line_z++) {
				draw3d_on_2d(x, y, line_z, '-');
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
