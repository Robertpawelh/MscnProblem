#pragma once
#include "CMscnProblem.h"
#include "CRandomSolutionGenerator.h"

class COptimizer {
private:
protected:
	CMscnProblem * pc_problem;
	double * pd_current_best;
public:
	
	virtual ~COptimizer() {
		delete [] pd_current_best;
	}

	double* pdGetCurrentBest() {
		return pd_current_best;
	};

	virtual void vInitialize() = 0;
	virtual void vRunIteration() = 0;

};

