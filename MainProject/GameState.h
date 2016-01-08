#pragma once
#include "stdafx.h"

// Enumeration type of the possible gamestates of the game. Used to determine which game loop behaviours to use.
enum class GameState {
    PLAYING, QUITTING
};