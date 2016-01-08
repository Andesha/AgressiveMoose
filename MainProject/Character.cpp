#pragma once 
#include "stdafx.h"
#include "Character.h"

Character::Character(glm::vec3 position) :
playerPosition(position), speed(0.1f), yaw(0.0f), pitch(0.0f), roll(0.0f),
dir(glm::vec3(0.0f, 0.0f, 1.0f)), charUp(0.0f, 1.0f, 0.0f){

}