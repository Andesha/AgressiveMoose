#include "stdafx.h"
#include "Material.h"

Material::Material(){
    this->name = new char[45];
    this->textureFile = new char[45];
    this->textureFile = "none";
}