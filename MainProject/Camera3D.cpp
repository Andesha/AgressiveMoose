#include "stdafx.h"
#include "Camera3D.h"


Camera3D::Camera3D() : yaw(90.0f), pitch(0.0f), roll(0.0f), sensitivity(0.5f) {
	camUp = glm::vec3(0.0f, 1.0f, 0.0f);
	pos = glm::vec3(0.0f, 100.0f, 0.0f);
    target = pos + glm::vec3(0.0f, 0.0f, 1.0f);
	cameraFront = glm::normalize(target - pos);
	camRight = glm::normalize(glm::cross(cameraFront, camUp));
}

Camera3D::Camera3D(glm::vec3 posi, GLfloat yaw, GLfloat pitch, GLfloat roll, float sensitivity):
pos(posi), yaw(90.0f), pitch(0.0f), roll(0.0f), sensitivity(0.5f){
    pos = glm::vec3(0, 100, 0);
    camUp = glm::vec3(0.0f, 1.0f, 0.0f);
    target = pos + glm::vec3(0.0f, 0.0f, 1.0f);
    cameraFront = glm::normalize(target - pos);
    camRight = glm::normalize(glm::cross(cameraFront, camUp));
}

                                                                     
void Camera3D::setPos(glm::vec3 newpos){
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
    return dir;
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


void Camera3D::computePos(GLfloat speed, GLfloat speedLat){
    this->pos += glm::normalize(this->cameraFront) * speed;
	if (speedLat != 0.0f)this->pos += this->camRight * speedLat;
}