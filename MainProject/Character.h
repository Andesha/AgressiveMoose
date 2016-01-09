#pragma once

#include "stdafx.h"

enum CamMode{FIRST, THIRD};

/// <summary>
/// 
/// </summary>
class Character{
public:

	Character();

    /// <summary>
    ///
    /// </summary>
    Character(glm::vec3 position);

    /// <summary>
    ///
    /// </summary>
    glm::vec3 getPos();

    /// <summary>
    ///
    /// </summary>
    void setPos(glm::vec3 newPos);

    /// <summary>
    ///
    /// </summary>
    void updateCharacter();

    /// <summary>
    ///
    /// </summary>
    glm::mat4 getViewMatrix();

    /// <summary>
    ///
    /// </summary>
    GLfloat getSpeed();
    
    /// <summary>
    ///
    /// </summary>
    void setSpeed(GLfloat spd);

    /// <summary>
    ///
    /// </summary>
    void setLatSpeed(GLfloat spd);

    /// <summary>
    ///
    /// </summary>
    void applyMouseInput(int x, int y);

private:
    
    Camera3D* camera;

    int cameraState = FIRST;
    
    glm::vec3 charPos;

    GLfloat yaw, pitch, roll;

    GLfloat speed, speedLat;

    glm::vec3 pos;
    
    glm::vec3 charFront;

    glm::vec3 dir;
    
    glm::vec3 target;

    glm::vec3 charRight;

    glm::vec3 charUp;

    /// <summary>
    ///
    /// </summary>
    void updateCharacterPos();

    /// <summary>
    ///
    /// </summary>
    void updateFirstCam();

    /// <summary>
    ///
    /// </summary>
    void updateThirdCam();

};