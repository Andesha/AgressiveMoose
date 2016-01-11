#pragma once
#include "stdafx.h"

class Material{
public:

    Material::Material();
    glm::vec3 amb;
    glm::vec3 diff;
    glm::vec3 spec;
    glm::vec3 kE;
    float Ni;
    float ns;
    float d;
    int illum;


    char *name;
    char *textureFile;

    
};