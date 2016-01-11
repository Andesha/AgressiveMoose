#pragma once

#include "stdafx.h"

class Perlin {

	/// Reference perlin vector.
    std::vector<int> perm; //Perlin noise permutation vector.

public:

	/// <summary>
	/// Default constructor with Ken Perlin's vector.
	/// </summary>
    Perlin();

	/// <summary>
	/// Second constructor with a random permutation vector.
	/// </summary>
	/// <param name="seed">Random number generator seed to base vector off of.</param>
    Perlin(int seed);

	/// <summary>
	/// Sample perlin noise at the input value.
	/// </summary>
	/// <param name="x">X value to sample at.</param>
	/// <param name="y">Y value to sample at.</param>
	/// <returns>Return the value of perlin noise at the given x,y .</return>
    float at(float x, float y); //Function which actually will generate the noise.

private:
    ///Below functions are needed to create our terrain.
    ///All functions below functions are from Ken Perlin: http://mrl.nyu.edu/~perlin/noise/
	double examinePerlin(double x, double y, double z);
    double fade(double t);
    double lerp(double t, double a, double b);
    double grad(int hash, double x, double y, double z);

};