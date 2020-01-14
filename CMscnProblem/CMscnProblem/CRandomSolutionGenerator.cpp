#include "pch.h"
#include "CRandomSolutionGenerator.h"

double* CRandomSolutionGenerator::pd_random_solution(CRandom &cGenerator, CMscnProblem* pcProblem, double dValuesDivider) {
	int i_solution_data_len =
		pcProblem->iGetD()*pcProblem->iGetF() +
		pcProblem->iGetF()*pcProblem->iGetM() +
		pcProblem->iGetM()*pcProblem->iGetS();

	double * pd_solution = new double[INDEX_OF_FIRST_DATA_IN_SOLUTION + i_solution_data_len];
	bool b_is_success;
	int i_counter = 0;

	pd_solution[i_counter++] = pcProblem->iGetD();
	pd_solution[i_counter++] = pcProblem->iGetF();
	pd_solution[i_counter++] = pcProblem->iGetM();
	pd_solution[i_counter++] = pcProblem->iGetS();

	for (int i = 0; i < i_solution_data_len; i++) {
		double d_min_val = pcProblem->dGetMin(i, b_is_success);
		double d_max_val = pcProblem->dGetMax(i, b_is_success);
		pd_solution[i_counter] = cGenerator.d_random(d_min_val, d_max_val/dValuesDivider);
		i_counter++;
	}

	return pd_solution;
}
