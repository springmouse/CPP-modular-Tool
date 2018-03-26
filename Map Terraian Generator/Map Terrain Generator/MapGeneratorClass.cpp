#include "MapGeneratorClass.h"
#include <iostream>



MapGeneratorClass::MapGeneratorClass()
{
	m_diamondSquare = new DiamondSquare();
}


MapGeneratorClass::~MapGeneratorClass()
{
}

MapClass MapGeneratorClass::GenerateNewMap(eMapGenTypes type, int width, int scale)
{
	MapClass map(width, scale);

	switch (type)
	{
	case DIAMONDSQUARE:
		m_diamondSquare->MidPointDisplaceMeant(& map, 0, map.size - 1, map.size * (map.size - 1), map.g_mapPoints.size() - 1, 0, map.size / 2, 0);
		break;

	default:
		std::cout << "Invalid Map Generator Type Passed!!!";
		break;
	}

	map.GenVectors();

	return map;
}
