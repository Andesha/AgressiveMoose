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
		pos = newPos;
	}

	// Getter for position.
	glm::vec3 getPos() {
		return pos;
	}

  // setter for direction.
  void setPos(glm::vec3& newDir){
      dir = newDir;
  }

  // Getter for direction.
  glm::vec3 getPos() {
      return pos;
  }

private:
	glm::vec3 pos;
	glm::vec3 dir;
  glm::vec3 target;
  glm::vec3 camRight;
  glm::vec3 camUp
};

