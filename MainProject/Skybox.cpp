#include "stdafx.h"
#include "Skybox.h"


Skybox::Skybox() {
}

void Skybox::draw(glm::mat4 view, glm::mat4 proj) {
	glDepthMask(GL_FALSE); // Need to make sure we will actually see anything inside of the cube.
	program.useProg();
	
	GLint viewLoc = program.getUniformLocation("view");
	GLint projLoc = program.getUniformLocation("proj");

	glUniformMatrix4fv(glGetUniformLocation(viewLoc, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(projLoc, "projection"), 1, GL_FALSE, glm::value_ptr(proj));

	program.unuseProg();
	glDepthMask(GL_TRUE);
}

void Skybox::initialize() {
	program.compileShaders("Shaders\\skyboxShader.vtx",
		"Shaders\\skyboxShader.frg");
	program.addAttribute("position");

	program.linkShaders();


}

Skybox::~Skybox() {
}
