#include "stdafx.h"

// Initialize game object to default values.
SimulationGame::SimulationGame() : window(NULL), windowWidth(1024), windowHeight(720), gameState(GameState::PLAYING) {

}

// Currently no destructor.
SimulationGame::~SimulationGame() {
}

// Start will call initialize to build all windows, followed by jumping into the game loop.
void SimulationGame::start() {
	this->initialize(); // Build.

	tc.initialize(0.0f,0.0f);
	initializeShaders();

	this->gameLoop(); // Run.
}

// Builds the window and creates all of the OpenGL context information we need.
void SimulationGame::initialize() {
	SDL_Init(SDL_INIT_EVERYTHING); // SDL initial call.

	// SDL Window building.
	this->window = SDL_CreateWindow("Flight Simulation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->windowWidth, this->windowHeight, SDL_WINDOW_OPENGL);
	if (this->window == NULL)outputError("Window failed to build.");

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

	this->program.useProg();
	//GLfloat timePassed = SDL_GetTicks()/500;
	//GLfloat blueValue = (sin(timePassed)/2)+0.5;
	//glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
	glm::mat4 trans;
	trans = glm::rotate(trans, (GLfloat)SDL_GetTicks()/1000.f, glm::vec3(0.0f, 0.3f, 1.0f));
	//vec = trans * vec;

	GLuint transformLoc = program.getUniformLocation("transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
	tc.draw();

	this->program.unuseProg();

	SDL_GL_SwapWindow(this->window);
}

void SimulationGame::initializeShaders() {
	program.compileShaders("Shaders\\basicShader.vtx","Shaders\\basicShader.frg");
	program.addAttribute("vertexPosition");
	program.addAttribute("vertexColor");
	program.linkShaders();
}