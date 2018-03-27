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

	g_mapPoints[0] = 0.5f;
	g_mapPoints[size - 1] = 0.5f;
	g_mapPoints[size * (size - 1)] = 0.5f;
	g_mapPoints[g_mapPoints.size() - 1] = 0.5f;

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
	
	for (int i = 0; i < g_mapVertecs.size(); i++)
	{
		//g_mapVertecs[i] = glm::normalize(g_mapVertecs[i]);
	}
}
