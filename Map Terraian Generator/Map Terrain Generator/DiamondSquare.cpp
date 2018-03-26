#include "DiamondSquare.h"



DiamondSquare::DiamondSquare()
{
}


DiamondSquare::~DiamondSquare()
{
}

void DiamondSquare::MidPointDisplaceMeant(MapClass * map, int corner1, int corner2, int corner3, int corner4, int iteration, int maxIteration, unsigned int seed)
{
	if (iteration == maxIteration)
	{
		return;
	}

	if (seed != 0)
	{
		std::srand(seed);
	}

	map->g_mapPoints[corner1] = (std::rand() % 101);
	map->g_mapPoints[corner1] /= 100;
	map->g_mapPoints[corner2] = (std::rand() % 101);
	map->g_mapPoints[corner2] /= 100;
	map->g_mapPoints[corner3] = (std::rand() % 101);
	map->g_mapPoints[corner3] /= 100;
	map->g_mapPoints[corner4] = (std::rand() % 101);
	map->g_mapPoints[corner4] /=100;

	map->g_mapPoints[(corner1 + corner4) / 2] = (std::rand() % 101);
	map->g_mapPoints[(corner1 + corner4) / 2] /=100;

	map->g_mapPoints[(corner1 + corner2) / 2] = (map->g_mapPoints[corner1] + map->g_mapPoints[corner2]) * 0.5f;
	map->g_mapPoints[(corner1 + corner3) / 2] = (map->g_mapPoints[corner1] + map->g_mapPoints[corner3]) * 0.5f;
	map->g_mapPoints[(corner4 + corner2) / 2] = (map->g_mapPoints[corner4] + map->g_mapPoints[corner2]) * 0.5f;
	map->g_mapPoints[(corner4 + corner3) / 2] = (map->g_mapPoints[corner4] + map->g_mapPoints[corner3]) * 0.5f;

	MidPointDisplaceMeant(map, corner1,					(corner1 + corner2) / 2,	(corner1 + corner3) / 2,	(corner1 + corner4) / 2, iteration + 1, maxIteration, seed);

	MidPointDisplaceMeant(map, (corner1 + corner2) / 2,	corner2,					(corner1 + corner4) / 2,	(corner2 + corner4) / 2, iteration + 1, maxIteration, seed);

	MidPointDisplaceMeant(map, (corner1 + corner3) / 2,	(corner1 + corner4) / 2,	corner3,					(corner3 + corner4) / 2, iteration + 1, maxIteration, seed);
	
	MidPointDisplaceMeant(map, (corner1 + corner4) / 2,	(corner2 + corner4) / 2,	(corner3 + corner4) / 2,	corner4,				 iteration + 1, maxIteration, seed);
}
