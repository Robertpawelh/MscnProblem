#include "pch.h"
#include "CRandomSearch.h"


CRandomSearch::CRandomSearch(CMscnProblem *pcProblem) {
	pc_problem = pcProblem;
}


CRandomSearch::~CRandomSearch() {
}



double * CRandomSearch::pdFindBestSolution(int iSeed) {
	CRandom c_generator(iSeed);
	bool b_is_success;
	string s_error_code;

	double* pd_best_solution = CRandomSolutionGenerator::pd_random_solution(c_generator, pc_problem, STARTING_VALUES_RAND_SEARCH_DIVIDER);
	double d_best_quality = INT_MIN;

	if (pc_problem->bConstraintsSatisfied(pd_best_solution, s_error_code)) {
		d_best_quality = pc_problem->dGetQuality(pd_best_solution, b_is_success);
	}

	double d_current_quality;
	double* pd_current_solution;// = CRandomSolutionGenerator::pd_random_solution(c_generator, pc_problem, STARTING_VALUES_RAND_SEARCH_DIVIDER);

	for (int i = 0; i < NUMBER_OF_ITERATIONS; i++) {
		pd_current_solution = CRandomSolutionGenerator::pd_random_solution(c_generator, pc_problem, STARTING_VALUES_RAND_SEARCH_DIVIDER);
		d_current_quality = pc_problem->dGetQuality(pd_current_solution, b_is_success);

		if (d_best_quality < d_current_quality) {
			if (pc_problem->bConstraintsSatisfied(pd_current_solution, s_error_code)) {
				d_best_quality = d_current_quality;
				delete[] pd_best_solution;
				cout << d_best_quality << endl;
				pd_best_solution = pd_current_solution;
			}
			else {
				delete[] pd_current_solution;
			}
		}

	}
	return pd_best_solution;
}
