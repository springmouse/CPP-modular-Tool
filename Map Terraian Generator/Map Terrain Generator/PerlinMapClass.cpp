#include "PerlinMapClass.h"



PerlinMapClass::PerlinMapClass() : MapClass(3, 2)
{
}


PerlinMapClass::~PerlinMapClass()
{
}

void PerlinMapClass::GeneratSeed(unsigned int seed, int count)
{
	if (seed != 0)
	{
		std::srand(seed);
	}

	for (int i = 0; i < count; i++)
	{
		m_seed.push_back((float)std::rand() / (float)RAND_MAX);
	}
}

void PerlinMapClass::GeneratArray()
{
	m_finish.clear();

	for (int i = 0; i < m_seed.size(); i++)
	{
		m_finish.push_back(0);
	}

}
