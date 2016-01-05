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

    glm::vec3 getFront();

    void setFront(glm::vec3 &front);


    /// <summary>
    /// function for controlling 
    /// </summary>
    /// <returns> returns the view matrix of the camera </return>
    void mouseUpdatePos(int mouseX, int mouseY);

    void moveKeys(int keyIn);

    void Camera3D::setPrevXY(int x, int y);

    void Camera3D::checkWarp(SDL_Window* window, int x, int y, int windowWidth,
        int windowHeight);

private:

    bool hasMoved = false;
    int prevX, prevY;

    GLfloat yaw, pitch, roll;
    GLfloat sensitivity;
    GLfloat speed;

    glm::vec3 pos;
    glm::vec3 dir;
    glm::vec3 target;
    glm::vec3 camRight;
    glm::vec3 camUp;
    glm::vec3 cameraFront;
};
