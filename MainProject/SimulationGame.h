#pragma once
#include "stdafx.h"
#include "GameState.h"
#include "TerrainChunk.h"

// Main class which specifies all behaviour of our game engine.
class SimulationGame {
private:
	SDL_Window* window; // Window information. Possibly auto-detect later.
	int windowWidth;
	int windowHeight;

	TerrainChunk tc;

	GameState gameState; // See GameState.h

	void outputError(std::string error);

	void initialize(); // Builds all objects like OpenGL contexts and our window.

	void examineInput(); // SDL input polling.

	void gameLoop(); // Method to be called after initialize has finished.

	void drawWorld(); // Method call for drawing all objects we need.

public:
	SimulationGame();
	~SimulationGame();

	void start(); // To be called to start the whole game.
};

