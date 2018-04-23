#include "MapClass.h"



MapClass::MapClass(int n, int scale)
{
	size = std::pow(2, n) + 1;
	m_scale = scale;

	for (int x = 0; x < size; x++)
	{
		for (int y = 0; y < size; y++)
		{
			g_mapPoints.push_back(0);
		}
	}
}


MapClass::~MapClass()
{
}

void MapClass::GenVectors()
{
	for (int x = 0; x < size; x++)
	{
		for (int y = 0; y < size; y++)
		{
			g_mapVertecs.push_back(glm::vec3(x, y, g_mapPoints[x + size * y] * m_scale));
		}
	}	
}
