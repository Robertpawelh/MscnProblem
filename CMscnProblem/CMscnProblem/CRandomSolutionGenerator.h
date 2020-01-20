#pragma once
#include "CRandom.h"
#include "CProblem.h"
class CRandomSolutionGenerator{
public:
	static double * pd_random_solution(CRandom &cGenerator, CProblem* pcProblem, double dValuesDivider);
};

