#include "stdafx.h"
#include "TerrainChunk.h"

// Default constructor.
TerrainChunk::TerrainChunk() : vaoID(0), vboID(0), eboID(0), drawing(false), perlin(NULL){
}

void TerrainChunk::sendPerlin(Perlin& p) {
    this->perlin = p;
}

TerrainChunk::~TerrainChunk() {
    if (this->vboID != 0) {
        glDeleteBuffers(1, &this->vboID);
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
        glGenBuffers(1, &this->vboID); // Pass in a reference to "THIS" vboID. Only generating one.
    }
    if (this->eboID == 0) {
        glGenBuffers(1, &this->eboID);
    }
    if (this->vaoID == 0) {
        glGenVertexArrays(1, &this->vaoID);
    }

    glBindVertexArray(this->vaoID);

    Vertex vertices[TOTAL_VERTICIES]; // Size of grid.

    int countBuild = 0;
    float rowCount = 0.0f;
    float colCount = 0.0f;
    for (int i = BUILD_INCREMENT; i >= -BUILD_INCREMENT; --i) {
        for (int j = -BUILD_INCREMENT; j <= BUILD_INCREMENT; ++j) {
            vertices[countBuild].position.x = (float)j;
            vertices[countBuild].position.z = (float)i;
            vertices[countBuild].position.y = perlin.at(this->centerX + j, this->centerY + i);

            vertices[countBuild].textureCoord.x = colCount * (1.0f / ((float)GRID_WIDTH - 1));
            vertices[countBuild].textureCoord.y = rowCount * (1.0f / ((float)GRID_WIDTH - 1));
            
			glm::vec3 tempVnorm = calcVertexNormal(vertices[countBuild].position);

			vertices[countBuild].vNorm.x = tempVnorm.x;
			vertices[countBuild].vNorm.y = tempVnorm.y;
			vertices[countBuild].vNorm.z = tempVnorm.z;

            ++countBuild;
            ++colCount;
        }
        ++rowCount;
        colCount = 0;
    }

    //for (int i = 0; i < TOTAL_VERTICIES; ++i) { // Set all to the same color.
    //    int modifier = rand() % 127;
    //    vertices[i].color.r = 255 - modifier;
    //    modifier = rand() % 127;
    //    vertices[i].color.g = 255 - modifier;
    //    modifier = rand() % 127;
    //    vertices[i].color.b = 255 - modifier;
    //    vertices[i].color.a = 255;
    //}

    //vertices[24].color.r = 255;
    //vertices[24].color.g = 0;
    //vertices[24].color.b = 255;
    //vertices[24].color.a = 255;

    GLuint indices[INDICES_SIZE];

    int countIndex = 0;
    for (int j = 0; j < GRID_WIDTH - 1; ++j) {
        for (int i = 0; i < GRID_WIDTH - 1; ++i) {
            int root = i + (j*GRID_WIDTH);
            indices[countIndex++] = root + 1; // Triangle one.
            indices[countIndex++] = root + GRID_WIDTH + 1;
            indices[countIndex++] = root;

            indices[countIndex++] = root + GRID_WIDTH + 1; // Triangle two.
            indices[countIndex++] = root + GRID_WIDTH;
            indices[countIndex++] = root;
        }
    }

    glBindBuffer(GL_ARRAY_BUFFER, this->vboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->eboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position)); // Position.
    glEnableVertexAttribArray(0);

    // Color
    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color)); // Color.
    glEnableVertexAttribArray(1);

    // texture
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, textureCoord)); // TextureCoord.
    glEnableVertexAttribArray(2);

    // vertex norm
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, vNorm));
    glEnableVertexAttribArray(3);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

// Outside method call for building a chunk around a given point.
void TerrainChunk::rebase(float cX, float cY) {
    initialize(cX, cY);
    this->vaoID = 0;// Mark as null so that we know to redraw.
    this->vboID = 0;
    this->eboID = 0;
}

//float TerrainChunk::examinePerlin(float x, float y) {
//    double temp = perlin.at(x / TOTAL_VERTICIES_ON_SIDE, y / TOTAL_VERTICIES_ON_SIDE, 0.5);
//    return (float)temp*HEIGHT_LIMIT - HEIGHT_OFFSET;
//}

void TerrainChunk::draw() {
    glBindVertexArray(this->vaoID);
    glDrawElements(GL_TRIANGLES, INDICES_SIZE, GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);

    glDisableVertexAttribArray(0); // Delete and unbind.
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//I know this doesnt look pretty, but hey, whatever man.....
glm::vec3 TerrainChunk::calcVertexNormal(Position pos){
	float x = pos.x + centerX;
	float y = pos.y;
	float z = pos.z + centerY;

	//std::cout << x+centerX << "," << y << "," << z+centerY << std::endl;

    glm::vec3 vNorm1, vNorm2, vNorm3, vNorm4, vNorm5, vNorm6;
	glm::vec3 p1, p2, p3;

    // Triangle 1
    p1 = glm::vec3(x, y, z);
    p2 = glm::vec3(x- 1, examinePerlin(x- 1, z), z);
    p3 = glm::vec3(x- 1, examinePerlin(x- 1, z - 1), z - 1);
    vNorm1 = glm::normalize(glm::cross((p3 - p1), (p2 - p1)));

    // Triangle 2
    p2 = glm::vec3(x- 1, examinePerlin(x- 1, z - 1), z - 1);
    p3 = glm::vec3(x,examinePerlin(x,z - 1), z - 1);
    vNorm2 = glm::normalize(glm::cross((p3 - p1), (p2 - p1)));

    // Triangle 3
    p2 = glm::vec3(x,examinePerlin(x,z - 1), z - 1);
    p3 = glm::vec3(x+ 1, examinePerlin(x+ 1, z), z);
    vNorm3 = glm::normalize(glm::cross((p3 - p1), (p2 - p1)));

    // Triangle 4
    p3 = glm::vec3(x+ 1, examinePerlin(x+ 1, z), z);
    p3 = glm::vec3(x+ 1, examinePerlin(x+ 1, z + 1), z + 1);
    vNorm4 = glm::normalize(glm::cross((p3 - p1), (p2 - p1)));

    // Triangle 5
    p2 = glm::vec3(x,examinePerlin(x,z + 1), z + 1);
    p3 = glm::vec3(x+ 1, examinePerlin(x+ 1, z + 1), z + 1);
    vNorm5 = glm::normalize(glm::cross((p3 - p1), (p2 - p1)));

    // Triangle 6
    p3 = glm::vec3(x,examinePerlin(x,z + 1), z + 1);
    p2 = glm::vec3(x- 1, examinePerlin(x- 1, z), z);
    vNorm6 = glm::normalize(glm::cross((p3 - p1), (p2 - p1)));

   // std::cout << vNorm.x << "\t" << vNorm.y << "\t" << vNorm.z << "\t" << std::endl;
    //std::cout << vNorm.x << "\t" << vNorm.y << "\t" << vNorm.z << std::endl;  
    return glm::normalize(vNorm1 + vNorm2 + vNorm3 + vNorm4 + vNorm5 + vNorm6);
}