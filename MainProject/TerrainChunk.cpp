#include "stdafx.h"
#include "TerrainChunk.h"

// Default constructor.
TerrainChunk::TerrainChunk() : vaoID(0), vboID(0), eboID(0), drawing(false), perlin(NULL) {
}

void TerrainChunk::sendPerlin(Perlin& p) {
	this->perlin = p;
}

TerrainChunk::~TerrainChunk() {
	if (this->vboID != 0) {
		glDeleteBuffers(1,&this->vboID);
	}
	if (this->eboID != 0) {
		glDeleteBuffers(1, &this->eboID);
	}
}

bool TerrainChunk::isDrawing() {
	return this->drawing;
}

float TerrainChunk::getCenterX() {
	return this->centerX;
}

float TerrainChunk::getCenterY() {
	return this->centerY;
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
		glGenVertexArrays(1,&this->vaoID);
	}
	
	glBindVertexArray(this->vaoID);

	Vertex vertices[TOTAL_VERTICIES]; // Size of grid.
	
	int countBuild = 0;
	for (int i = BUILD_INCREMENT; i >= -BUILD_INCREMENT; i--) {
		for (int j = -BUILD_INCREMENT; j <= BUILD_INCREMENT; j++) {
			//std::cout << "(" << j << "," << i << ")";
			vertices[countBuild].position.x = (float)j;
			vertices[countBuild].position.z = (float)i;
			vertices[countBuild].position.y = examinePerlin(this->centerX + j, this->centerY + i);
			++countBuild; // I don't know?
		}
		//std::cout << std::endl;
	}

	GLuint indices[INDICES_WORKAROUND];

	int countIndex = 0;
	for (int j = 0; j < GRID_WIDTH - 1; j++) {
		for (int i = 0; i < GRID_WIDTH - 1; i++) {
			int root = i + (j*GRID_WIDTH);
			indices[countIndex++] = root + 1; // Triangle one.
			indices[countIndex++] = root + GRID_WIDTH + 1;
			indices[countIndex++] = root;

			indices[countIndex++] = root + GRID_WIDTH + 1; // Triangle two.
			indices[countIndex++] = root + GRID_WIDTH;
			indices[countIndex++] = root;
		}
	}

	//GLuint indices[] = {
	//	1, 4, 0,
	//	4, 3, 0,
	//	2, 5, 1,
	//	5, 4, 1,
	//	4, 7, 3,
	//	7, 6, 3,
	//	5, 8, 4,
	//	8, 7, 4
	//};

	for (int i = 1; i <= INDICES_SIZE; i++) {
		std::cout << indices[i-1] << ",";
		if (i % 3 == 0)std::cout << std::endl;
	}
	std::cout << "---" << std::endl;

	for (int i = 0; i < 9; i++) { // Set all to the same color.
		int modifier = rand() % 127;
		vertices[i].color.r = 255 - modifier;
		vertices[i].color.g = 255 - modifier;
		vertices[i].color.b = 255 - modifier;
		vertices[i].color.a = 255;
	}

	vertices[4].color.r = 255;
	vertices[4].color.g = 0;
	vertices[4].color.b = 255;
	vertices[4].color.a = 255;

	glBindBuffer(GL_ARRAY_BUFFER, this->vboID);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,this->eboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position)); // Position.
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color)); // Color.
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindVertexArray(0);
}

// Outside method call for building a chunk around a given point.
void TerrainChunk::rebase(float cX, float cY) {
	initialize(cX, cY);
	this->vaoID = 0;// Mark as null so that we know to redraw.
	this->vboID = 0; 
	this->eboID = 0;
}

float TerrainChunk::examinePerlin(float x, float y) {
	double temp = perlin.at(x, y, 0.5);
	return (float)temp;
}

void TerrainChunk::draw() {
	//glBindBuffer(GL_ARRAY_BUFFER,this->eboID);

	//glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color)); // Color.

	glBindVertexArray(this->vaoID);

	glDrawElements(GL_TRIANGLES, INDICES_SIZE, GL_UNSIGNED_INT, (void*)0);

	glBindVertexArray(0);

	glDisableVertexAttribArray(0); // Delete and unbind.
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}