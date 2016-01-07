#pragma once

#include "stdafx.h"

const bool ENABLE_BFC = false; // Debugging flag for enabling Back Face Culling.

const int TOTAL_VERTICIES = 49; // Number of verticies. So in a 3x3, that would be 9.
const int GRID_WIDTH = 7;      // Width of the grid. So if it's a 3x3, thats just 3.
const int BUILD_INCREMENT = GRID_WIDTH / 2; // Should work fine. 3->1, 5->2, 9->4.
const int INDICES_SIZE = pow(2.0, GRID_WIDTH) * 3; // 2 ^ GridWidth is the number of triangles. That times three is the number of indices in the EBO.
#define INDICES_WORKAROUND 384
// The above define needs to be set to the same value as INDICES_SIZE . Just a workaround for now.

const int TERRAIN_LIST_SIZE = 16; // Number of TerrainChunk objects inside of the TerrainList.
const int CHUNK_PER_ROW = 4; // In relation to the above number, this is how many the TerrainList will translate per row.

const float TOTAL_VERTICIES_ON_SIDE = GRID_WIDTH*CHUNK_PER_ROW; // Leave this value alone. Will obviously auto compute.
// Need to be kept track of for properly scaling perlin noise based on all the vertices on screen.
// Since we will be keeping a solid count of vertices on the screen at all time - I think this is safe.

const float HEIGHT_LIMIT = 50.0f; // Maximum value of the height and as such will scale the open interval for the perlin noise.

const float MAX_FPS = 60.0f;