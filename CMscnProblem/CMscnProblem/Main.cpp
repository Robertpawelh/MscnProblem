#include "CMscnProblem.h"
#include "CRandomSearch.h"
#include "CDiffEvol.h"
#include "CTimer.h"

int main() {
	bool b_is_success;
	string s_error_code;
	double * pd_best_found_solution = nullptr;

	CMscnProblem *pc_mscn_problem_object = new CMscnProblem();

	cout << "WSPOLNY TEST:" << endl;
	pc_mscn_problem_object->bReadProblemInstance("wspolny_test.txt");
	double* pd_solution = pc_mscn_problem_object->pdReadSolution("wspolne_solution.txt");
	cout << "Wspolne rozwiazanie " << endl;
	cout << "PROFIT: " << pc_mscn_problem_object->dGetQuality(pd_solution, b_is_success) << endl;

	CProblem *pc_problem_object = pc_mscn_problem_object;
	CRandomSearch * pc_rand_search = new CRandomSearch(pc_problem_object, 2);
	CDiffEvol * pc_diff_evol = new CDiffEvol(pc_problem_object, 2);

	COptimizer *pc_optimizer;
	CTimer c_timer;

	cout << "\nRandomSearch:\n";
	double d_time_passed = 0;
	c_timer.vSetStartNow();
	pc_optimizer = pc_rand_search;
	pc_optimizer->vInitialize();

	while (d_time_passed <= MAX_TIME) {
		pc_optimizer->vRunIteration();
		pd_best_found_solution = pc_optimizer->pdGetCurrentBest();
		c_timer.vSetTimePassed(&d_time_passed);
	}
	pc_mscn_problem_object->vPrintSolution(pd_best_found_solution);

	cout << "\nDiffEvolution:\n";
	d_time_passed = 0;
	c_timer.vSetStartNow();
	pc_optimizer = pc_diff_evol;
	pc_optimizer->vInitialize();

	while (d_time_passed <= MAX_TIME) {
		pc_optimizer->vRunIteration();
		pd_best_found_solution = pc_optimizer->pdGetCurrentBest();
		c_timer.vSetTimePassed(&d_time_passed);
	}
	pc_mscn_problem_object->vPrintSolution(pd_best_found_solution);
	

	cout << "Inny test" << endl;

	pc_mscn_problem_object->bSetD(15);
	pc_mscn_problem_object->bSetF(15);
	pc_mscn_problem_object->bSetM(15);
	pc_mscn_problem_object->bSetS(15);
	pc_mscn_problem_object->vGenerateInstance(15);

	cout << "\nRandomSearch:\n";
	d_time_passed = 0;
	c_timer.vSetStartNow();
	pc_optimizer = pc_rand_search;
	pc_optimizer->vInitialize();

	while (d_time_passed <= MAX_TIME) {
		pc_optimizer->vRunIteration();
		pd_best_found_solution = pc_optimizer->pdGetCurrentBest();
		c_timer.vSetTimePassed(&d_time_passed);
	}
	pc_mscn_problem_object->vPrintSolution(pd_best_found_solution);
	cout << "\nDiffEvolution:\n";
	d_time_passed = 0;
	c_timer.vSetStartNow();
	pc_optimizer = pc_diff_evol;
	pc_optimizer->vInitialize();

	while (d_time_passed <= MAX_TIME) {
		pc_optimizer->vRunIteration();
		pd_best_found_solution = pc_optimizer->pdGetCurrentBest();
		c_timer.vSetTimePassed(&d_time_passed);
	}
	pc_mscn_problem_object->vPrintSolution(pd_best_found_solution);

	delete pc_mscn_problem_object;
	delete pc_rand_search;
	delete pc_diff_evol;
}