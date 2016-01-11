#pragma once
#include "stdafx.h"

#include "GameState.h"
#include "GLSLProgram.h"
#include "Camera3D.h"
#include "TerrainList.h"
#include "Character.h"
#include "Skybox.h"

/// <summary>
/// Main class for the entire project. All behaviour is controlled from here.
/// </summary>
class SimulationGame {
private:

	/// Below are SDL variables.
	SDL_Window* window;
	int windowWidth;
	int windowHeight;
	float fps;
	float frameTime;

	/// Reference to the TerrainList containing the chunks.
	TerrainList* terrainList;

	/// Default shader for the chunks.
	GLSLProgram program;

	/// See GameState.h
	GameState gameState; 

	/// Reference to the character for drawing/camera/model behaviours.
    Character* character;

	/// Skybox for the project. Contains all of its own inits and drawing methods.
	Skybox* skybox;
	
	/// Perlin object for generating and building our terrain.
	Perlin perlin;

	/// <summary>
	/// Builds all objects like OpenGL contexts and our window.
	/// </summary>
	void initialize();

	/// <summary>
	/// Call all needed attributes of the GLSL program. 
	/// </summary>
	void initializeShaders();

	/// <summary>
	/// SDL input polling.
	/// </summary>
	void examineInput();

	/// <summary>
	/// Standard game loop which will call for input polling.
	/// </summary>
	void gameLoop();

	/// <summary>
	/// Call to draw and render all of our objects.
	/// </summary>
	void drawWorld();

	/// <summary>
	/// Do the math required for calculating the average in the circular buffer.
	/// </summary>
	void calculateFPS();

	/// <summary>
	/// Bind the default ground texture.
	/// </summary>
	void makeTestTexture();

	/// <summary>
	/// Helper method for cleaning up the game loop when computing fps.
	/// </summary>
	/// <param name="startMarker">Marker in ticks from when we last counted.</param>
	void fpsCaretaker(float startMarker);

	/// <summary>
	/// Method for handling keys that start pressing down.
	/// </summary>
    void handleKeyDown();

	/// <summary>
	/// Method for handling keys that finish pressing.
	/// </summary>
    void handleKeyUp();

	/// <summary>
	/// Method for passing mouse updates to outside classes.
	/// </summary>
	/// <param name="mouseX">SDL relative mouse X.</param>
	/// <param name="mouseY">SDL relative mouse Y.</param>
    void mouseUpdatePos(int mouseX, int mouseY);

public:
	/// <summary>
	/// Default constructor containing all of the proper inits.
	/// </summary>
	SimulationGame();

	/// <summary>
	/// Never to be called destructor.
	/// </summary>
	~SimulationGame();

	/// Texture ID for the ground.
	GLuint tid;

	/// <summary>
	/// To be called for the main class to begin the project.
	/// </summary>
	void start(); // To be called to start the whole game.
};

