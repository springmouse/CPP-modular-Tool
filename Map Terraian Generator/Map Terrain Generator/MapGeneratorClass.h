#pragma once
#include "DiamondSquare.h"
#include "MapClass.h"

enum eMapGenTypes
{
	DIAMONDSQUARE
};

class MapGeneratorClass
{
public:
	MapGeneratorClass();
	~MapGeneratorClass();

	MapClass GenerateNewMap(eMapGenTypes type, int width, int height);

private:
	DiamondSquare * m_diamondSquare;
};

