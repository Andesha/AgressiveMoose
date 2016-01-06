#include "stdafx.h"
#include "Camera3D.h"


// roll is applied by changing camUp based on roll
Camera3D::Camera3D(): yaw(90.0f), pitch(0.0f), roll(0.0f), sensitivity(0.5f){
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    pos = glm::vec3(0.0f, 2.0f, 0.0f);
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
    // Normalize the vectors, because their length gets closer to 0 the more 
    // you look up or down which results in slower movement.
    this->camRight = glm::normalize(glm::cross(this->cameraFront, glm::vec3(0.0f, 1.0f, 0.0f)));  
    this->camUp = glm::normalize(glm::cross(this->camRight, this->cameraFront));
}


glm::vec3 Camera3D::getFront(){
    // std::cout << cameraFront[0] << "\t" << cameraFront[1] << "\t" << cameraFront[2] << "\t" << std::endl;
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
        speedFace = 0.1f;
    }
    if (state[SDL_SCANCODE_A]) {
        speedLat = -1 * 0.1f;

    }
    if (state[SDL_SCANCODE_S]) {
        speedLat = -1 * 0.1f;

    }
    if (state[SDL_SCANCODE_D]) {
        speedLat = 0.1f;
    }
}


void Camera3D::handleKeyUp(){
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_RETURN]) {
        printf("<RETURN> is pressed.\n");
    }
    if (state[SDL_SCANCODE_W]) {
        speedFace = 0.0f;
    }
    if (state[SDL_SCANCODE_A]) {
        speedLat = 0.0f;

    }
    if (state[SDL_SCANCODE_S]) {
        speedLat = 0.0f;

    }
    if (state[SDL_SCANCODE_D]) {
        speedFace = 0.0f;
    }
}


void Camera3D::setPrevXY(int x, int y){
    this->prevX = x;
    this->prevY = y;
}

void Camera3D::checkWarp(SDL_Window* window, int x, int y, int windowWidth,
    int windowHeight){

    // if you're 25% of the way from the border
    int win_top_lim = windowHeight / 4;
    int win_bot_lim = 3 * win_top_lim;
    int win_l_lim = windowWidth / 4;
    int win_r_lim = 3 * win_l_lim;
    if (y < win_top_lim || y > win_bot_lim || x < win_l_lim || x > win_r_lim){
        SDL_WarpMouseInWindow(window, windowWidth / 2, windowHeight / 2);
        this->setPrevXY(windowWidth / 2, windowHeight / 2);
    }
}


void Camera3D::computePos(){

    this->pos += this->cameraFront * 0.01f; 
}