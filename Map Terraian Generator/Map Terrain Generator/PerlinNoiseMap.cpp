#include "PerlinNoiseMap.h"

//S curve over liniear?

PerlinNoiseMap::PerlinNoiseMap()
{
	NewSeed((unsigned int)(rand() % 1000001));
	m_repeat = -1;
}


PerlinNoiseMap::~PerlinNoiseMap()
{
}

void PerlinNoiseMap::NewSeed(unsigned int seed)
{
	std::srand(seed);
	std::vector<int> List;

	for (int i = 0; i < 256; i++)
	{
		List.push_back(i);
	}

	int n;
	for (int i = 0; i < 256; i++)
	{
		n = rand() % List.size();
		m_permutation[i] = List[n];

		List.erase(List.begin() + n);
	}

	for (int i = 0; i < 512; i++)
	{
		p[i] = m_permutation[i % 256];
	}
}

double PerlinNoiseMap::OctivePerlin(double x, double y, double z, int octaives, double persistence)
{
	double total = 0;
	double frequency = 1;
	double amplitude = 1;
	double maxValue = 0;

	for (int i = 0; i < octaives; i++)
	{
		total += PerlinNoise(x * frequency, y * frequency, z * frequency) * amplitude;
		
		maxValue += amplitude;

		amplitude *= persistence;
		frequency *= 2;
	}

	return total / maxValue;
}

double PerlinNoiseMap::PerlinNoise(double x, double y, double z)
{
	if (m_repeat > 0)
	{
		x = (x - (int)x) + ((int)x % m_repeat);
		y = (y - (int)y) + ((int)y % m_repeat);
		z = (z - (int)z) + ((int)z % m_repeat);
	}

	int xi = (int)x % 255;
	int yi = (int)y % 255;
	int zi = (int)z % 255;

	double xf = x - (int)x;
	double yf = y - (int)y;
	double zf = z - (int)z;

	double u = Fade(xf);
	double v = Fade(yf);
	double w = Fade(zf);

	int aaa, aba, aab, abb, baa, bba, bab, bbb;
	aaa = p[p[p[	xi  ] +		yi ] +	   zi ];
	aba = p[p[p[	xi  ] +Inc(yi) ] + 	   zi ];
	aab = p[p[p[	xi  ] +		yi ] +Inc(zi) ];
	abb = p[p[p[	xi  ] +Inc(yi) ] +Inc(zi) ];
	baa = p[p[p[Inc(xi) ] +		yi ] +	   zi ];
	bba = p[p[p[Inc(xi) ] +Inc(yi) ] +	   zi ];
	bab = p[p[p[Inc(xi) ] +		yi ] +Inc(zi) ];
	bbb = p[p[p[Inc(xi) ] +Inc(yi) ] +Inc(zi) ];

	double  x1, x2, y1, y2;
	x1 = Lerp(	Grad(aaa, xf, yf, zf),
				Grad(baa, xf-1, yf, zf),
				u);

	x2 = Lerp(	Grad(aba, xf, yf - 1, zf),
				Grad(bab, xf - 1, yf - 1, zf),
				u);

	y1 = Lerp(x1, x2, v);

	x1 = Lerp(	Grad(aab, xf, yf, zf - 1),
				Grad(bab, xf - 1, yf, zf - 1),
				u);

	x1 = Lerp(	Grad(abb, xf, yf - 1, zf - 1),
				Grad(bbb, xf - 1, yf - 1, zf - 1),
				u);

	y2 = Lerp(x1, x2, v);

	return (Lerp(y1, y2, w) + 1) / 2;
}

int PerlinNoiseMap::Inc(int num)
{
	num++;
	
	if (m_repeat > 0)
	{
		num %= m_repeat;
	}

	return num;
}