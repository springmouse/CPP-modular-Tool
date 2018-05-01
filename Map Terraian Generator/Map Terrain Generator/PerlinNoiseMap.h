#pragma once

//http://flafla2.github.io/2014/08/09/perlinnoise.html
//http://mrl.nyu.edu/~perlin/paper445.pdf

#include "MapClass.h"

#include <vec2.hpp>
#include <vector>

class PerlinNoiseMap
{
public:
	PerlinNoiseMap();
	~PerlinNoiseMap();
	
	void NewSeed(unsigned int seed);
	
	double PerlinNoise(float x, float y);

	double OctivePerlin(double x, double y, int octaives, double persistence);

	float SmoothStep(float f);

	float DotGridGradient(int ix, int iy, float x, float y);
	
	static double Lerp(double a, double b, double x);

private:
	int m_repeat;

	std::vector<glm::vec2> m_randomMap;

	int size;
};

