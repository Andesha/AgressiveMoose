#include "stdafx.h"
#include "Mesh.h"

Mesh::Mesh(){
    //this->objectName = new char[25];
    this->materialName = new char[45];
}

Mesh::~Mesh() {
	delete materialName;
}


void Mesh::initialize(){
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
    int index = vetexes.size();
    std::vector<GLuint> indices;
    indices.resize(index);
    for (unsigned int j = 0; j < indices.size(); ++j) {
            indices[j] = (GLuint)j;
    }
    
    glBindBuffer(GL_ARRAY_BUFFER, this->vboID);
    glBufferData(GL_ARRAY_BUFFER, vetexes.size() * sizeof(Vertex), &vetexes[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->eboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

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


void Mesh::draw() {
    glBindVertexArray(this->vaoID);
    glDrawElements(GL_TRIANGLES, vetexes.size(), GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);
    glDisableVertexAttribArray(0); // Delete and unbind.
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}