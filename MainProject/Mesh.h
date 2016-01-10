#pragma once
#include "stdafx.h"
class Mesh{
public:
    Mesh();

    char* objectName;
    char* materialName;
    GLuint texture;

    std::vector<Vertex> vetexes;
    std::vector<int> indicies;
    void initialize();

    void Mesh::draw();


private:

    float kA;   // ambiant
    float kD;   // diffuse
    float kS;   // specular

    GLuint vaoID;
    GLuint vboID;
    GLuint eboID;
    

};