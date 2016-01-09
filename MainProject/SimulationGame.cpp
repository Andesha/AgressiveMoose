#include "stdafx.h"

// Initialize game object to default values.
SimulationGame::SimulationGame() : window(NULL), windowWidth(1024),
windowHeight(720), gameState(GameState::PLAYING), perlin(PERLIN_SEED) {
	terrainList = TerrainList(perlin);
    character = new Character(glm::vec3(0.0f,0.0f,0.0f));
	skybox = new Skybox();
}

// Currently no destructor.
SimulationGame::~SimulationGame() {
}

// Start will call initialize to build all windows, followed by jumping 
// into the game loop.
void SimulationGame::start() {
	this->initialize(); // Build.
	
	terrainList.buildPool(TERRAIN_LIST_SIZE); // Nine total chunks for the pool.
	terrainList.firstInit(); // Build the start of the grid.

	skybox->initialize();

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
		glEnable(GL_DEPTH_TEST);
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
            //TODO add input function on character
            this->mouseUpdatePos(input.motion.xrel, input.motion.yrel);
			break;
		case SDL_KEYDOWN: // Key presses.
			if (input.key.keysym.sym == 27)this->gameState = GameState::QUITTING;
            //TODO add input function on character
            handleKeyDown();
			break;
        case SDL_KEYUP:
            handleKeyUp();
            //TODO add input function on character
            break;
		}
	}

}

void SimulationGame::fpsCaretaker(float startMarker) {
	calculateFPS();

	std::string label = "Flight Simulation: ";
	static int frameCount = 0; // Fun cheesey way of making sure we don't print too much.
	frameCount++;
	if (frameCount == 10) {
		SDL_SetWindowTitle(this->window, (label + std::to_string(this->fps)).c_str());
		frameCount = 0;
	}

	float totalTicks = SDL_GetTicks() - startMarker;

	//FPS limiting.
	if (1000.0f / MAX_FPS > totalTicks) {
		SDL_Delay(1000.0f / MAX_FPS - totalTicks);
	}
}

void SimulationGame::handleKeyDown(){
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_RETURN]) {
        printf("<RETURN> is pressed.\n");
    }
    if (state[SDL_SCANCODE_W]) {
        character->setSpeed(0.75f);
        std::cout << character->getSpeed();
    }
    if (state[SDL_SCANCODE_A]) {
        character->setLatSpeed(-0.75f);
    }
    if (state[SDL_SCANCODE_S]) {
        character->setSpeed(-0.75f);
    }
    if (state[SDL_SCANCODE_D]) {
        character->setLatSpeed(0.75f);
    }
    if (state[SDL_SCANCODE_LSHIFT]) {
        character->setSpeed(1.75f);
    }
}


void SimulationGame::handleKeyUp(){
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_W] == 0 && state[SDL_SCANCODE_S] == 0) {
        character->setSpeed(0.0f);
    }
    if (state[SDL_SCANCODE_S] == 0 && state[SDL_SCANCODE_D] == 0) {
        character->setLatSpeed(0.0f);
    }
}

void SimulationGame::mouseUpdatePos(int mouseX, int mouseY){
    character->applyMouseInput(mouseX, mouseY);
}


// Main gameloop where all behaviour will exist.
void SimulationGame::gameLoop() {
	while (this->gameState != GameState::QUITTING) {
		float startMarker = SDL_GetTicks(); // Frame time.
		
		this->examineInput();

		this->drawWorld();
		
		fpsCaretaker(startMarker); // Just trying to clean up the game loop.
	}
}

// Method call for drawing all objects we need.
void SimulationGame::drawWorld() {
    //compute character pos
    character->updateCharacter();

	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
	glm::mat4 proj;
	proj = glm::perspective(45.0f, (float)this->windowWidth / (float)this->windowHeight, 0.1f, 1000.0f);
 
	glm::mat4 view = glm::mat4(glm::mat3(character->getViewMatrix()));

	skybox->draw(view,proj); // CALL TO THE SKYBOX DRAW IS HERE

	this->program.useProg();
	
	int id = program.getProgID(); // Program ID for shaders needing them for uniform things.
 
	GLint viewLoc = this->program.getUniformLocation("view");
	GLint projLoc = this->program.getUniformLocation("proj");
	GLint modelLoc = this->program.getUniformLocation("model");

	view = character->getViewMatrix(); // Update view matrix now that we aren't doing the skybox.

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