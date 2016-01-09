#pragma once

#include "stdafx.h"

class Skybox {

private:

	GLSLProgram program;

public:

	void draw(glm::mat4 view, glm::mat4 proj);

	void initialize();
	
	Skybox();
	~Skybox();
};

