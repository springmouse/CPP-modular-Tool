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

	MapClass GenerateNewMap(eMapGenTypes type, int n, int scale);

private:
	DiamondSquare * m_diamondSquare;
};

