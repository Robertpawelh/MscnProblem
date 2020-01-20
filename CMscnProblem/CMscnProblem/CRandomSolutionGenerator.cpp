#include "CRandomSolutionGenerator.h"

double* CRandomSolutionGenerator::pd_random_solution(CRandom &cGenerator, CProblem* pcProblem, double dValuesDivider) {
	int i_solution_data_len = pcProblem->iGetSolutionArrayLen();
	double * pd_solution = new double[i_solution_data_len];
	bool b_is_success;

	for (int i = 0; i < i_solution_data_len; i++) {
		double d_min_val = pcProblem->dGetMin(i, b_is_success);
		double d_max_val = pcProblem->dGetMax(i, b_is_success);
		pd_solution[i] = cGenerator.d_random(d_min_val, d_max_val/dValuesDivider);
	}

	return pd_solution;
}
