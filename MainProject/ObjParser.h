#pragma once

#include "stdafx.h"
#include "Model.h"
#include "objData.h"

class ObjParser{
public:
    ObjParser();

    Model *parseFile();

    char matlib[25];
    
private:
    Mesh *current_mesh;
 
    int testLine(char* line);

    Vertex ObjParser::getMeshVertex(int vIndex, int uvIndex, int normieIndex);

    std::vector<glm::vec3> file_vertexs;

    std::vector<glm::vec2> file_uvs;

    std::vector<glm::vec3> file_norms;

    
};