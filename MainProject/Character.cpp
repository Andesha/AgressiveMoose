#pragma once 
#include "stdafx.h"
#include "Character.h"

Character::Character(glm::vec3 position) :
charPos(position), speed(0.1f), yaw(90.0f), pitch(0.0f), roll(0.0f),
dir(glm::vec3(0.0f, 0.0f, 1.0f)), charUp(0.0f, 1.0f, 0.0f){
    target = charPos + glm::vec3(0.0f, 0.0f, 1.0f);
    charFront = glm::normalize(target - pos);
    charRight = glm::normalize(glm::cross(charFront, charUp));
    camera = new Camera3D(charPos, yaw, pitch, roll, 0.5);
}


glm::mat4 Character::getViewMatrix(){
    return camera->getViewMatrix();
}


void Character::updateCharacter(){
    //TODO: APPLY THIRD PERSON LOGIC

    // update character position
    pos += glm::normalize(charFront) * speed;
    // this->pos += this->cameraFront * speedFace;
    // update camera position
    this->camera->computePos(speed, speedLat);
    this->camera->updateTarget(target);
    //test collision?
}