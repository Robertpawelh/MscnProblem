#include "CRandomSearch.h"

CRandomSearch::CRandomSearch(CMscnProblem * pcProblem, int iSeed) {
	pc_problem = pcProblem;
	c_generator = CRandom(iSeed);
}

void CRandomSearch::vInitialize() {
	bool b_is_success;
	string s_error_code;
	pd_current_best = CRandomSolutionGenerator::pd_random_solution(c_generator, pc_problem);
	d_best_quality = pc_problem->dGetQuality(pd_current_best, b_is_success);
}

void CRandomSearch::vRunIteration() {
	bool b_is_success;
	double d_current_quality;
	double* pd_current_solution = CRandomSolutionGenerator::pd_random_solution(c_generator, pc_problem);

	pd_current_solution = CRandomSolutionGenerator::pd_random_solution(c_generator, pc_problem);
	d_current_quality = pc_problem->dGetQuality(pd_current_solution, b_is_success);
	if (d_best_quality < d_current_quality) {
		d_best_quality = d_current_quality;
		delete[] pd_current_best;
		cout << d_best_quality << endl;
		pd_current_best = pd_current_solution;
	}
	else {
		delete[] pd_current_solution;
	}
}
