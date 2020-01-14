#pragma once
#include "CMscnProblem.h"
#include "CRandomSolutionGenerator.h"
#define NUMBER_OF_ITERATIONS 200000
#define STARTING_VALUES_RAND_SEARCH_DIVIDER 1 //max(max(pc_problem->iGetD(), pc_problem->iGetF()), max(pc_problem->iGetM(), pc_problem->iGetS()))

class CRandomSearch {
private:
	CMscnProblem * pc_problem;
public:
	CRandomSearch(CMscnProblem * pcProblem);
	~CRandomSearch();

	double * pdFindBestSolution(int iSeed);
};

