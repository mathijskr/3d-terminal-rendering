#include "cube.h"

Cube cube = {
{
	/* Points */
	/*	x   y   z   */
	0,  0,  0,	/* Front side */
	20, 0,  0,
	20, 10, 0,
	0,  10, 0,

	0,  0,  5,	/* Back side */
	20, 0,  5,
	20, 10, 5,
	0,  10, 5,
},
	/* Connections */
{
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
}
};
