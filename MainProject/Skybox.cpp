#include "stdafx.h"

#include "Skybox.h"
#include "SkyboxVert.h"

Skybox::Skybox() : vaoID(0), vboID(0) {
}

void Skybox::draw(glm::mat4& view, glm::mat4& proj) {
	glDepthMask(GL_FALSE); // Need to make sure we will actually see anything inside of the cube.
	program.useProg(); // Use proper shader.

	// Send VP matrix information.
	glUniformMatrix4fv(program.getUniformLocation("view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(program.getUniformLocation("proj"), 1, GL_FALSE, glm::value_ptr(proj));

	glBindVertexArray(vaoID); // Standard draw copied from TerrainChunk.
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(program.getUniformLocation("skybox"), 0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTexture);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);

	program.unuseProg(); // No need to use this anymore.
	glDepthMask(GL_TRUE); // Turn BFC back on.
}

void Skybox::initialize() {
	program.compileShaders("Shaders\\skyboxShader.vtx",
		"Shaders\\skyboxShader.frg");
	program.addAttribute("position");

	program.linkShaders();

	// Above is shader inits.

	// Below OpenGL generates the needed buffers for the cube.
	if (this->vaoID == 0) { 
		glGenVertexArrays(1, &this->vaoID);
	}
	if (this->vboID == 0) { // If true, we have to rebuild the VBO.
		glGenBuffers(1, &this->vboID); // Pass in a reference to "THIS" vboID. Only generating one.
	}

	glBindVertexArray(this->vaoID);

	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertexList), &skyboxVertexList, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glBindVertexArray(0);

	// Loading of skybox textures. Standard from example code.
	std::vector<const GLchar*> faces;
	faces.push_back("skybox\\right.jpg");
	faces.push_back("skybox\\left.jpg");
	faces.push_back("skybox\\top.jpg");
	faces.push_back("skybox\\bottom.jpg");
	faces.push_back("skybox\\back.jpg");
	faces.push_back("skybox\\front.jpg");
	skyboxTexture = loadCubemap(faces);
}

Skybox::~Skybox() {
}

GLuint Skybox::loadCubemap(std::vector<const GLchar*> faces) {

	// Standard from example code.
	// Modified to use SOIL.

	GLuint textureID;
	glGenTextures(1, &textureID);

	int width, height;
	unsigned char* image;

	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	for (GLuint i = 0; i < faces.size(); i++) {
		image = SOIL_load_image(faces[i], &width, &height, 0, SOIL_LOAD_RGB);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		SOIL_free_image_data(image);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	return textureID;
}