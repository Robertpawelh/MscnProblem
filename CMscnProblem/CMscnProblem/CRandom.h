#pragma once
#include <random>

using namespace std;

class CRandom{
private:
	mt19937 gen;
public:
	CRandom();
	CRandom(int iInstanceSeed);
	~CRandom();

	int i_random(int min, int max) {
		return uniform_int_distribution<int>{min, max}(gen);
	}

	double d_random(double min, double max) {
		return uniform_real_distribution<double>{min, max}(gen);

	}
};

