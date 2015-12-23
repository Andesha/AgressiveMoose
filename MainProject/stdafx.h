// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently

#pragma once

#include "targetver.h"

#include <windows.h> // Needed by glew to get access to window resizing.
#include <tchar.h>

#include <iostream> // Standard libraries.
#include <fstream>
#include <string>
#include <cstddef>
#include <vector>

#include <SDL\SDL.h> // SDL/Glew for OpenGL behaviours.
#include <GL\glew.h>
#include <glm\glm.hpp>

#include "SimulationGame.h" // Created classes/files.
#include "GameState.h"
#include "TerrainChunk.h"
#include "Vertex.h"
#include "ErrorHandling.h"
#include "GLSLProgram.h"
