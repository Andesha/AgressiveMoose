#pragma once

#include "stdafx.h"

class Skybox {

private:

	GLuint vaoID;
	GLuint vboID;

	GLuint skyboxTexture;

	GLSLProgram program;

	GLuint loadCubemap(vector<const GLchar*> faces);

public:

	void draw(glm::mat4 view, glm::mat4 proj);

	void initialize();
	
	Skybox();
	~Skybox();
};

