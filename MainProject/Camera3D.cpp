#include "stdafx.h"
#include "Camera3D.h"


Camera3D::Camera3D(){
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    pos = glm::vec3(0.0f, 0.0f, 5.0f);
    target = glm::vec3(0.0f, 0.0f, 0.0f);
    dir = glm::normalize(pos - target);
    camRight = glm::normalize(glm::cross(up, dir));
    camUp = glm::normalize(glm::cross(dir, camRight));
    cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
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

glm::vec3 Camera3D::getDir(){
    return dir;
}

void Camera3D::incPos(){
    pos = pos + glm::vec3(0.001f,0.0f,0.001f);
}

void Camera3D::setFront(glm::vec3 &front){
    this->cameraFront = front;
}


glm::mat4 Camera3D::getViewMatrix(){
    return glm::lookAt(this->pos, pos + cameraFront , camUp);
}
