#pragma once
#include "CRandom.h"
#include "CMscnProblem.h"
#include <algorithm>
class CRandomSolutionGenerator{
public:
	static double * pd_random_cmscn_solution(CRandom &cGenerator, CMscnProblem* pcProblem);
};

