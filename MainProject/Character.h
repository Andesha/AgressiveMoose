#pragma once

#include "stdafx.h"

enum CamMode{FIRST, THIRD};

class Character{
public:
    Character(glm::vec3 position);

    glm::vec3 getPos();

    void setPos(glm::vec3 newPos);

    

private:
    int cameraState = FIRST;
    
    glm::vec3 playerPosition;

    GLfloat yaw, pitch, roll;

    GLfloat speed;

    glm::vec3 pos;

    glm::vec3 dir;

    glm::vec3 target;

    glm::vec3 charRight;

    glm::vec3 charUp;

    void updateCharacterPos();

    void updateFirstCam();

    void updateThirdCam();



    

};