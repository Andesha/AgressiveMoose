#pragma once
#include "stdafx.h"

/// <summary>
/// This class is to be used as an object which contains all of the needed behaviour for a
/// shader. It will compile - link and add behaviour as needed.
/// </summary>
class GLSLProgram {
private:

	/// Below three values are IDs which the class will use to link.
    GLuint progID;
    GLuint vertexID;
    GLuint fragID;

	/// Counter for keeping track of the number of attribute that the shader has.
    int attributeCount;

	/// <summary>
	/// Compiles both of the shaders and will also print any errors to console.
	/// </summary>
	/// <param name="shaderPath">Path of the single shader file.</param>
	/// <param name="id">Path of the ID we're binding to.</param>
    void compileShader(const std::string& shaderPath, GLuint id);

public:

	/// <summary>
	/// Empty default constructor.
	/// </summary>
    GLSLProgram();

	/// <summary>
	/// Empty destructor - never getting rid of these objects.
	/// </summary>
    ~GLSLProgram();

	/// <summary>
	/// Getter for the program ID of the shader. Needed for uniform searching.
	/// </summary>
	/// <returns>Returns the program ID of the shader.</return>
    int getProgID();

	/// <summary>
	/// Add an attribute to the shader so that it can be found easily later with a get.
	/// </summary>
	/// <param name="attributeName">Attribute name to bind.</param>
    void addAttribute(const std::string& attributeName);

	/// <summary>
	/// Public method that will compile the two input shaders.
	/// </summary>
	/// <param name="vertexPath">Vertex shader path.</param>
	/// <param name="fragPath">Fragment shader path.</param>
    void compileShaders(const std::string& vertexPath, const std::string& fragPath);

	/// <summary>
	/// Public method that will call a full binding so that the shaders can be used.
	/// </summary>
    void linkShaders();

	/// <summary>
	/// Method which will return the location GLint of a uniform variable inside of a shader.
	/// Will fail softly.
	/// </summary>
	/// <param name="uniformName">Variable name to find.</param>
    GLint getUniformLocation(const std::string& uniformName);

	/// <summary>
	/// Activate shader.
	/// </summary>
    void useProg();

	/// <summary>
	/// Deactivate shader.
	/// </summary>
    void unuseProg();
};

