#pragma once

#include "stdafx.h"

class Perlin {

    std::vector<int> perm; //Perlin noise permutation vector.

public:

    Perlin(); //Default constructor with Ken Perlin's vector.

    Perlin(int seed); //Only constructor forces us to use a random seed.

    double at(double x, double y, double z); //Function which actually will generate the noise.

private:
    //Below functions are needed to create our image.
    //All functions below functions are from Ken Perlin: http://mrl.nyu.edu/~perlin/noise/

    double fade(double t);

    double lerp(double t, double a, double b);

    double grad(int hash, double x, double y, double z);

};