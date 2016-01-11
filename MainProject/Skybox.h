#pragma once

#include "stdafx.h"

/// <summary>
/// Class contains all of the object members and behaviours to display a skybox.
/// </summary>
class Skybox {

private:

	/// Standard VAO ID's
	GLuint vaoID;
	GLuint vboID;

	/// Bound texture reference.
	GLuint skyboxTexture;

	/// Reference to the shader.
	GLSLProgram program;

	/// <summary>
	/// Standard loading of a cube map.
	/// </summary>
	/// <param name="faces">Vector of the face locations.</param>
	/// <returns>Bound texture reference for the skybox.</return>
	GLuint loadCubemap(std::vector<const GLchar*> faces);

public:

	/// <summary>
	/// Draws the skybox according to the view and projection matrix.
	/// Note that the skybox should always be drawn independant of the rotation
	/// found in the view matrix.
	/// </summary>
	/// <param name="view">View Matrix.</param>
	/// <param name="proj">Projection Matrix.</param>
	void draw(glm::mat4& view, glm::mat4& proj);

	/// <summary>
	/// One time first use function for calling and binding everything needed.
	/// </summary>
	void initialize();
	
	/// <summary>
	/// Default constructor.
	/// </summary>
	Skybox();

	/// <summary>
	/// Empty default destructor.
	/// </summary>
	~Skybox();
};