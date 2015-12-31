#pragma once
#include "stdafx.h"

/// <summary>
///	Main class for 3d camera object
/// </summary>
class Camera3D {
public:
	Camera3D();

	// setter for position.
    void setPos(glm::vec3& newPos);

	// Getter for position.
    glm::vec3 getPos();

    // setter for direction.
    void setDir(glm::vec3& newDir);

    // Getter for direction.
    glm::vec3 getDir();

    /// <summary>
    /// create the matrix based on cameras position, target and global up vector
    /// to use as VIEW component of MVP matrix
    /// </summary>
    glm::mat4 getViewMatrix();

private:
    glm::vec3 pos;
    glm::vec3 dir;
    glm::vec3 target;
    glm::vec3 camRight;
    glm::vec3 camUp;
};

