#pragma once
#include <MapGeneratorClass.h> 
#include <vec3.hpp>

void main()
{
	MapGeneratorClass * mapGen = new MapGeneratorClass();

	MapClass map = mapGen->GenerateNewMap(eMapGenTypes::DIAMONDSQUARE, 2, 9);

	std::string name = "AHHHHHHHHHH";

	return;
}