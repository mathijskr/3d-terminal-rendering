#include "cube.h"

Cube cube = {
{
	/* Points */
	/*	x   y   z   */
	0.0f,  0.0f,  0.0f,	/* Front side */
	20.0f, 0.0f,  0.0f,
	20.0f, 10.0f, 0.0f,
	0.0f,  10.0f, 0.0f,

	0.0f,  0.0f,  5.0f,	/* Back side */
	20.0f, 0.0f,  5.0f,
	20.0f, 10.0f, 5.0f,
	0.0f,  10.0f, 5.0f,
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
