#include "DiamondSquare.h"



DiamondSquare::DiamondSquare()
{
}


DiamondSquare::~DiamondSquare()
{
}

/*
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

	float i = (std::rand() % 101) - 50;

	//if (iteration == 0)
	//{
	//	i /= 100;
	//	map->g_mapPoints[corner1] += i;
	//
	//	i = (std::rand() % 101) - 50;
	//	i /= 100;
	//	map->g_mapPoints[corner2] += i;
	//
	//	i = (std::rand() % 101) - 50;
	//	i /= 100;
	//	map->g_mapPoints[corner3] += i;
	//
	//	i = (std::rand() % 101) - 50;
	//	i /= 100;
	//	map->g_mapPoints[corner4] += i;
	//}

	map->g_mapPoints[(corner1 + corner4) / 2] += (map->g_mapPoints[corner1] + map->g_mapPoints[corner2] + map->g_mapPoints[corner3] + map->g_mapPoints[corner4]) * 0.25f;

	i = (std::rand() % 101) - 50;
	i /= 100;
	map->g_mapPoints[(corner1 + corner4) / 2] = i;

	i = (std::rand() % 101) - 50;
	i /= 100;
	map->g_mapPoints[(corner1 + corner2) / 2] += (map->g_mapPoints[corner1] + map->g_mapPoints[corner2]) * 0.5f;
	map->g_mapPoints[(corner1 + corner2) / 2] += i;

	i = (std::rand() % 101) - 50;
	i /= 100;
	map->g_mapPoints[(corner1 + corner3) / 2] += (map->g_mapPoints[corner1] + map->g_mapPoints[corner3]) * 0.5f;
	map->g_mapPoints[(corner1 + corner3) / 2] += i;

	i = (std::rand() % 101) - 50;
	i /= 100;
	map->g_mapPoints[(corner4 + corner2) / 2] += (map->g_mapPoints[corner4] + map->g_mapPoints[corner2]) * 0.5f;
	map->g_mapPoints[(corner4 + corner2) / 2] += i;

	i = (std::rand() % 101) - 50;
	i /= 100;
	map->g_mapPoints[(corner4 + corner3) / 2] += (map->g_mapPoints[corner4] + map->g_mapPoints[corner3]) * 0.5f;
	map->g_mapPoints[(corner4 + corner3) / 2] += i;

	MidPointDisplaceMeant(map, corner1,					(corner1 + corner2) / 2,	(corner1 + corner3) / 2,	(corner1 + corner4) / 2, iteration + 1, maxIteration, seed);

	MidPointDisplaceMeant(map, (corner1 + corner2) / 2,	corner2,					(corner1 + corner4) / 2,	(corner2 + corner4) / 2, iteration + 1, maxIteration, seed);

	MidPointDisplaceMeant(map, (corner1 + corner3) / 2,	(corner1 + corner4) / 2,	corner3,					(corner3 + corner4) / 2, iteration + 1, maxIteration, seed);
	
	MidPointDisplaceMeant(map, (corner1 + corner4) / 2,	(corner2 + corner4) / 2,	(corner3 + corner4) / 2,	corner4,				 iteration + 1, maxIteration, seed);
}
*/

void DiamondSquare::MidPointDisplaceMeant(MapClass * map, int corner1, int corner2, int corner3, int corner4, int iteration, int maxIteration, unsigned int seed)
{
	float stepSize = map->size - 1;
	float lower = -0.1f;
	float upper = 0.1f;

	while (stepSize > 1)
	{
		int halfStep = stepSize / 2;

		for (int x = 0; x < map->size -1; x += stepSize)
		{
			for (int y = 0; y < map->size -1; y += stepSize)
			{
				float topLeft = map->g_mapPoints[x + (map->size * y)];
				float topRight = map->g_mapPoints[x + stepSize + (map->size * y)];
				float botLeft = map->g_mapPoints[x + ((map->size * y) + stepSize)];
				float botRight = map->g_mapPoints[(x + stepSize + ((map->size * y) + stepSize))];

				float avg = (topLeft + topRight + botLeft + botRight) / 4;
				float rand = glm::linearRand(lower, upper);
				map->g_mapPoints[x + halfStep + ((map->size * y) + halfStep)] = avg + rand;
			}
		}

		bool even = true;
		for (int x = 0; x < map->size; x += halfStep)
		{
			float xStart = even ? 0 : halfStep;

			for (int y = 0; y < map->size; y += halfStep)
			{
				float left = x - halfStep < 0 ? 0 : map->g_mapPoints[x - halfStep + (map->size * y)];
				float right = x + halfStep >= map->size ? 0 : map->g_mapPoints[x + halfStep + (map->size * y)];
				float up;
				if (x + ((map->size * y) + halfStep) > map->g_mapPoints.size() || y ==0)
				{
					up = 0;
				}
				else
				{
					up = map->g_mapPoints[x + ((map->size * y) - halfStep)];
				}

				float down;
				if (y == 0)
				{
					down = 0;
				}
				else
				{
					down = map->g_mapPoints[x + ((map->size * y) - halfStep)];
				}

				float avg = (left + right + up + down) / 4;
				float rand = glm::linearRand(lower, upper);
				map->g_mapPoints[x + (map->size * y)] = avg + rand;
			}
			even = !even;
		}

		stepSize /= 2;
		lower += 0.005f;
		upper += 0.005f;
	}
}