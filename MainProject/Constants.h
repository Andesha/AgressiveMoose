#pragma once

#include "stdafx.h"

#define PERLIN_SEED 1234 // Obivous reference to the seed of the area.

const bool ENABLE_BFC = true; // Debugging flag for enabling Back Face Culling.

const int GRID_WIDTH = 9;      // Width of the grid. So if it's a 3x3, thats just 3.
const int TOTAL_VERTICIES = 81; // Number of verticies. So in a 3x3, that would be 9.
const int BUILD_INCREMENT = GRID_WIDTH / 2; // Should work fine. 3->1, 5->2, 9->4.
const int INDICES_SIZE = ((GRID_WIDTH - 1)*(GRID_WIDTH - 1)) * 2 * 3;
// The above define needs to be set to the same value as INDICES_SIZE . Just a workaround for now.

const int CHUNK_PER_ROW = 11; // In relation to the above number, this is how many the TerrainList will translate per row.
const int TERRAIN_LIST_SIZE = 500; // Number of TerrainChunk objects inside of the TerrainList.
const float SCALING_FACTOR = 5.0f; // If we scale the chunks to be bigger - we need to initialize them differently.

const float TOTAL_VERTICIES_ON_SIDE = GRID_WIDTH*CHUNK_PER_ROW; // Leave this value alone. Will obviously auto compute.
// Need to be kept track of for properly scaling perlin noise based on all the vertices on screen.
// Since we will be keeping a solid count of vertices on the screen at all time - I think this is safe.

const float HEIGHT_LIMIT = 200.0f; // Maximum value of the height and as such will scale the open interval for the perlin noise.
const float HEIGHT_OFFSET = HEIGHT_LIMIT / 2; // Just a value to adjust the perlin stuff by to make it easier to see.

const float MAX_FPS = 1000.0f; // Pretty obvious.

const float DISTANCE_CONSTANT = 30.0f; // "View distance."