#pragma once

#include "stdafx.h"

const int TOTAL_VERTICIES = 49; // Number of verticies. So in a 3x3, that would be 9.
const int GRID_WIDTH = 7;      // Width of the grid. So if it's a 3x3, thats just 3.
const int BUILD_INCREMENT = GRID_WIDTH / 2; // Should work fine. 3->1, 5->2, 9->4.
const int INDICES_SIZE = pow(2.0, GRID_WIDTH) * 3; // 2 ^ GridWidth is the number of triangles. That times three is the number of indices in the EBO.
#define INDICES_WORKAROUND 384
// The above define needs to be set to the same value as INDICES_SIZE . Just a workaround for now.

//GLuint indices[] = {
//	1, 4, 0,
//	4, 3, 0,
//	2, 5, 1,
//	5, 4, 1,
//	4, 7, 3,
//	7, 6, 3,
//	5, 8, 4,
//	8, 7, 4
//};