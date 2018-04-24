#pragma once
#include "MapClass.h"

class PerlinMapClass :
	public MapClass
{
public:
	PerlinMapClass();
	~PerlinMapClass();

	void GeneratSeed(unsigned int seed, int count);
	void GeneratArray();

	std::vector<float> m_seed;
	std::vector<float> m_finish;
};

