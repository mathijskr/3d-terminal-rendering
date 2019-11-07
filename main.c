#include "main.h"

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

	int cube[32] = {
	/*	x   y   z    index of connected point	*/
		0,  0,  0,   1,
		0,  10, 0,   3,
		20, 0,  0,   0,
		20, 10, 0,   0,

		0,  0,  5,   1,
		0,  10, 5,   0,
		20, 0,  5,   4,
		20, 10, 5,   5
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

		/* Draw cube skeleton. */
		for(int i = 0; i < 32; i+=4) {
			int x = cube[i]; int y = cube[i + 1]; int z = cube[i + 2];
			draw3d_on_2d(x, y, z, '.');

			/* Draw line between this point and next point. */
			int next_index = cube[i + 3];
			if(next_index < 0 || next_index > 27) {
				EXIT = true;
				printf("Error in cube points...");
			} else {
				int next_x = cube[next_index * 4]; int next_y = cube[next_index * 4 + 1]; int next_z = cube[next_index * 4 + 2];
				drawLine(x, y, z, next_x, next_y, next_z);
			}
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
				draw3d_on_2d(x, y, line_z, '/');
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
