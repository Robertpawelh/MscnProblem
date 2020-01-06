#include "pch.h"
#include "CRandomSearch.h"


CRandomSearch::CRandomSearch(CMscnProblem *pcProblem) {
	pc_problem = pcProblem;
}


CRandomSearch::~CRandomSearch() {
}

double* CRandomSearch::pd_random_solution(CRandom &cGenerator) {
	int i_solution_data_len = 
		pc_problem->iGetD()*pc_problem->iGetF() +
		pc_problem->iGetF()*pc_problem->iGetM() +
		pc_problem->iGetM()*pc_problem->iGetS();

	double * pd_solution = new double[INDEX_OF_FIRST_DATA_IN_SOLUTION + i_solution_data_len];
	bool b_is_success;
	int i_counter = 0;

	//int i_minmax_len = pc_problem->iGetD() + 2 * pc_problem->iGetF() + 2 * pc_problem->iGetM();
	//double* pd_current_min = new double[i_solution_data_len];
//	double* pd_current_max = new double[i_solution_data_len];

//	for (int i = 0; i < i_solution_data_len; i++) {
	//	pd_current_min[i] = pc_problem->dGetMin(i, b_is_success);
//		pd_current_max[i] = pc_problem->dGetMax(i, b_is_success);
//	}

	pd_solution[i_counter++] = pc_problem->iGetD();
	pd_solution[i_counter++] = pc_problem->iGetF();
	pd_solution[i_counter++] = pc_problem->iGetM();
	pd_solution[i_counter++] = pc_problem->iGetS();

	for (int i = 0; i < i_solution_data_len; i++) {
		double d_min_val = pc_problem->dGetMin(i, b_is_success);
		double d_max_val = pc_problem->dGetMax(i, b_is_success);
	//	double d_min_val = pd_current_min[i];
	//	double d_max_val = pd_current_max[i];
		pd_solution[i_counter] = cGenerator.d_random(d_min_val, d_max_val);
		i_counter++;
		//pd_current_max[i] = d_max_val - pd_solution[i_counter++];
	}

	return pd_solution;
}

double * CRandomSearch::pd_findBestSolution(int iSeed) {
	CRandom c_generator(iSeed);
	bool b_is_success;
	string s_error_code;
	double* pd_best_solution = pd_random_solution(c_generator); //seed
	double d_best_quality = INT_MIN;
	if (pc_problem->bConstraintsSatisfied(pd_best_solution, s_error_code)){
		d_best_quality = pc_problem->dGetQuality(pd_best_solution, b_is_success);
	}

	double d_current_quality;
	double* pd_current_solution = pd_random_solution(c_generator);
	for (int i = 0; i < NUMBER_OF_ITERATIONS; i++) {
		pd_current_solution = pd_random_solution(c_generator);
		d_current_quality = pc_problem->dGetQuality(pd_current_solution, b_is_success);
		if (d_best_quality < d_current_quality) {
			if (pc_problem->bConstraintsSatisfied(pd_current_solution, s_error_code)) {
				d_best_quality = d_current_quality;
				pd_best_solution = pd_current_solution;
				cout << d_best_quality << endl;
			}
		}
	}
	return pd_best_solution;
}
