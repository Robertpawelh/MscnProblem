#pragma once
#include <random>

#define MIN_CD 10
#define MAX_CD 100
#define MIN_CF 10
#define MAX_CF 100
#define MIN_CM 10
#define MAX_CM 100

#define MIN_UD 10
#define MAX_UD 300
#define MIN_UF 10
#define MAX_UF 300
#define MIN_UM 10
#define MAX_UM 300

#define MIN_P 10
#define MAX_P 300

#define MIN_SD 1
#define MAX_SD 200
#define MIN_SF 25
#define MAX_SF 200
#define MIN_SM 50
#define MAX_SM 200
#define MIN_SS 75
#define MAX_SS 200

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

