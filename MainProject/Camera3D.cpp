#include "stdafx.h"
#include "Camera3D.h"


Camera3D::Camera3D() : yaw(90.0f), pitch(0.0f), roll(0.0f), sensitivity(0.5f), speedFace(0.0f), speedLat(0.0f) {
	camUp = glm::vec3(0.0f, 1.0f, 0.0f);
	pos = glm::vec3(0.0f, 0.0f, 0.0f);
    target = pos + glm::vec3(0.0f, 0.0f, 1.0f);
	cameraFront = glm::normalize(target - pos);
	camRight = glm::normalize(glm::cross(cameraFront, camUp));
}
                                                                     
void Camera3D::setPos(glm::vec3& newpos){
    pos = newpos;
}

glm::vec3 Camera3D::getPos(){
    return pos;
}

void Camera3D::setDir(glm::vec3& newdir){
    dir = newdir;
}

void Camera3D::updateTarget(glm::vec3& targetPos){
    cameraFront = glm::normalize(targetPos - pos);
}

glm::vec3 Camera3D::getDir(){
	// std::cout << dir[0] << "\t" << dir[1] << "\t" << dir[2] << "\t" << std::endl;
    return dir;
}

void Camera3D::mouseUpdatePos(int mouseX, int mouseY){



    GLfloat sensitivity = 0.1;
    mouseX *= sensitivity;
    mouseY *= -sensitivity;

    yaw += mouseX;
    pitch += mouseY;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

	camUp = glm::vec3(0.0f, 1.0f, 0.0f); // Defining up relative to world space.
	cameraFront = glm::vec3(1.0f, 0.0f, 0.0f); // Define front relative to world space.

	glm::mat4 rotationMat(1); // Fun way to get the front vector to rotate around up by yaw.
	rotationMat = glm::rotate(rotationMat, glm::radians(-yaw), camUp);
	cameraFront = glm::vec3(rotationMat * glm::vec4(cameraFront, 1.0));

	camRight = glm::cross(cameraFront,camUp); // Cross of front and up.

	rotationMat = glm::mat4(1);
	rotationMat = glm::rotate(rotationMat, glm::radians(pitch), camRight);
	cameraFront = glm::vec3(rotationMat * glm::vec4(cameraFront, 1.0));
	camUp = glm::vec3(rotationMat * glm::vec4(camUp, 1.0));
}


glm::vec3 Camera3D::getFront(){
    return cameraFront;
}


void Camera3D::setFront(glm::vec3 &front){
    this->cameraFront = front;
}


glm::mat4 Camera3D::getViewMatrix(){
    return glm::lookAt(this->pos, pos + cameraFront , camUp);
}


void Camera3D::handleKeyDown(){
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_RETURN]) {
        printf("<RETURN> is pressed.\n");
    }
    if (state[SDL_SCANCODE_W]) {
        speedFace = 0.75f;
    }
    if (state[SDL_SCANCODE_A]) {
        speedLat = -0.5f;
    }
    if (state[SDL_SCANCODE_S]) {
		speedFace = -0.75f;
    }
    if (state[SDL_SCANCODE_D]) {
        speedLat = 0.5f;
    }
	if (state[SDL_SCANCODE_LSHIFT]) {
		speedFace= 1.75f;
	}
}


void Camera3D::handleKeyUp(){
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_W] == 0 && state[SDL_SCANCODE_S]== 0) {
        speedFace = 0.0f;
    }
    if (state[SDL_SCANCODE_S] == 0 && state[SDL_SCANCODE_D] ==0) {
        speedLat = 0.0f;
    }
}


void Camera3D::computePos(){
    this->pos += this->cameraFront * speedFace;
	if (speedLat != 0.0f)this->pos += this->camRight * speedLat;
}