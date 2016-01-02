#include "stdafx.h"
#include "Camera3D.h"


// roll is applied by changing camUp based on roll
Camera3D::Camera3D(): yaw(90.0f), pitch(0.0f), roll(0.0f), sensitivity(0.5f), speed(0.01f){
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    pos = glm::vec3(0.0f, 0.2f, 0.0f);
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
   // std::cout << dir[0] << "\t" << dir[1] << "\t" << dir[2] << "\t" << std::endl;
    return dir;
}

void Camera3D::mouseUpdatePos(int mouseX, int mouseY){
    if (!hasMoved){
        hasMoved = true;
        prevX = mouseX;
        prevY = mouseY;
        return;
    }

    GLfloat xoffset = mouseX - prevX;
    GLfloat yoffset = mouseY - prevY;
    prevX = mouseX;
    prevY = mouseY;

    GLfloat sensitivity = 0.1;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    setFront(front);
    this->camRight = glm::normalize(glm::cross(this->cameraFront, glm::vec3(0.0f, 1.0f, 0.0f)));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    this->camUp = glm::normalize(glm::cross(this->camRight, this->cameraFront));
}


glm::vec3 Camera3D::getFront(){
    std::cout << cameraFront[0] << "\t" << cameraFront[1] << "\t" << cameraFront[2] << "\t" << std::endl;
    return cameraFront;
}


void Camera3D::setFront(glm::vec3 &front){
    this->cameraFront = front;
}


glm::mat4 Camera3D::getViewMatrix(){
    return glm::lookAt(this->pos, pos + cameraFront , camUp);
}


void Camera3D::moveKeys(int keyIn){
    GLfloat speed = 0.01;
    switch (keyIn){
 
    case SDLK_w:
        this->pos += speed * this->cameraFront;
        break;
    case SDLK_a:
        this->pos -= speed * this->camRight;
        break;
    case SDLK_s:
        this->pos -= speed * this->cameraFront;
        break;
    case SDLK_d:
        this->pos += speed * this->camRight;

        break;
    default:
        break;
    }

}