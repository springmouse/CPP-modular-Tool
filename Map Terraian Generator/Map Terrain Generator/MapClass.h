#pragma once
#include<vec3.hpp>
#include<vector>
#include<ext.hpp>

class MapClass
{
public:
	MapClass(int n, int scale);
	~MapClass();

	void GenVectors();


	std::vector<float> g_mapPoints;
	std::vector<glm::vec3> g_mapVertecs;

	//the size of the array
	int size;

	//the max and min value for the map points
	float min;
	float max;
	

private:
	float m_scale;
};

