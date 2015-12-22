#include "stdafx.h"

// Initialize game object to default values.
SimulationGame::SimulationGame() {
	this->window = NULL;
	this->windowWidth = 1024;
	this->windowHeight = 720;
	this->gameState = GameState::PLAYING;
}

// Currently no destructor.
SimulationGame::~SimulationGame() {
}

// Start will call initialize to build all windows, followed by jumping into the game loop.
void SimulationGame::start() {
	this->initialize(); // Build.
	this->gameLoop(); // Run.
}

// Builds the window and creates all of the OpenGL context information we need.
void SimulationGame::initialize() {
	SDL_Init(SDL_INIT_EVERYTHING); // SDL initial call.

	// SDL Window building.
	this->window = SDL_CreateWindow("Flight Simulation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,this->windowWidth,this->windowHeight, SDL_WINDOW_OPENGL);
	if (this->window == NULL)outputError("Window failed to build.");

	// Build the OpenGL context.
	SDL_GLContext context = SDL_GL_CreateContext(this->window);
	if (context == NULL)outputError("OpenGL context failed to build.");

	// For older hardware, this should help.
	GLenum error = glewInit();
	if (error != GLEW_OK)outputError("Glew failed to initialize");

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // Enable double buffering.

	glClearColor(0.0f,0.0f,1.0f,1.0f);
}

// Input polling.
void SimulationGame::examineInput() {
	SDL_Event input; // Input event.
	
	while (SDL_PollEvent(&input)) { // Pass reference to our input object.
		switch (input.type) {
		case SDL_QUIT: // Exiting.
			this->gameState = GameState::QUITTING;
			break;
		case SDL_MOUSEMOTION: // Mouse event.
			std::cout << input.motion.x << "," << input.motion.y << std::endl;
			break;
		case SDL_KEYDOWN: // Key presses.
			if (input.key.keysym.sym == 27)this->gameState = GameState::QUITTING;
			std::cout << input.key.keysym.sym << std::endl;
			break;
		}
	}

}

// Main gameloop where all behaviour will exist.
void SimulationGame::gameLoop() {
	while (this->gameState != GameState::QUITTING) {
		this->examineInput();
		this->drawWorld();
	}
}

// Helper method for determining any crashes when actually debugging the game.
void SimulationGame::outputError(std::string error) {
	std::cout << "An error has occurred:" << std::endl; // Pretty output formatting:
	std::cout << error << std::endl;
	std::cout << "Press any key to exit the application" << std::endl;

	int t; // Pause.
	std::cin >> t;

	SDL_Quit();
	exit(1); // Exit with error code.
}

// Method call for drawing all objects we need.
void SimulationGame::drawWorld(){
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnableClientState(GL_COLOR_ARRAY);
	glBegin(GL_TRIANGLES);
	glColor3f(1.0,0.0,0.0);
	glVertex2f(-1, -1);
	glVertex2f(0, -1);
	glVertex2f(0, 0);
	glEnd();

	SDL_GL_SwapWindow(this->window);
}