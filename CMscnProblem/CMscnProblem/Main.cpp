#include "CMscnProblem.h"
#include "CRandomSearch.h"
#include "CDiffEvol.h"
#include "CTimer.h"

int main() {
	bool b_is_success;
	string s_error_code;
	double * pd_best_found_solution = nullptr;
	CMscnProblem *pc_mscn_problem_object = new CMscnProblem();
	pc_mscn_problem_object->vGenerateInstance(13);
	CRandomSearch * pc_rand_search = new CRandomSearch(pc_mscn_problem_object, 2);
	CDiffEvol * pc_diff_evol = new CDiffEvol(pc_mscn_problem_object, 2); // 

	COptimizer *pc_optimizer;
	CTimer c_timer;

	double d_time_passed = 0;
	c_timer.vSetStartNow();
	//pc_optimizer = pc_rand_search;
	pc_optimizer = pc_diff_evol;//
	pc_optimizer->vInitialize();
	//pc_mscn_problem_object->vPrintInstance();
	string err_code = "";
	while (d_time_passed <= MAX_TIME) {
		pc_optimizer->vRunIteration();
		pd_best_found_solution = pc_optimizer->pdGetCurrentBest();
		c_timer.vSetTimePassed(&d_time_passed);
	}
	pc_mscn_problem_object->vPrintSolution(pd_best_found_solution);
	cout << pc_mscn_problem_object->bConstraintsSatisfied(pd_best_found_solution, err_code);

	delete pc_mscn_problem_object;
	delete pc_diff_evol;
	delete pc_rand_search;
}
