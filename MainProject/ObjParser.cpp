#include "stdafx.h"
#include "ObjParser.h"
#include "Mesh.h"
#include "Model.h"

enum lineType{
    _V, _VT, _VN, _F, _O, _MTLLIB, _USEMTL, _CMT, _S
};

ObjParser::ObjParser(){
    

}

Model *ObjParser::parseFile(){
    bool noObj = true;
    Model* new_m = new Model();
    std::FILE* file; 
    std::cout << fopen_s(&file, "reap/reaperTri.obj", "r");
    this->current_mesh = new Mesh();
    this->current_mesh->objectName = "default";
    if (file == NULL){
        std::cout << "Unable to read OBJ!" << std::endl;
        return NULL;
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
        case _CMT:
            std::cout << "sdsadas" << std::endl;
            break;

        case _V:
        {   
            if (current_mesh->objectName == "default" && noObj){
                noObj = false;
                new_m->components.emplace_back(std::move(current_mesh));
            }
            float x, y, z;
            fscanf(file, "%f %f %f\n",&x, &y, &z);
            this->file_vertexs.push_back(glm::vec3(x, y, z));
            break;
        }
        case _VT:
        {
            glm::vec2 geoTexVert;
            fscanf(file, "%f %f\n", &geoTexVert.x, &geoTexVert.y);
            this->file_uvs.push_back(geoTexVert);
            break;
        }
        case _VN:
        {
            glm::vec3 geoNorm;
            fscanf(file, "%f %f %f\n", &geoNorm.x, &geoNorm.y, &geoNorm.z);
            this->file_norms.push_back(geoNorm);
            break;
        }
        case _F:
        {
            // we know the model is triangulated
            int vertindex, texindex, normieindex;
            fscanf(file, "%d/%d/%d", &vertindex, &texindex, &normieindex);
            this->current_mesh->vetexes.push_back(getMeshVertex(vertindex, texindex, normieindex));
            fscanf(file, "%d/%d/%d", &vertindex, &texindex, &normieindex);
            this->current_mesh->vetexes.push_back(getMeshVertex(vertindex, texindex, normieindex));

            fscanf(file, "%d/%d/%d\n", &vertindex, &texindex, &normieindex);
            this->current_mesh->vetexes.push_back(getMeshVertex(vertindex, texindex, normieindex));
            break;
        }
        case _O:
        {
            //THIS MIGHT BE AN ISSUE
            this->current_mesh = new Mesh();
            new_m->components.emplace_back(std::move(current_mesh));
            fscanf(file, "%s", this->current_mesh->objectName);
            std::cout << "OBJECT NAMED " << this->current_mesh->objectName << std::endl;
            break;
        }
        case _S:
        {
            char stuff[10];
            fscanf(file, "%s\n", stuff);
            break;
        }
        case _MTLLIB:
        {
            fscanf(file, "%s\n", this->matlib);
            break;
        }
        case _USEMTL:
        {
            fscanf(file, "%s\n", this->current_mesh->materialName);
            break;
        }
        default:
            break;
        }
        
    }
    std::cout << new_m->components.size() << "number of models" << std::endl;

    return new_m;
}

int ObjParser::testLine(char* line){
    if (strcmp(line, "#") == 0){
        return _CMT;
    }
    else if (strcmp(line, "vt")==0){
        return _VT;
    }
    else if (strcmp(line, "vn")==0){
        return _VN;
    }
    else if (strcmp(line, "v")==0){
        return _V;
    }
    else if (strcmp(line, "f")==0){
        return _F;
    }
    else if (strcmp(line, "o")==0){
        return _O;
    }
    else if (strcmp(line, "mtllib")==0){
        return _MTLLIB;
    }
    else if (strcmp(line, "s")==0){
        return _S;
    }
    else if (strcmp(line, "usemtl")==0){
        return _USEMTL;
    }
    return -1;
}

Vertex ObjParser::getMeshVertex(int vIndex, int uvIndex, int normieIndex){
    Vertex modelVert;

    glm::vec3 tempV = file_vertexs[vIndex-1];
    glm::vec2 tempUV = file_uvs[uvIndex - 1];
    glm::vec3 tempnormie = file_norms[normieIndex - 1];

    modelVert.position.x = tempV.x;
    modelVert.position.y = tempV.y;
    modelVert.position.z = tempV.z;

    modelVert.textureCoord.x = tempUV.x;
    modelVert.textureCoord.y = tempUV.y;

    modelVert.color.r = 255;
    modelVert.color.g = 0;
    modelVert.color.b = 0;
    modelVert.color.a = 0;

    modelVert.vNorm.x = tempnormie.x;
    modelVert.vNorm.x = tempnormie.y;
    modelVert.vNorm.x = tempnormie.z;

    return modelVert;
}
