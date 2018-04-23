#include "MapGeneratorClass.h"
#include <iostream>



MapGeneratorClass::MapGeneratorClass()
{
	m_diamondSquare = new DiamondSquare();
}


MapGeneratorClass::~MapGeneratorClass()
{
}

MapClass MapGeneratorClass::GenerateNewMap(eMapGenTypes type, int n, int scale)
{
	MapClass map(n, scale);

	switch (type)
	{
	case DIAMONDSQUARE:
		m_diamondSquare->MidPointDisplaceMeant(& map, 0, map.size - 1, map.size * (map.size - 1), map.g_mapPoints.size() - 1, 0, (map.size / 2) - 1, 10908060607);
		break;

	default:
		std::cout << "Invalid Map Generator Type Passed!!!";
		break;
	}

	map.GenVectors();

	return map;
}
