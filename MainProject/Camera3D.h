#pragma once
#include "stdafx.h"

/// <summary>
///	 Class which controls a 3D Camera for our opengl view port.
///  Understood to belong to a character class at one point or another.
/// </summary>
class Camera3D {
    friend class  Character; // make it a friend so we can manipulate the member
    // camera with private functions
public:

    /// <summary>
    /// Default constructor. No parameter calls so that we can have default objects.
    /// </summary>
    Camera3D();

	/// <summary>
	/// Constructor which allows the passing of default values to the camera for where it is
	/// to be positioned in the world at the start.
	/// </summary>
	/// <param name="pos">Default camera position..</param>
	/// <param name="yaw">Standard Euler yaw.</param>
	/// <param name="pitch">Standard Euler pitch.</param>
	/// <param name="roll">Standard Euler roll.</param>
	/// <param name="sensitivity">Param for how much mouse movement is needed to move the camera.</param>
    Camera3D(glm::vec3 pos, GLfloat yaw, GLfloat pitch, GLfloat roll, float sensitivity);

	/// <summary>
	/// Set the position of the camera.
	/// </summary>
	/// <param name="newPos">New position of the camera.</param>
    void setPos(glm::vec3 newPos);

    /// <summary>
    /// Get current position of the camera.
    /// </summary>
    /// <returns>the position in 3D space</return>
    glm::vec3 getPos();

	/// <summary>
	/// Set the direction of the camera to the input vector.
	/// </summary>
	/// <param name="newDir">New direction to be sent to the camera.</param>
    void setDir(glm::vec3& newDir);

	/// <summary>
	/// Returns the current direction that the camera is facing.
	/// </summary>
	/// <returns>Returns the current direction that the camera is facing.</return>
    glm::vec3 getDir();

    /// <summary>
    /// Create the matrix based on cameras position, target and global up
    /// vector to use as VIEW component of MVP matrix.
    /// </summary>
    /// <returns> Returns the view matrix of the camera.</return>
    glm::mat4 getViewMatrix();

	/// <summary>
	/// What the vector of a typical camera front is.
	/// </summary>
	/// <returns>The front vector of the camera</return>
    glm::vec3 getFront();

	/// <summary>
	/// Setter method for the front vector.
	/// </summary>
	/// <param name="front">Reference to a vector which is to be the new front for the camera.</param>
    void setFront(glm::vec3 &front);

    /// <summary>
    /// Updates the typical target of the camera.
	/// <param name="front">Reference to a vector which is to be the new target for the camera.</param>
    void updateTarget(glm::vec3& targetPos);

	/// <summary>
	/// Update the camera based on SDL relative mouse mode inputs.
	/// </summary>
	/// <param name="mouseX">SDL relative mouse x.</param>
	/// <param name="mouseY">SDL relative mouse y.</param>
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
    /// Set the previous x and y values for camera values for comparison to later.
    /// </summary>
	/// <param name="x">Previous x</param>
	/// <param name="y">Previous y</param>
    void Camera3D::setPrevXY(int x, int y);

    /// <summary>
    ///	Method for checking and warping the mouse back into the center of the window to make the
	/// camera just like a typical camera.
    /// </summary>
	/// <param name="window">Reference to the window that is currently being used.</param>
	/// <param name="x">X Value of mouse.</param>
	/// <param name="y">Y Value of mouse.</param>
	/// <param name="windowWidth">Width of the passed window.</param>
	/// <param name="windowHeight">Height of the passed window.</param>
    void Camera3D::checkWarp(SDL_Window* window, int x, int y, int windowWidth,
        int windowHeight);

    /// <summary>
    /// Compute the new position of a camera based on all of the input information.
    /// </summary>
	/// <param name="speed">Typical speed that the character is moving.</param>
	/// <param name="speedLat">Lateral speed that the character is moving.</param>
    void Camera3D::computePos(GLfloat speed, GLfloat speedLat);



private:
	/// Storage variables for a Euler based camera.
    GLfloat yaw, pitch, roll;
    GLfloat sensitivity;

	///Below are vectors for maintaining a camera.
    glm::vec3 pos;
    glm::vec3 dir;
    glm::vec3 target;
    glm::vec3 camRight;
    glm::vec3 camUp;
    glm::vec3 cameraFront;
};
