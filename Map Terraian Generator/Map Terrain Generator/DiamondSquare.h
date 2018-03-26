#pragma once
#include <vec3.hpp>
#include <iostream>
#include "MapClass.h"

class DiamondSquare
{
public:
	DiamondSquare();
	~DiamondSquare();

	void MidPointDisplaceMeant(MapClass * map, int corner1, int corner2, int corner3, int corner4, int iteration, int maxIteration, unsigned int seed);

};

