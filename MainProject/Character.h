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
	~Character();

    /// <summary>
    /// Default constructor for the character class. Takes in the default position as the only parameter.
    /// </summary>
	/// <param name="position">Default position for this to start at.</param>
    Character(glm::vec3 position);

    /// <summary>
    /// Get the current position of the character.
    /// </summary>
    glm::vec3 getPos();

    /// <summary>
    /// Set the position of the character.
    /// </summary>
	/// <param name="newPos">New position to be sent to.</param>
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
	/// <param name="spd">Speed to set.</param>
    void setSpeed(GLfloat spd);

    /// <summary>
    /// Set the speed of the player in the lateral direction.
    /// </summary>
	/// <param name="spd">Speed to set.</param>
    void setLatSpeed(GLfloat spd);

	void multiplySpeed(GLfloat factor);

    /// <summary>
    /// Read the input from the mouse and apply to the proper methods which will move the character.
    /// </summary>
	/// <param name="x">Mouse input x.</param>
	/// <param name="y">Mouse input y.</param>
    void applyMouseInput(int x, int y);

	/// Reference to this classes 'friend' camera.
    Camera3D* camera;

private:
  
	/// Mode switch here for the camera type.
    int cameraState = FIRST;
    
	/// Euler camera values.
    GLfloat yaw, pitch, roll;

	/// Movement speed for the character.
    GLfloat speed, speedLat;

	/// Below vector store character camera information for pass through.
    glm::vec3 pos;
    glm::vec3 charFront;
    glm::vec3 dir;
    glm::vec3 target;
    glm::vec3 charRight;
    glm::vec3 charUp;

    /// <summary>
    /// Call for updating the internal position of the character.
    /// </summary>
    void updateCharacterPos();

    /// <summary>
    /// Call for pass through of camera information in form of a first person camera.
    /// </summary>
    void updateFirstCam();

    /// <summary>
    /// Call for pass through of camera information in form of a third person camera.
    /// </summary>
    void updateThirdCam();

};