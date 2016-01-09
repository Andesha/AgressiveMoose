#pragma once
#include "stdafx.h"

/// <summary>
///	 Main class for 3d camera object
/// </summary>
class Camera3D {
    friend class  Character; // make it a friend so we can manipulate the member
    // camera with private functions
public:

    /// <summary>
    ///
    /// </summary>
    Camera3D();

    /// <summary>
    ///
    /// </summary>
    Camera3D(glm::vec3 pos, GLfloat yaw, GLfloat pitch, GLfloat roll, float sensitivity);

    /// <summary>
    ///
    /// </summary>
    void setPos(glm::vec3 newPos);

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

    /// <summary>
    ///
    /// </summary>
    glm::vec3 getFront();

    /// <summary>
    ///
    /// </summary>
    void setFront(glm::vec3 &front);

    /// <summary>
    ///
    /// </summary>
    void updateTarget(glm::vec3& targetPos);

    /// <summary>
    /// function for controlling 
    /// </summary>
    /// <returns> returns the view matrix of the camera </return>
    void mouseUpdatePos(int mouseX, int mouseY);


    /// <summary>
    /// examine status of keys on press
    /// </summary>
    void handleKeyDown();


    /// <summary>
    /// examine status of keys on release
    /// </summary>
    void handleKeyUp();

    /// <summary>
    ///
    /// </summary>
    void Camera3D::setPrevXY(int x, int y);

    /// <summary>
    ///
    /// </summary>
    void Camera3D::checkWarp(SDL_Window* window, int x, int y, int windowWidth,
        int windowHeight);

    /// <summary>
    ///
    /// </summary>
    void Camera3D::computePos(GLfloat speed, GLfloat speedLat);



private:
    GLfloat yaw, pitch, roll;
    GLfloat sensitivity;


    glm::vec3 pos;
    glm::vec3 dir;
    glm::vec3 target;
    glm::vec3 camRight;
    glm::vec3 camUp;
    glm::vec3 cameraFront;
};
