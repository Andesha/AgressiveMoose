#pragma once

const int TOTAL_VERTICIES = 9; // Number of verticies. So in a 3x3, that would be 9.
const int GRID_WIDTH = 3;      // Width of the grid. So if it's a 3x3, thats just 3.
const int BUILD_INCREMENT = GRID_WIDTH / 2; // Should work fine. 3->1, 5->2, 9->4.