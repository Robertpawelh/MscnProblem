#pragma once
#include "CMscnProblem.h"
#include "CRandom.h"
//#include "CRandomSolutionGenerator.h"
#include "COptimizer.h"

#define NUMBER_OF_ITERATIONS 200000
#define STARTING_VALUES_RAND_SEARCH_DIVIDER 1 //max(max(pc_problem->iGetD(), pc_problem->iGetF()), max(pc_problem->iGetM(), pc_problem->iGetS()))

class CRandomSearch : public COptimizer {
private:
//	CMscnProblem * pc_problem;
public:
	CRandomSearch(CProblem * pcProblem) {
		pc_problem = pcProblem;
	}

	~CRandomSearch() {
	}

	double * pdFindBestSolution(int iSeed);
};

