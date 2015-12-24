#pragma once
#include "stdafx.h"

class Camera3D {
public:
	Camera3D();
	~Camera3D();

	// setter for position.
	void setPos(glm::vec3& newPos){
		position = newPos;
	}

	// Getter for position.
	glm::vec3 getPos() {
		return position;
	}



private:
	glm::vec3 position;
	glm::mat4 orthoMatrix;
};

