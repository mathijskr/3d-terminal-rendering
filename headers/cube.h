#ifndef CUBE_H
#define CUBE_H

#define CUBE_SIZE 28
#define CUBE_CONNECTIONS_SIZE 24

typedef struct Cube Cube;

struct Cube 
{
	float points[CUBE_SIZE];
	int connections[CUBE_CONNECTIONS_SIZE];
} cube;

#endif
