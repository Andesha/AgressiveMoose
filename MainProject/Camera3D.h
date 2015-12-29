#pragma once
#include "stdafx.h"

/// <summary>
///	Main class for 3d camera object
/// </summary>
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
	glm::vec3 direction;
};

