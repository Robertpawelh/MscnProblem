#pragma once
#include "CProblem.h"
#include "CRandomSolutionGenerator.h"

class COptimizer {
private:
protected:
	CProblem * pc_problem;
public:
	
	virtual ~COptimizer() {
	}

	virtual double * pdFindBestSolution(int iSeed) = 0;

};

