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
	CRandom c_generator;
	double d_best_quality;
public:
	CRandomSearch(CProblem * pcProblem, int iSeed);

	~CRandomSearch() {
	}

//	double * pdFindBestSolution(int iSeed);

	void vInitialize();
	void vRunIteration();
};

