#pragma once
#include "stdafx.h"

/// <summary>
/// Struct for storing position to be sent to the GPU.
/// </summary>
struct Position {
	float x;
	float y;
	float z;
};

/// <summary>
/// Struct for storing texture information to be sent to the GPU.
/// </summary>
struct TextureCoord {
	GLfloat x;
	GLfloat y;
};

/// <summary>
/// Struct for storing normals to be sent to the GPU.
/// </summary>
struct VertexNormal {
    GLfloat x;
    GLfloat y;
    GLfloat z;
};

/// <summary>
/// Struct for storing Color to be sent to the GPU.
/// </summary>
struct Color {
	GLubyte r;
	GLubyte g;
	GLubyte b;
	GLubyte a;
};
                                                                                
/// <summary>
/// Full Vertex struct for sending information to the GPU.
/// </summary>
struct Vertex {
	Position position;
	Color color;
	TextureCoord textureCoord;
    VertexNormal vNorm;
};

