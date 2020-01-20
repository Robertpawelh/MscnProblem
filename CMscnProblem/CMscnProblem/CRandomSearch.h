#pragma once
#include "CProblem.h"
#include "CRandom.h"
#include "COptimizer.h"

#include <iostream>

#define STARTING_VALUES_RAND_SEARCH_DIVIDER 1

class CRandomSearch : public COptimizer {
private:
	CRandom c_generator;
	double d_best_quality;
public:
	CRandomSearch(CProblem * pcProblem, int iSeed);

	~CRandomSearch() {
	}

	void vInitialize();
	void vRunIteration();
};

