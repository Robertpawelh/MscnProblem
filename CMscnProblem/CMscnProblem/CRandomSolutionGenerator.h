#pragma once
#include "CRandom.h"
#include "CMscnProblem.h"
class CRandomSolutionGenerator
{
public:
	static double * pd_random_solution(CRandom &cGenerator, CMscnProblem* pcProblem, double dValuesDivider);
};

