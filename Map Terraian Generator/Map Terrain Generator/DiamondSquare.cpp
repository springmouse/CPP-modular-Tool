#include "DiamondSquare.h"
#include <thread>


DiamondSquare::DiamondSquare()
{
}


DiamondSquare::~DiamondSquare()
{
}

/*
void DiamondSquare::MidPointDisplaceMeant(MapClass * map, int c1, int c2, int c3, int c4, int iteration, int maxIteration, unsigned int seed)
{
	//c1 bottem left
	//c2 bottom right
	//c3 top left
	//c4 top right

	if (iteration == maxIteration)
	{
		return;
	}

	if (seed != 0)
	{
		std::srand(seed);
	}

	float lower = -100 + (5 * iteration);
	float upper = 100 - (5 * iteration);
	
	//std::cout << glm::linearRand(lower, upper) << std::endl;
	//std::rand() % ((int)upper * 2)
	//std::cout << map->g_mapPoints[50] << std::endl;

	//e1 bottom middle
	//e2 middle left
	//e3 middle right
	//e4 top middle

	int midPoint = (c1 + c4 + c3 + c2) / 4;
	int e1 = (c1 + c2) / 2, e2 = (c1 + c3) / 2, e3 = (c2 + c4) / 2, e4 = (c3 + c4) / 2;

	//std::cout << midPoint << ", " << e1 << ", " << e2 << ", " << e3 << ", " << e4 << "n\n\ " ;
	
	if(map->g_mapPoints[midPoint] == 0)
		map->g_mapPoints[midPoint] += ((map->g_mapPoints[c1] + map->g_mapPoints[c2] + map->g_mapPoints[c3] + map->g_mapPoints[c4]) / 4) + glm::linearRand(lower, upper);

	if (map->g_mapPoints[e1] == 0)
		map->g_mapPoints[e1] += ((map->g_mapPoints[c1] + map->g_mapPoints[midPoint] + map->g_mapPoints[c2]) / 3) + glm::linearRand(lower, upper);

	if(map->g_mapPoints[e2] == 0)
		map->g_mapPoints[e2] += ((map->g_mapPoints[c1] + map->g_mapPoints[midPoint] + map->g_mapPoints[c3]) / 3) + glm::linearRand(lower, upper);

	if(map->g_mapPoints[e3] == 0)
		map->g_mapPoints[e3] += ((map->g_mapPoints[c2] + map->g_mapPoints[midPoint] + map->g_mapPoints[c4]) / 3) + glm::linearRand(lower, upper);

	if(map->g_mapPoints[e4] == 0)
		map->g_mapPoints[e4] += ((map->g_mapPoints[c3] + map->g_mapPoints[midPoint] + map->g_mapPoints[c4]) / 3) + glm::linearRand(lower, upper);

	MidPointDisplaceMeant(map, c1, e1, e2, midPoint, iteration + 1, maxIteration, 0);
	MidPointDisplaceMeant(map, e1, c2, midPoint, e3, iteration + 1, maxIteration, 0);
	MidPointDisplaceMeant(map, e2, midPoint, c3, e4, iteration + 1, maxIteration, 0);
	MidPointDisplaceMeant(map, midPoint, e3, e4, c4, iteration + 1, maxIteration, 0);

	if (iteration == 0)
	{
		std::cout << "Hit" << std::endl;

		float div = 0;

		for (int i = 0; i < map->g_mapPoints.size(); i++)
		{
			if (abs(map->g_mapPoints[i]) > div)
			{
				div = abs(map->g_mapPoints[i]);
			}
		}

		float min = 0, max = 0;

		for (int i = 0; i < map->g_mapPoints.size(); i++)
		{
			map->g_mapPoints[i] = map->g_mapPoints[i] / div;
			
			min > map->g_mapPoints[i] ? min = map->g_mapPoints[i] : min;
			max < map->g_mapPoints[i] ? max = map->g_mapPoints[i] : max;
		}

		map->min = min;
		map->max = max;
	}
}
*/


void DiamondSquare::MidPointDisplaceMeant(MapClass * map, int c1, int c2, int c3, int c4, int iteration, int maxIteration, unsigned int seed)
{

	if (seed != 0)
	{
		std::srand(seed);
	}

	float stepSize = (int)(map->size - 1);
	float lower = -0.1f;
	float upper = 0.1f;

	while (stepSize > 1)
	{
		int halfStep = stepSize / 2;

		for (int x = 0; (x * stepSize) < map->size -1; x ++)
		{
			for (int y = 0; (y * stepSize) < map->size -1; y ++)
			{
				int e1 = (stepSize * x) + (map->size * (stepSize * y));
				int e2 = ((stepSize * x) + stepSize + (map->size * (stepSize * y)));
				int e3 = (stepSize * x) + (map->size * stepSize) + (map->size * (stepSize * y));
				int e4 = (stepSize * x) + (map->size * stepSize) + stepSize + (map->size * (stepSize * y));

				float botLeft = map->g_mapPoints[e1];
				float botRight = map->g_mapPoints[e2];
				float topLeft = map->g_mapPoints[e3];
				float topRight = map->g_mapPoints[e4];

				float avg = (topLeft + topRight + botLeft + botRight) / 4;
				float rand = glm::linearRand(lower, upper);
				map->g_mapPoints[(e1 + e2 + e3 + e4) / 4] = avg + rand;
			}
		}

		bool even = true;
		for (int x = 0; x < map->size; x += halfStep)
		{
			float xStart = even ? 0 : halfStep;

			for (int y = 0; y < map->size; y += halfStep)
			{
				int e1;
				int e2;
				int e3;
				int e4;

				float left = 0;
				float right = 0;
				float up = 0;
				float down = 0;

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

	float div = 0;

	for (int i = 0; i < map->g_mapPoints.size(); i++)
	{
		if (abs(map->g_mapPoints[i]) > div)
		{
			div = abs(map->g_mapPoints[i]);
		}
	}
	
	for (int i = 0; i < map->g_mapPoints.size(); i++)
	{
		map->g_mapPoints[i] = abs(map->g_mapPoints[i] / div);
	}
}
