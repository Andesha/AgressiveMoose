#pragma once
#include "stdafx.h"

struct LightComponent{
    float r, g, b;
};

struct Material{
    char name[25];
    LightComponent Amb, Diff, Spec;
};