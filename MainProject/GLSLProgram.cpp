#include "stdafx.h"
#include "GLSLProgram.h"

GLSLProgram::GLSLProgram() :  progID(0), vertexID(0), fragID(0), attributeCount(0) {
	
}

GLSLProgram::~GLSLProgram() {

}

void GLSLProgram::compileShaders(const std::string& vertexPath, const std::string& fragPath) {
	//Vertex and fragment shaders are successfully compiled.
	//Now time to link them together into a program.
	//Get a program object.
	this->progID = glCreateProgram();

	this->vertexID = glCreateShader(GL_VERTEX_SHADER);
	if (this->vertexID == 0) outputError("Vertex shader failed to create.");

	this->fragID = glCreateShader(GL_FRAGMENT_SHADER);
	if (this->fragID == 0) outputError("Fragment shader failed to create.");

	compileShader(vertexPath, this->vertexID);
	compileShader(fragPath, this->fragID);

}

void GLSLProgram::linkShaders() {

	//Attach our shaders to our program
	glAttachShader(this->progID, this->vertexID);
	glAttachShader(this->progID, this->fragID);

	//Link our program
	glLinkProgram(this->progID);

	//Note the different functions here: glGetProgram* instead of glGetShader*.
	GLint isLinked = 0;
	glGetProgramiv(this->progID, GL_LINK_STATUS, (int *)&isLinked);
	if (isLinked == GL_FALSE) {
		GLint maxLength = 0;
		glGetProgramiv(this->progID, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		std::vector<char> infoLog(maxLength);
		glGetProgramInfoLog(this->progID, maxLength, &maxLength, &infoLog[0]);

		//We don't need the program anymore.
		glDeleteProgram(this->progID);
		//Don't leak shaders either.
		glDeleteShader(this->vertexID);
		glDeleteShader(this->fragID);

		//Use the infoLog as you see fit.
		std::printf("%s\n", &(infoLog[0])); // Print out our errors.
		outputError("Shader did not link");

		//In this simple program, we'll just leave
		return;
	}

	//Always detach shaders after a successful link.
	glDetachShader(this->progID, this->vertexID);
	glDetachShader(this->progID, this->fragID);

	glDeleteShader(this->vertexID);
	glDeleteShader(this->fragID);
}

void GLSLProgram::compileShader(const std::string& shaderPath, GLuint id) {
	
	std::ifstream vertexFile(shaderPath);
	if (vertexFile.fail()) outputError("Failed to open " + shaderPath);

	std::string contents = "";
	std::string line;

	while (std::getline(vertexFile, line)) {
		contents += line + "\n";
	}
	vertexFile.close();

	const char* contentPointer = contents.c_str(); // Yay internet for fixing things
	glShaderSource(id, 1, &contentPointer, NULL);

	glCompileShader(id);

	GLint success = 0; // Error checking code from the wiki.
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);

	if (success == GL_FALSE) { // Error checking more stuff from the wiki.
		GLint maxLength = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

		// Provide the infolog in whatever manor you deem best.
		// Exit with failure.
		glDeleteShader(id); // Don't leak the shader.

		std::printf("%s\n", &(errorLog[0])); // Print out our errors.
		outputError("Shader did not compile: " + shaderPath);

		return;
	}
}

void GLSLProgram::addAttribute(const std::string& attributeName) {
	glBindAttribLocation(this->progID, this->attributeCount++, attributeName.c_str());
}

void GLSLProgram::useProg() {
	glUseProgram(this->progID);
	for (int i = 0; i < this->attributeCount; i++) {
		glEnableVertexAttribArray(i);
	}
}

void GLSLProgram::unuseProg() {
	glUseProgram(0);
	for (int i = 0; i < this->attributeCount; i++) {
		glDisableVertexAttribArray(i);
	}
}

GLint GLSLProgram::getUniformLocation(const std::string& uniformName) {
	GLint location = glGetUniformLocation(progID, uniformName.c_str());
	if (location == GL_INVALID_INDEX) outputError("Uniform name not found: " + uniformName);
	return location;
}