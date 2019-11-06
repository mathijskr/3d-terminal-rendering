#include "main.h"

void draw3d_on_2d(int x, int y, int z, char c);

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

	int cube[24] = {
		0,  0,  0,
		0,  10, 0,
		20, 0,  0,
		20, 10, 0,

		0,  0,  5,
		0,  10, 5,
		20, 0,  5,
		20, 10, 5
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
		for(int i = 0; i < 24; i+=3) {
			int x = cube[i]; int y = cube[i + 1]; int z = cube[i + 2];
			draw3d_on_2d(x, y, z, '.');

			/* Draw line between this point and next point. */
			if(i < 21) {
				int next_x = cube[i + 3]; int next_y = cube[i + 4]; int next_z = cube[i + 5];

				if(z == next_z) {
					for(int x_line = x + 1; x_line < next_x; x_line++) {
						tb_change_cell(x_line, 10 + y, '-', TB_GREEN, BACKGROUND_COLOR);
					}

					for(int y_line = y + 1; y_line < next_y; y_line++) {
						tb_change_cell(x, 10 + y_line, '|', TB_GREEN, BACKGROUND_COLOR);
					}
				}
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
	tb_change_cell(x + 2 * z, 10 + (y - z), c, TB_GREEN, BACKGROUND_COLOR);
}
