#pragma once

#include "stdafx.h"

enum CamMode{FIRST, THIRD};

/// <summary>
/// This class groups together a Camera class and the needed vectors for maintaining it.
/// Other information stored in the location of the player - the camera mode - as well as model information.
/// </summary>
class Character{
public:

	Character();

    /// <summary>
    /// Default constructor for the character class. Takes in the default position as the only parameter.
    /// </summary>
    Character(glm::vec3 position);

    /// <summary>
    /// Get the current position of the character.
    /// </summary>
    glm::vec3 getPos();

    /// <summary>
    /// Set the position of the character.
    /// </summary>
    void setPos(glm::vec3 newPos);

    /// <summary>
    /// Begin and updated. To be called when moving and translating objects held by this class.
    /// </summary>
    void updateCharacter();

    /// <summary>
    /// Gets the view matrix that the camera contained inside of this class has.
    /// </summary>
    glm::mat4 getViewMatrix();

    /// <summary>
    /// Gets the current speed of the player.
    /// </summary>
    GLfloat getSpeed();
    
    /// <summary>
    /// Set the speed of the player in the forward direction.
    /// </summary>
    void setSpeed(GLfloat spd);

    /// <summary>
    /// Set the speed of the player in the lateral direction.
    /// </summary>
    void setLatSpeed(GLfloat spd);

    /// <summary>
    /// Read the input from the mouse and apply to the proper methods which will move the character.
    /// </summary>
    void applyMouseInput(int x, int y);

    Camera3D* camera;

private:
  
    int cameraState = FIRST;
    
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