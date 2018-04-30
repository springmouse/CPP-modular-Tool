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
	
	double PerlinNoise(double x, double y, double z);

	double OctivePerlin(double x, double y, double z, int octaives, double persistence);

	int Inc(int num);
	
	static double Fade(double t)
	{
		return t * t * t * (t *(t * 6 - 15) + 10);
	}

	static double Grad(int hash, double x, double y, double z)
	{
		switch (hash & 0xF)
		{
			case 0x0: return  x + y;
			case 0x1: return -x + y;
			case 0x2: return  x - y;
			case 0x3: return -x - y;
			case 0x4: return  x + z;
			case 0x5: return -x + z;
			case 0x6: return  x - z;
			case 0x7: return -x - z;
			case 0x8: return  y + z;
			case 0x9: return -y + z;
			case 0xA: return  y - z;
			case 0xB: return -y - z;
			case 0xC: return  y + x;
			case 0xD: return -y + z;
			case 0xE: return  y - x;
			case 0xF: return -y - z;
			default: return 0;	// never happens
		}
	}

	static double Lerp(double a, double b, double x)
	{
		return a + x * (b - a);
	}

private:
	int m_repeat;

	int m_permutation[256];
	int p[512];

	std::vector<glm::vec3> m_randomMap;

	int size;
};

