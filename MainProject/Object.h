#pragma once
#include "stdafx.h"

class Object{
public:

    Object();

    char *objectName; 
    
    void init();

    void draw();

    std::vector<std::unique_ptr<Mesh>> components;


};