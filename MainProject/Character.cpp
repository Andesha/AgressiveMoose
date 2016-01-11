#pragma once 
#include "stdafx.h"
#include "Character.h"

Character::Character(glm::vec3 position) :
pos(position), speed(0.0f), yaw(90.0f), pitch(0.0f), roll(0.0f),
dir(glm::vec3(0.0f, 0.0f, 1.0f)), charUp(0.0f, 1.0f, 0.0f){
    target = pos + glm::vec3(0.0f, 0.0f, 1.0f);
    charFront = glm::normalize(target - pos);
    charRight = glm::normalize(glm::cross(charFront, charUp));

    camera = new Camera3D(pos, yaw, pitch, roll, 0.5);

}

Character::Character() {
}

glm::mat4 Character::getViewMatrix(){
    return camera->getViewMatrix();
}

void Character::setPos(glm::vec3 posi) {
	this->pos = posi;
	this->camera->setPos(pos);
}

void Character::updateCharacter(){
    //TODO: APPLY THIRD PERSON LOGIC

    // update character position
    pos += glm::normalize(charFront) * speed;
    if (speedLat != 0.0f)
        pos += glm::normalize(charRight) * speedLat;
    //// update camera position
    this->camera->setPos(pos);
    //test collision?
}

void Character::setSpeed(GLfloat spd){
    this->speed = spd;
}

void Character::setLatSpeed(GLfloat spd){
    this->speedLat = spd;
}

GLfloat Character::getSpeed(){
    return speed;
}

glm::vec3 Character::getPos(){
    return this->camera->pos;
}

void Character::applyMouseInput(int mouseX, int mouseY){
    GLfloat sensitivity = 0.1;
    GLfloat xoffset = mouseX;
    GLfloat yoffset = mouseY;

    xoffset *= sensitivity;
    yoffset *= -sensitivity;
    
    yaw += xoffset;
    pitch += yoffset;
    
    if (pitch > 89.0f)
    pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

	// Above changes are considered to be all mouse input.
    
    charUp = glm::vec3(0.0f, 1.0f, 0.0f); // Defining up relative to world space.
    charFront = glm::vec3(1.0f, 0.0f, 0.0f); // Define front relative to world space.
    
    glm::mat4 rotationMat(1); // Fun way to get the front vector to rotate around up by yaw.
    rotationMat = glm::rotate(rotationMat, glm::radians(-yaw), charUp);
    charFront = glm::vec3(rotationMat * glm::vec4(charFront, 1.0));
    
    charRight = glm::cross(charFront, charUp); // Cross of front and up.
    
    rotationMat = glm::mat4(1); // Get new rotation identity matrix.
    rotationMat = glm::rotate(rotationMat, glm::radians(pitch), charRight); // Rotate the char front and up by pitch this time.
    charFront = glm::vec3(rotationMat * glm::vec4(charFront, 1.0));
    charUp = glm::vec3(rotationMat * glm::vec4(charUp, 1.0));

    camera->camUp = charUp; // Pass through to the camera.
    camera->cameraFront = charFront;
    camera->camRight = charRight;
}