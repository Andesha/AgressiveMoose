#pragma once

#include "stdafx.h"

#define PERLIN_SEED 1234 // Obivous reference to the seed of the area.

const bool ENABLE_BFC = true; // Debugging flag for enabling Back Face Culling.

const int GRID_WIDTH = 19;      // Width of the grid. So if it's a 3x3, thats just 3.
const float GRID_INCREMENT = GRID_WIDTH - 1.f;
const int TOTAL_VERTICIES = GRID_WIDTH*GRID_WIDTH; // Number of verticies. So in a 3x3, that would be 9.
const int BUILD_INCREMENT = GRID_WIDTH / 2; // Should work fine. 3->1, 5->2, 9->4.
const int INDICES_SIZE = ((GRID_WIDTH - 1)*(GRID_WIDTH - 1)) * 2 * 3;
// The above define needs to be set to the same value as INDICES_SIZE . Just a workaround for now.

const float SCALING_FACTOR = 2.f; // If we scale the chunks to be bigger - we need to initialize them differently

const float VIEW_DISTANCE = 200.f; // "View distance."
const float PERLIN_DISTANCE = 8.f;

const float FARCLIP = VIEW_DISTANCE * GRID_INCREMENT * 0.4f;

const float CHUNKS_PER_SIDE = (VIEW_DISTANCE / SCALING_FACTOR);
const float TOTAL_VERTICIES_ON_SIDE = GRID_INCREMENT*(PERLIN_DISTANCE / SCALING_FACTOR)+1.f; // Leave this value alone. Will obviously auto compute.
// Need to be kept track of for properly scaling perlin noise based on all the vertices on screen.
// Since we will be keeping a solid count of vertices on the screen at all time - I think this is safe.

const float GRID_OFFSET = (0.5f * (GRID_INCREMENT*(CHUNKS_PER_SIDE - 1.f)));

const float HEIGHT_LIMIT = 200.0f; // Maximum value of the height and as such will scale the open interval for the perlin noise.
const float HEIGHT_OFFSET = HEIGHT_LIMIT / 2; // Just a value to adjust the perlin stuff by to make it easier to see.

const float MAX_FPS = 1000.0f; // Pretty obvious.
