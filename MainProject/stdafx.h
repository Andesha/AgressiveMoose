// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently

#pragma once

#include "targetver.h"

#include <windows.h> // Needed by glew to get access to window resizing.
#include <tchar.h>

#include <iostream> // Standard libraries.
#include <fstream>
#include <list>
#include <string>
#include <cstddef>
#include <vector>
#include <numeric>
#include <random>
#include <algorithm>
#include <cmath>

#include <SDL\SDL.h> // SDL/Glew for OpenGL behaviours.
#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include <SOIL\SOIL.h> // Simple OpenGL Image Library

#include "SimulationGame.h" // Created classes/files.
#include "GameState.h"
#include "TerrainChunk.h"
#include "Vertex.h"
#include "ErrorHandling.h"
#include "GLSLProgram.h"
#include "Perlin.h"
#include "Constants.h"
#include "TextureFactory.h"
#include "Camera3D.h"
#include "Character.h"