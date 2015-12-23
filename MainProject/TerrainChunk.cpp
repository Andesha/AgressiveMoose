#include "stdafx.h"
#include "TerrainChunk.h"

// Default constructor.
TerrainChunk::TerrainChunk() : vaoID(0), vboID(0), eboID(0), drawing(false) {
	
}


TerrainChunk::~TerrainChunk() {
	if (this->vboID != 0) {
		glDeleteBuffers(1,&this->vboID);
	}
	if (this->eboID != 0) {
		glDeleteBuffers(1, &this->eboID);
	}
}

// Private method to be called when first building, AND rebuilding chunks.
void TerrainChunk::initialize(float cX, float cY) {
	this->drawing = true;
	
	this->centerX = cX;
	this->centerY = cY;

	if (this->vboID == 0) { // If true, we have to rebuild the VBO.
		glGenBuffers(1,&this->vboID); // Pass in a reference to "THIS" vboID. Only generating one.
	}
	if (this->eboID == 0) {
		glGenBuffers(1,&this->eboID);
	}
	if (this->vaoID == 0) {
		glGenVertexArrays(1,&vaoID);
	}

	glBindVertexArray(this->vaoID);

	//Vertex vertices[9]; // Size of grid.
	//int vertStart = 9 / 2;

	//for (int i = vertStart; i >= -vertStart; i--) {
	//	for (int j = -vertStart; j <= vertStart; j++) {
	//		//std::cout << "(" << j << "," << i << ")";
	//		vertices[i].position.x = (float)j;
	//		vertices[i].position.y = (float)i;
	//		vertices[i].position.z = examinePerlin((int)this->centerX+j, (int)this->centerY+i);
	//	}
	//	//std::cout << std::endl;
	//}

	GLfloat vertices[] = {
		0.5f, 0.5f, 0.0f,  // Top Right
		0.5f, -0.5f, 0.0f,  // Bottom Right
		-0.5f, -0.5f, 0.0f,  // Bottom Left
		-0.5f, 0.5f, 0.0f   // Top Left 
	};
	GLuint indices[] = {  // Note that we start from 0!
		0, 1, 3,  // First Triangle
		1, 2, 3   // Second Triangle
	};

	//for (int i = 0; i < 9; i++) { // Set all to the same color.
	//	vertices[i].color.r = 255;
	//	vertices[i].color.g = 0;
	//	vertices[i].color.b = 255;
	//	vertices[i].color.a = 255;
	//}

	//GLuint indices[] = {
	//	1,10,0,
	//	10,9,0
	//};

	glBindBuffer(GL_ARRAY_BUFFER, this->vboID);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,this->eboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER,0);

	glBindVertexArray(0);
}

// Outside method call for building a chunk around a given point.
void TerrainChunk::rebase(float cX, float cY) {
	initialize(cX, cY);
	this->vaoID = 0;
	this->vboID = 0; // Mark as null so that we know to redraw.
	this->eboID = 0;
}

float TerrainChunk::examinePerlin(int x, int y) {
	return 1.0f;
}

void TerrainChunk::draw() {
	//glBindBuffer(GL_ARRAY_BUFFER,this->eboID);

	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position)); // Position.
	//glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color)); // Color.

	glBindVertexArray(this->vaoID);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

	glBindVertexArray(0);

	glDisableVertexAttribArray(0); // Delete and unbind.
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}