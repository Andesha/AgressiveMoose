#pragma once

#include "stdafx.h"

class Perlin {

    std::vector<int> perm; //Perlin noise permutation vector.

public:

    Perlin(); //Default constructor with Ken Perlin's vector.

    Perlin(int seed); //Only constructor forces us to use a random seed.

    float at(float x, float y); //Function which actually will generate the noise.

private:
    //Below functions are needed to create our image.
    //All functions below functions are from Ken Perlin: http://mrl.nyu.edu/~perlin/noise/

	double examinePerlin(double x, double y, double z);

    double fade(double t);

    double lerp(double t, double a, double b);

    double grad(int hash, double x, double y, double z);

};