#pragma once
#include "CRandomSearch.h"
#include "CIndividual.h"
#include <vector>

#define	NUMBER_OF_ITERATIONS 100000
#define POPULATION_SIZE 15
#define CROSS_PROBABILITY 0.4
#define DIFF_WEIGHT  1.2

using namespace std;

class CDiffEvol{
private:
	CMscnProblem * pc_problem;
	bool b_check_stop_condition(int iCounter); // konwencja
public:
	CDiffEvol(CMscnProblem * pcProblem);
	~CDiffEvol();

	double* pdFindBestSolution(int iSeed);
};

