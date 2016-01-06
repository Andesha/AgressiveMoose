#include "stdafx.h"

// Initialize game object to default values.
SimulationGame::SimulationGame() : window(NULL), windowWidth(1024),
windowHeight(720), gameState(GameState::PLAYING), perlin(1234){
	terrainList = TerrainList(perlin);
}

// Currently no destructor.
SimulationGame::~SimulationGame() {
}

// Start will call initialize to build all windows, followed by jumping 
// into the game loop.
void SimulationGame::start() {
	this->initialize(); // Build.
    this->camera = Camera3D();
	
	terrainList.buildPool(9); // Nine total chunks for the pool.
	terrainList.firstInit(); // Build the start of the grid.

	initializeShaders();

	this->gameLoop(); // Run.
}

// Builds the window and creates all of the OpenGL context information we need.
void SimulationGame::initialize() {
	SDL_Init(SDL_INIT_EVERYTHING); // SDL initial call.
    /*SDL_SetRelativeMouseMode(SDL_TRUE);*/
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

	glEnable(GL_CULL_FACE);

	glFrontFace(GL_CCW);
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
            camera.mouseUpdatePos(input.motion.x, input.motion.y);
            camera.checkWarp(this->window, input.motion.x, input.motion.y, 
                             this->windowWidth, this->windowHeight);
			break;
		case SDL_KEYDOWN: // Key presses.
			if (input.key.keysym.sym == 27)this->gameState = GameState::QUITTING;
            camera.handleKeyDown();
			break;
    case SDL_KEYUP:
        camera.handleKeyUp();
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
  camera.computePos();
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
	glm::mat4 proj;
	proj = glm::perspective(45.0f, (float)this->windowWidth / (float)this->windowHeight, 0.1f, 1000.0f);
 
	glm::mat4 view;
	// Note :translating the scene in the reverse direction of where we want to move
	//view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	view = camera.getViewMatrix();

	glm::mat4 model;
	model = glm::rotate(model, -55.0f, glm::vec3(1.0f, 0.0f, 0.0f));

	this->program.useProg();
 
	GLint viewLoc = this->program.getUniformLocation("view");
	GLint projLoc = this->program.getUniformLocation("proj");
	GLint modelLoc = this->program.getUniformLocation("model");

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

	for (TerrainChunk tc : terrainList.getList()) {
		glm::mat4 model;

		glm::vec3 pos;
		pos.x = tc.getCenterX();
		pos.z = tc.getCenterY(); // Confusing but oh well.

		model = glm::translate(model, pos);

		//no rotate

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)); // Send model matrix.

		tc.draw();
	}

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