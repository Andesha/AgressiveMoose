#pragma once
#include "stdafx.h"

class GLSLProgram {
private:
	GLuint progID;
	GLuint vertexID;
	GLuint fragID;

	int attributeCount;

	void compileShader(const std::string& shaderPath, GLuint id);

public:
	GLSLProgram();
	~GLSLProgram();

	int getProgID();

	void addAttribute(const std::string& attributeName);

	void compileShaders(const std::string& vertexPath, const std::string& fragPath);

	void linkShaders();

	GLint getUniformLocation(const std::string& uniformName);

	void useProg();
	void unuseProg();
};

