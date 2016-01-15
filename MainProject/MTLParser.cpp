#include "stdafx.h"
#include "MTLParser.h"
#include <memory>
/*********************************************

Rudementary file parser to create material objects
from an OBJ format
**********************************************/

enum lineHeads{_NEWMTL, _NS, _KA, _KS, _KD, _KE, _NI, _D, _ILLUM, _MAP};

MTLParser::MTLParser(){}

void MTLParser::parseMTL(){


    std::FILE* file;
    std::cout << fopen_s(&file, "reap/untitled.mtl", "r");

    if (file == NULL){
        std::cout << "Unable to read MTL!" << std::endl;
        return;
    }
    while (true){
        char line[128];
        int isEOF;
        isEOF = fscanf(file, "%s", line);
        if (isEOF == EOF){
            break;
        }

        switch (testLine(line))
        {

        case _NEWMTL:
        {
                        currentMat = new Material();
                        fscanf(file, "%s\n", &currentMat->name); 
                        std::cout << currentMat->name;
                        break;
        }
        case _NS:
        {
                        fscanf(file, "%f\n", &this->currentMat->ns);
                        break;
        }
        case _KA:
        {
                  glm::vec3 amb;
                  fscanf(file, "%f %f %f\n", &amb.x, &amb.y, &amb.z);
                  this->currentMat->amb = amb;
                  break;
        }
        case _KD:
        {
                    glm::vec3 diff;
                    fscanf(file, "%f %f %f\n", &diff.x, &diff.y, &diff.z);
                    this->currentMat->diff = diff;
                    break;
        }
        case _KS:
        {
                    glm::vec3 spec;
                    fscanf(file, "%f %f %f\n", &spec.x, &spec.y, &spec.z);
                    this->currentMat->spec = spec;
                    break;
        }
        case _KE:
        {
                    glm::vec3 em;
                    fscanf(file, "%f %f %f\n", &em.x, &em.y, &em.z);
                    this->currentMat->kE = em;
                    break;
        }
        case _NI:
        {
                    
                    fscanf(file, "%f\n", &this->currentMat->Ni);
                    break;
        }
        case _D:
        {
                   fscanf(file, "%f\n", &this->currentMat->d);
                    break;
        }
        case _ILLUM:
        {
                       fscanf(file, "%d\n", &this->currentMat->illum);
                       break;
        }
        case _MAP:
        {
                    fscanf(file, "%s\n", &this->currentMat->textureFile);
                    break;
        }
        default:
            fscanf(file, "\n");
            break;
        }
    }
    fclose(file);
}


int MTLParser::testLine(char* line){
    if (strcmp(line, "newmtl") == 0){
        return _NEWMTL;
    }
    else if (strcmp(line, "Ns") == 0){
        return _NS;
    }
    else if (strcmp(line, "Ka") == 0){
        return _KA;
    }
    else if (strcmp(line, "Kd") == 0){
        return _KS;
    }
    else if (strcmp(line, "Ks") == 0){
        return _KD;
    }
    else if (strcmp(line, "Ke") == 0){
        return _KE;
    }
    else if (strcmp(line, "Ni") == 0){
        return _NI;
    }
    else if (strcmp(line, "d") == 0){
        return _D;
    }
    else if (strcmp(line, "illum") == 0){
        return _ILLUM;
    }
    else if (strcmp(line, "map_Kd") == 0){
        return _MAP;
    }
    return -1;
}
