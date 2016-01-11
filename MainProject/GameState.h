#pragma once
#include "stdafx.h"


/// <summary>
/// Enumeration type of the possible gamestates of the game. Used to determine which game loop behaviours to use.
/// </summary>
enum class GameState {
    PLAYING, QUITTING
};