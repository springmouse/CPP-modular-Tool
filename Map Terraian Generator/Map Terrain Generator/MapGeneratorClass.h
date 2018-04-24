#pragma once
#include "DiamondSquare.h"
#include "PerlinNoiseMap.h"
#include "MapClass.h"
#include "PerlinMapClass.h"

enum eMapGenTypes
{
	DIAMONDSQUARE,
	PERLINNOISE
};

class MapGeneratorClass
{
public:
	MapGeneratorClass();
	~MapGeneratorClass();

	MapClass GenerateNewMap(eMapGenTypes type, int n, int scale);
	void PerlinNoiseMapGenerator(int outPutSize, int octaves, PerlinMapClass * map);

private:
	DiamondSquare * m_diamondSquare;
	PerlinNoiseMap * m_perlinNoise;
};

