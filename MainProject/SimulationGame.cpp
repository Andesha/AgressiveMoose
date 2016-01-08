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
	
	terrainList.buildPool(TERRAIN_LIST_SIZE); // Nine total chunks for the pool.
	terrainList.firstInit(); // Build the start of the grid.

	initializeShaders();

	makeTestTexture();

	this->gameLoop(); // Run.
}

void SimulationGame::makeTestTexture() {
	glGenTextures(1, &this->tid);

	glBindTexture(GL_TEXTURE_2D, this->tid);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height;
	unsigned char* image = SOIL_load_image("wall.jpg", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
}

// Builds the window and creates all of the OpenGL context information we need.
void SimulationGame::initialize() {
	SDL_Init(SDL_INIT_EVERYTHING); // SDL initial call.
    
	SDL_SetRelativeMouseMode(SDL_TRUE);

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

	if (ENABLE_BFC) { // Toggle for BFC.
		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CCW);
	}
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
			camera.mouseUpdatePos(input.motion.xrel, input.motion.yrel);
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
		float startMarker = SDL_GetTicks(); // Frame time.
		
		this->examineInput();
		this->drawWorld();
		calculateFPS();

		static int frameCount = 0; // Fun cheesey way of making sure we don't print too much.
		frameCount++;
		if (frameCount == 10) {
			std::cout << this->fps << std::endl;
			frameCount = 0;
		}

		float totalTicks = SDL_GetTicks() - startMarker;

		//FPS limiting.
		if (1000.0f / MAX_FPS > totalTicks) {
			SDL_Delay(1000.0f / MAX_FPS - totalTicks);
		}
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
	
	int id = program.getProgID(); // Program ID for shaders needing them for uniform things.
 
	GLint viewLoc = this->program.getUniformLocation("view");
	GLint projLoc = this->program.getUniformLocation("proj");
	GLint modelLoc = this->program.getUniformLocation("model");

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

	for (TerrainChunk tc : terrainList.getList()) {
		glm::mat4 model;

		glm::vec3 toScale = glm::vec3(SCALING_FACTOR); // Scaling matrix.
		model = glm::scale(model, toScale);

		glm::vec3 pos;
		pos.x = tc.getCenterX();
		pos.z = tc.getCenterY(); // Confusing but oh well.

		model = glm::translate(model, pos);

		// No rotate

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)); // Send model matrix.

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, this->tid);
		glUniform1i(glGetUniformLocation(id, "texIm"), 0);

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

	program.addAttribute("texCoord");

	program.linkShaders();
}

void SimulationGame::calculateFPS() {
	static const int samples = 10; // Need the next three variables to be accessed again as the same values. 
	static float frameTimes[samples]; // Thus we make them static variables.
	static int framePointer = 0;
	static float previousTicks = SDL_GetTicks(); // Idea of the implementation is a circular buffer.
	
	float currentTicks = SDL_GetTicks();

	this->frameTime = currentTicks - previousTicks;

	frameTimes[framePointer % samples] = this->frameTime;

	previousTicks = currentTicks;

	framePointer++; // Increment to next frame.

	int count; // Keep track of how many numbers we're averaging even in the start cases.
	if (framePointer < samples) count = framePointer;
	else count = samples;

	float frameAvg = 0; // Calculating the average.
	for (int i = 0; i < count; i++) {
		frameAvg += frameTimes[i];
	}
	frameAvg /= count;

	if (frameAvg > 0)this->fps = 1000.0f / frameAvg; // Avoid nasty dividing by zero problems.
	else this->fps = 60.0f; // Hard coded for those beginning iterations.
}