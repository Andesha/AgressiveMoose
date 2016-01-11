#pragma once

#include "stdafx.h"
#include "Model.h"
#include "objData.h"
#include "Material.h"

class MTLParser{
public:
    MTLParser();
    std::vector<std::unique_ptr<Material>> matList;

    void parseMTL();
    char matlib[25];

private:
    int MTLParser::testLine(char* line);
    Material* currentMat;

};