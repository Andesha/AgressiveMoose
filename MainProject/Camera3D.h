#pragma once
#include "stdafx.h"

/// <summary>
///	Main class for 3d camera object
/// </summary>
class Camera3D {
public:
	Camera3D();

    /// <summary>
    ///
    /// </summary>
    void setPos(glm::vec3& newPos);

    /// <summary>
    /// get position
    /// </summary>
    /// <returns>the position in 3D space</return>
    glm::vec3 getPos();

    /// <summary>
    /// set direction vector
    /// </summary>
    void setDir(glm::vec3& newDir);

    /// <summary>
    /// return direction vector
    /// </summary>
    /// <returns>the direction vector</return>
    glm::vec3 getDir();

    /// <summary>
    /// create the matrix based on cameras position, target and global up
    /// vector to use as VIEW component of MVP matrix
    /// </summary>
    /// <returns> returns the view matrix of the camera </return>
    glm::mat4 getViewMatrix();

    void setFront(glm::vec3 &front);

    void Camera3D::incPos();

private:
    glm::vec3 pos;
    glm::vec3 dir;
    glm::vec3 target;
    glm::vec3 camRight;
    glm::vec3 camUp;
    glm::vec3 cameraFront;
};

