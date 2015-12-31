#include "stdafx.h"

// Initialize game object to default values.
SimulationGame::SimulationGame() : 
    window(NULL),
    windowWidth(1024), 
    windowHeight(720), 
    gameState(GameState::PLAYING){

}

// Currently no destructor.
SimulationGame::~SimulationGame() {
}

// Start will call initialize to build all windows, followed by jumping 
// into the game loop.
void SimulationGame::start() {
	this->initialize(); // Build.
    this->camera = Camera3D();
	tc.initialize(0.0f,0.0f);
	initializeShaders();

	this->gameLoop(); // Run.
}

// Builds the window and creates all of the OpenGL context information we need.
void SimulationGame::initialize() {
	SDL_Init(SDL_INIT_EVERYTHING); // SDL initial call.

	// SDL Window building.
	this->window = SDL_CreateWindow("Flight Simulation", SDL_WINDOWPOS_CENTERED, 
									SDL_WINDOWPOS_CENTERED, this->windowWidth, 
									this->windowHeight, SDL_WINDOW_OPENGL);                                                                                                              
	// Build the OpenGL context.
	SDL_GLContext context = SDL_GL_CreateContext(this->window);
	if (context == NULL)outputError("OpenGL context failed to build.");

	// For older hardware, this should help.
	GLenum error = glewInit();
	if (error != GLEW_OK)outputError("Glew failed to initialize");

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // Enable double buffering.

	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
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

// Method call for drawing all objects we need.
void SimulationGame::drawWorld() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
  glm::mat4 proj;
  proj = glm::perspective(
      45.0f, (float)this->windowWidth / (float)this->windowHeight, 
      0.1f, 100.0f);
 
  glm::mat4 view;
  // Note that we're translating the scene in the reverse direction of where we want to move
  //view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
  view = camera.getViewMatrix();

  glm::mat4 model;
  model = glm::rotate(model, -55.0f, glm::vec3(1.0f, 0.0f, 0.0f));

	this->program.useProg();

  GLint modelLoc = this->program.getUniformLocation("model");
  glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
 
  GLint viewLoc = this->program.getUniformLocation("view");
  glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
  
  GLint projLoc = this->program.getUniformLocation("proj");
  glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

	tc.draw();
	this->program.unuseProg();

	SDL_GL_SwapWindow(this->window);
}

void SimulationGame::initializeShaders() {
	program.compileShaders("Shaders\\basicShader.vtx",
                         "Shaders\\basicShader.frg");
	program.addAttribute("vertexPosition");
	program.addAttribute("vertexColor");
	program.linkShaders();
}