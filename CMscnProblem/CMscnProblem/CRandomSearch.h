#pragma once
#include "CMscnProblem.h"

#define NUMBER_OF_ITERATIONS 140000
class CRandomSearch{
private:
	CMscnProblem * pc_problem;
	double* pd_random_solution(CRandom &cGenerator);
public:
	CRandomSearch(CMscnProblem * cProblem);
	~CRandomSearch();

	double * pd_findBestSolution(int iSeed);
};

