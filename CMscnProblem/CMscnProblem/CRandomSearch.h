#pragma once
#include "CMscnProblem.h"

#define NUMBER_OF_ITERATIONS 100000
class CRandomSearch {
private:
	CMscnProblem * pc_problem;
	double* pd_random_solution(CRandom &cGenerator);
public:
	CRandomSearch(CMscnProblem * pcProblem);
	~CRandomSearch();

	double * pd_findBestSolution(int iSeed);
};

