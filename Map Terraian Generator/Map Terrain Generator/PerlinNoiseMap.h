#pragma once

#include "MapClass.h"
#include "PerlinMapClass.h"

class PerlinNoiseMap
{
public:
	PerlinNoiseMap();
	~PerlinNoiseMap();
	
	void GenderatePerlinNoise(float width, float height, unsigned int seed);

	void GenderatePerlinNoise1D(int nCount, float nOctaves, PerlinMapClass * map);
};

