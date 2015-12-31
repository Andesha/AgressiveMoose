#include "stdafx.h"
#include "Camera3D.h"


Camera3D::Camera3D(){
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    pos = glm::vec3(-6.0f, 1.0f, -3.0f);
    target = glm::vec3(0.0f, 1.0f, 0.0f);
    dir = glm::normalize(pos - target);
    camRight = glm::normalize(glm::cross(up, dir));
    camUp = glm::normalize(glm::cross(dir, camRight));
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

glm::mat4 Camera3D::getViewMatrix(){
    return glm::lookAt(this->pos, target, glm::vec3(0.0f, 1.0f, 0.0f));
}
