#include "aePerlin.h"

namespace aeEngineSDK
{
	PerlinNoise::PerlinNoise() 
	{

		// Initialize the permutation vector with the reference values
		p = {
			151,160,137,91,90,15,131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,
			8,99,37,240,21,10,23,190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,
			35,11,32,57,177,33,88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,
			134,139,48,27,166,77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,
			55,46,245,40,244,102,143,54, 65,25,63,161,1,216,80,73,209,76,132,187,208, 89,
			18,169,200,196,135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,
			250,124,123,5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,
			189,28,42,223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167,
			43,172,9,129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,
			97,228,251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,
			107,49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
			138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180 };
		// Duplicate the permutation vector
		p.insert(p.end(), p.begin(), p.end());
	}

	// Generate a new permutation vector based on the value of seed
	PerlinNoise::PerlinNoise(uint32 seed) 
	{
		Seed(seed);
	}

	PerlinNoise::PerlinNoise(const PerlinNoise & N)
	{
		*this = N;
	}

	void PerlinNoise::Seed(uint32 seed)
	{
		aeZiggurat Z;

		//Seed random
		Z.Seed(seed);

		//Clear the previous list
		p.clear();

		//Resize vector
		p.resize(512);

		//Fill the vector
		for (uint32 num = 0; num < (uint32)p.size(); num++)
		{
			p[num] = (int32)(255.0 * Z.UDRand());
		}
	}

	double PerlinNoise::Noise(double x, double y, double z) 
	{
		int X;
		int Y;
		int Z;
		double u;
		double v;
		double w;
		int A;
		int AA;
		int AB;
		int B;
		int BA;
		int BB;
		double res;
		// Find the unit cube that contains the point
		X = (int)floor(x) & 255;
		Y = (int)floor(y) & 255;
		Z = (int)floor(z) & 255;

		// Find relative x, y,z of point in cube
		x -= floor(x);
		y -= floor(y);
		z -= floor(z);

		// Compute fade curves for each of x, y, z
		u = fade(x);
		v = fade(y);
		w = fade(z);

		// Hash coordinates of the 8 cube corners
		A = p[X] + Y;
		AA = p[A] + Z;
		AB = p[A + 1] + Z;
		B = p[X + 1] + Y;
		BA = p[B] + Z;
		BB = p[B + 1] + Z;

		// Add blended results from 8 corners of cube
		res =
			lerp(
				w, lerp(
					v, lerp(
						u, grad(p[AA], x, y, z), grad(p[BA], x - 1, y, z)
						),
					lerp(
						u, grad(p[AB], x, y - 1, z), grad(p[BB], x - 1, y - 1, z)
						)
					),
				lerp(
					v, lerp(
						u, grad(p[AA + 1], x, y, z - 1), grad(p[BA + 1], x - 1, y, z - 1)
						),
					lerp(
						u, grad(p[AB + 1], x, y - 1, z - 1), grad(p[BB + 1], x - 1, y - 1, z - 1)
						)
					)
				);
		return (res + 1.0) * 0.5;
	}

	double PerlinNoise::fade(double t) {
		return t * t * t * (t * (t * 6 - 15) + 10);
	}

	double PerlinNoise::lerp(double t, double a, double b) {
		return a + t * (b - a);
	}

	double PerlinNoise::grad(int hash, double x, double y, double z) {
		int h = hash & 15;
		// Convert lower 4 bits of hash inot 12 gradient directions
		double u = h < 8 ? x : y,
			v = h < 4 ? y : h == 12 || h == 14 ? x : z;
		return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
	}

	FractalNoise::FractalNoise() {
		m_pPerlin = PerlinNoise();

		m_nOctaves = 10;
		m_dLacunarity = 2.0;
		m_dPersistence = 0.5;
		m_dBaseFrequency = 1.0;
		m_dBaseAmplitude = 1.0;
		m_dScale = 1.0;
	}

	FractalNoise::FractalNoise(unsigned long seed) {
		m_pPerlin = PerlinNoise(seed);

		m_nOctaves = 10;
		m_dLacunarity = 2.0;
		m_dPersistence = 0.5;
		m_dBaseFrequency = 1.0;
		m_dBaseAmplitude = 1.0;
		m_dScale = 1.0;
	}

	FractalNoise::FractalNoise(const FractalNoise & N)
	{
		*this = N;
	}

	FractalNoise::~FractalNoise() {
	}

	double FractalNoise::Noise(double sample_x, double sample_y, double sample_z) {
		double sum = 0;
		double freq = m_dBaseFrequency;
		double amp = m_dBaseAmplitude;
		double MaxAmp = 0;
		double scaled_x = sample_x*m_dScale;
		double scaled_y = sample_y*m_dScale;
		double scaled_z = sample_x*m_dScale;

		for (int i = 0; i < m_nOctaves; ++i) {
			sum += m_pPerlin.Noise(scaled_x*freq, scaled_y*freq, scaled_z*freq)*amp;
			MaxAmp += amp;
			freq *= m_dLacunarity;
			amp *= m_dPersistence;
		}
		sum /= MaxAmp;

		return sum;
	}

	void FractalNoise::Seed(uint32 seed)
	{
		m_pPerlin.Seed(seed);
	}

	void FractalNoise::SetOctaves(int o) {
		if (o > 0) {
			m_nOctaves = o;
		}
	}

	void FractalNoise::SetPersistence(double p) {
		m_dPersistence = p;
	}

	void FractalNoise::SetLacunarity(double l) {
		m_dLacunarity = l;
	}

	void FractalNoise::SetBaseFrequency(double f) {
		m_dBaseFrequency = f;
	}

	void FractalNoise::SetBaseAmplitude(double a) {
		m_dBaseAmplitude = a;
	}

	void FractalNoise::SetScale(double s)
	{
		m_dScale = s;
	}

	
}