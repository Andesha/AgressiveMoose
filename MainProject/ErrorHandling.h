#pragma once

#include "stdafx.h"

/// <summary>
/// Method for outputting an error to console.
/// Used mostly by our OpenGL/GLSL shader classes.
/// </summary>
/// <param name="error">String to output to console.</param>
extern void outputError(std::string error);