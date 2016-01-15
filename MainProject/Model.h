#pragma once
#include "stdafx.h"
#include <vector>
#include <memory>
#include "objData.h"
#include "Mesh.h"
#include "Object.h"

/// <summary>
/// A model is a composition (or single) of meshes, which represent a 
/// collection of geometric data [vertex positions, normals] as well as texture 
/// coordinates.
///
/// Each mesh is also bound to an object, which also contains the material 
/// data [ie. the lighting constants]
/// </summary>
class Model{
public:

    Model();
 
    std::vector<std::unique_ptr<Object>> components;

    void Model::draw();
    GLuint tid;

    void Model::initialize();

private:



    void Model::makeTexture();
};