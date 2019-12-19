#pragma once
#include <random>

using namespace std;

class CRandom{
private:
	
public:
	CRandom();
	~CRandom();

	int i_random(int min, int max) {
	//	random_device rd;  //Will be used to obtain a seed for the random number engine CO TO
	//	mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd() CO TO
	//	return uniform_int_distribution<int>{min, max}(gen);
	}

	double d_random(double min, double max) {
		using dist = std::conditional_t<
			is_integral<double>::value,
			uniform_int_distribution<double>,
			uniform_real_distribution<double>
		>;
	//	return dist{ min, max }(gen);
	}
};

