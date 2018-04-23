#pragma once
class PerlinNoiseMap
{
public:
	PerlinNoiseMap();
	~PerlinNoiseMap();
	
	void GenderatePerlinNoise(float width, float height, unsigned int seed);
};

