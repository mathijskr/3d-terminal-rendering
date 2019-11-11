#include "main.h"

#define DIMENSIONS 3

int screen_ratio = 1.0f;

int main(int argv, char **argc)
{
	Cube cube = {
	{
		/* Points */
		/*	x   y   z   */
		0.0f,  0.0f,  0.0f,	/* Front side */
		10.0f, 0.0f,  0.0f,
		10.0f, 10.0f, 0.0f,
		0.0f,  10.0f, 0.0f,

		0.0f,  0.0f,  10.0f,	/* Back side */
		10.0f, 0.0f,  10.0f,
		10.0f, 10.0f, 10.0f,
		0.0f,  10.0f, 10.0f,
	},
		/* Connections */
	{
	/*	point1	point2	*/
		4,	5,	/* Back side */
		5, 	6,
		6,	7,
		7,	4,

		0,	1,	/* Front side */
		1,	2,
		2,	3,
		3,	0,


		0,	4,	/* Connecting back and front */
		1,	5,
		2,	6,
		3,	7
	}
	};

	int code = tb_init();

	/* Check if termbox was initialized. */
	if(code < 0) {
		fprintf(stderr, "termbox init failed, code: %d\n", code);
		return -1;
	}

	tb_select_input_mode(TB_INPUT_ESC);
	tb_select_output_mode(TB_OUTPUT_NORMAL);
	tb_clear();

	matrix_3x3 identity_matrix = {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	};

	matrix_3x3 proj = {
		1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 0.0f
	};

	matrix_3x3 scale = {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	};

	struct Rotation_angle {
		float x, y, z;
	} rotation_angle;

	rotation_angle.x = 0.0f;
	rotation_angle.y = 0.0f;
	rotation_angle.z = 0.0f;

	struct tb_event ev;
	bool EXIT = false;

	while(!EXIT){
		tb_clear();

		matrix_3x3 rotate = identity_matrix;

		matrix_3x3 rotate_x = rotate_x_matrix(rotation_angle.x);
		matrix_3x3 rotate_y = rotate_y_matrix(rotation_angle.y);
		matrix_3x3 rotate_z = rotate_z_matrix(rotation_angle.z);

		rotate = multiply_matrix_3x3_3x3(&rotate, &rotate_x);
		rotate = multiply_matrix_3x3_3x3(&rotate, &rotate_y);
		rotate = multiply_matrix_3x3_3x3(&rotate, &rotate_z);

		matrix_3x3 trans = multiply_matrix_3x3_3x3(&scale, &rotate);

		drawBackground();

		char text[70] = "Rotate with the x, y and z keys. Increase / decrease size with + and -";
		drawText(10, 5, text, 70, TB_BLACK, TB_WHITE);

		drawPoints(&trans, &proj, cube.points, CUBE_SIZE);
		drawConnections(&trans, &proj, cube.points, CUBE_SIZE, cube.connections, CUBE_CONNECTIONS_SIZE);

		/* Draw to screen. */
		tb_present();

		/* Update input with a timeout of n ms. */
		tb_peek_event(&ev, 0);

		if(ev.key == TB_KEY_ESC)
			EXIT = true;

		if(ev.ch == CONTROL_INC_SIZE)
			scale = multiply_matrix_3x3_scalar(&scale, 1.01f);

		if(ev.ch == CONTROL_DEC_SIZE)
			scale = multiply_matrix_3x3_scalar(&scale, 0.99f);

		if(ev.ch == CONTROL_ROTATE_X)
			rotation_angle.x += 0.1f;
		if(ev.ch == CONTROL_ROTATE_Y)
			rotation_angle.y += 0.1f;
		if(ev.ch == CONTROL_ROTATE_Z)
			rotation_angle.z += 0.1f;
	}

	tb_shutdown();
	return 0;
}

void drawPoints(matrix_3x3 *trans, matrix_3x3 *proj, float *points, int points_size)
{
	/* Draw cube points. */
	for(int i = 0; i < points_size; i += DIMENSIONS) {
		int x = points[i]; int y = points[i + 1]; int z = points[i + 2];
		vec_3d point = {x, y, z};
		point = multiply_matrix_3x3_vec3(trans, &point);
		drawPoint(&point, proj, '.');
	}
}

void drawConnections(matrix_3x3 *trans, matrix_3x3 *proj, float *points, int points_size, int *connections, int connections_size)
{
	for(int i = 0; i < connections_size; i+=2) {
		int index1 = connections[i] * DIMENSIONS;
		int index2 = connections[i + 1] * DIMENSIONS;

		vec_3d point1 = { points[index1], points[index1 + 1], points[index1 + 2] };
		vec_3d point2 = { points[index2], points[index2 + 1], points[index2 + 2] };

		point1 = multiply_matrix_3x3_vec3(trans, &point1);
		point2 = multiply_matrix_3x3_vec3(trans, &point2);

		/* Draw cube skeleton. */
		drawLine(point1, point2, proj);
	}
}

void drawPoint(vec_3d *point, matrix_3x3 *proj, char c)
{
	*point = multiply_matrix_3x3_vec3(proj, point);
	tb_change_cell(point->x, tb_height() - screen_ratio * (point->y), c, TB_GREEN, BACKGROUND_COLOR);
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

				tb_change_cell(10, 10, 'A', TB_RED, BACKGROUND_COLOR);
			/* Draw line between two y coordinates at the same x and z coordinates. */
			for(int line_y = point1.y + 1; line_y < point2.y; line_y++) {
				vec_3d point = {point1.x, line_y, point1.z};
				drawPoint(&point, proj, '-');
			}
		} else if(cmp_float(&point2.y, &point1.y) == 0) {

				tb_change_cell(10, 10, 'B', TB_RED, BACKGROUND_COLOR);
			/* Draw line between two x coordinates at the same y and z coordinates. */
			for(int line_x = point1.x + 1; line_x < point2.x; line_x++) {
				vec_3d point = {line_x, point1.y, point1.z};
				drawPoint(&point, proj, '-');
			}
		}
	} else {
		if(cmp_float(&point2.x, &point1.x) == 0 && cmp_float(&point2.y, &point1.y) == 0) {

				tb_change_cell(10, 10, 'C', TB_RED, BACKGROUND_COLOR);
			/* Draw line between two z coordinates at the same x and y coordinates. */
			for(int line_z = point1.z + 1; line_z < point2.z; line_z++) {
				vec_3d point = {point1.x, point1.y, line_z};
				drawPoint(&point, proj, '-');
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

void drawText(int x, int y, char *text, int text_size, int color, int back_color)
{
	for(int i = 0; i < text_size; i++)
		tb_change_cell(x++, y, text[i], color, back_color);
}

int cmp_float(float *f1, float *f2)
{
	if((int) (*f1 + 0.5f) == (int) (*f2 + 0.5f))
		return 0;
	return 1;
}

void swap(float *i1, float *i2)
{
	float temp = *i1;
	*i1 = *i2;
	*i2 = temp;
}
