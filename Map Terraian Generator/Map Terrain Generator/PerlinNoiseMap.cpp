#include "PerlinNoiseMap.h"

//S curve over liniear?

PerlinNoiseMap::PerlinNoiseMap()
{
}


PerlinNoiseMap::~PerlinNoiseMap()
{
}

void PerlinNoiseMap::GenderatePerlinNoise(float width, float height, unsigned int seed)
{
}

void PerlinNoiseMap::GenderatePerlinNoise1D(int nCount, float nOctaves, PerlinMapClass * map)
{
	if (map->m_seed.size() != nCount)
	{
		map->GeneratSeed(0, nCount);
		map->GeneratArray();
	}

	for (int x = 0; x < nCount; x++)
	{
		float fNoise = 0.0f;
		float fscale = 1.0f;
		float fscaleAcc = 0.0f;

		for (int o = 0; o < nOctaves; o++)
		{
			int nPitch = nCount >> o;

			int nSample1 = (x / nPitch) * nPitch;
			int nSample2 = (nSample1 + nPitch) % nCount;

			float fBland = (float)(x - nSample1) / (float)nPitch;
			float fSample = (1.0f - fBland) * map->m_seed[nSample1] + fBland * map->m_seed[nSample2];
			fNoise += fSample * fscale;
			fscaleAcc += fscale;

			fscale = fscale / 2;
		}


		map->m_finish[x] = fNoise / fscaleAcc;
	}

}
