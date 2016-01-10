#pragma once
#include "stdafx.h"

// Reusable struct for storing x,y,z positions.
struct Position {
	float x;
	float y;
	float z;
};

struct TextureCoord {
	GLfloat x;
	GLfloat y;
};

struct VertexNormal {
    GLfloat x;
    GLfloat y;
    GLfloat z;
};

// Reusable struct for displaying colour.
struct Color {
	GLubyte r;
	GLubyte g;
	GLubyte b;
	GLubyte a;
};
                                                                                
// Vertex struct for passing into the GPU5
struct Vertex {
	Position position;
	Color color;
	TextureCoord textureCoord;
    VertexNormal vNorm;
};

