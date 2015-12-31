#pragma once
#include "stdafx.h"
#include "GameState.h"
#include "GLSLProgram.h"
#include "TerrainChunk.h"
#include "Camera3D.h"

// Main class which specifies all behaviour of our game engine.
class SimulationGame {
private:
	SDL_Window* window; // Window information. Possibly auto-detect later.
	int windowWidth;
	int windowHeight;

	TerrainChunk tc;

	GLSLProgram program;

	GameState gameState; // See GameState.h

    Camera3D camera;

	void initialize(); // Builds all objects like OpenGL contexts and our window.

	void initializeShaders(); // Call all needed attributes of the GLSL program.

	void examineInput(); // SDL input polling.

	void gameLoop(); // Method to be called after initialize has finished.

	void drawWorld(); // Method call for drawing all objects we need.

public:
	SimulationGame();
	~SimulationGame();

	void start(); // To be called to start the whole game.
};

