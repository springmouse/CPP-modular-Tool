#include "PerlinNoiseMap.h"

//S curve over liniear?

PerlinNoiseMap::PerlinNoiseMap()
{
	NewSeed((unsigned int)(rand() % 1000001), 255);
	m_repeat = -1;
}


PerlinNoiseMap::~PerlinNoiseMap()
{
}

void PerlinNoiseMap::NewSeed(unsigned int seed, int size)
{
	std::srand(seed);
	m_randomMap.clear();

	m_size = size;

	glm::vec2 grad;
	float delta;

	for (int x = 0; x < m_size; x++)
	{
		for (int y = 0; y < m_size; y++)
		{
			delta = (rand() % 36000) / 100;
			delta *= 0.017453;

			grad.x = std::sin(delta);
			grad.y = std::cos(delta);
			
			m_randomMap.push_back(grad);
		}
	}
}

double PerlinNoiseMap::OctivePerlin(double x, double y, int octaives, double persistence)
{
	double total = 0;
	double frequency = 1;
	double amplitude = 1;
	double maxValue = 0;

	for (int i = 0; i < octaives; i++)
	{
		total += PerlinNoise(x * frequency, y * frequency) * amplitude;
		
		maxValue += amplitude;

		amplitude *= persistence;
		frequency *= 2;
	}

	return total / maxValue;
}

double PerlinNoiseMap::PerlinNoise(float x, float y)
{
	// ensure x and y are within range
	x = fmod(x, 255.0f);
	y = fmod(y, 255.0f);

	// Determine grid cell coordinates
	int x0 = std::floor(x);
	int x1 = x0 + 1;
	int y0 = std::floor(y);
	int y1 = y0 + 1;

	// Determine interpolation weights
	// Could also use higher order polynomial/s-curve here
	float sx = SmoothStep(x - (float)x0);
	float sy = SmoothStep(y - (float)y0);

	// Interpolate between grid point gradients
	float n0, n1, ix0, ix1, value;
	n0 = DotGridGradient(x0, y0, x, y);
	n1 = DotGridGradient(x1, y0, x, y);
	ix0 = Lerp(n0, n1, sx);
	n0 = DotGridGradient(x0, y1, x, y);
	n1 = DotGridGradient(x1, y1, x, y);
	ix1 = Lerp(n0, n1, sx);
	value = Lerp(ix0, ix1, sy);

	// clamp between 0 and 1
	//value = value * 0.5f + 0.5f;

	return value;
}

float PerlinNoiseMap::SmoothStep(float f)
{
	return 6 * std::pow(f, 5) - 15 * std::pow(f, 4) + 10 * std::pow(f, 3);
}

float PerlinNoiseMap::DotGridGradient(int ix, int iy, float x, float y)
{
	// Compute the distance vector
	float dx = x - (float)ix;
	float dy = y - (float)iy;

	// Compute the dot-product
	return (dx * m_randomMap[ix * m_size + iy].x + dy * m_randomMap[ix * m_size + iy].y);
}

double PerlinNoiseMap::Lerp(double a, double b, double x)
{
	return (1.0f - x) * a + x * b;
}