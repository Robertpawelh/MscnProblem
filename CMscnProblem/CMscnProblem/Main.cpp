#include "CMscnProblem.h"
#include "CRandomSearch.h"
#include "CDiffEvol.h"
#include "CTimer.h"

int main() {
	bool b_is_success;
	string s_error_code;

	CMscnProblem *pc_mscn_problem_object = new CMscnProblem();
	pc_mscn_problem_object->bReadProblemInstance("test_2.txt");
	double* pd_solution = pc_mscn_problem_object->pdReadSolution("solution.txt");
	//cout << pc_mscn_problem_object->bConstraintsSatisfied(pd_solution, s_error_code) << endl;
	cout << pc_mscn_problem_object->dGetQuality(pd_solution, b_is_success) << endl;
//	pc_mscn_problem_object->bSetD(3);
//	pc_mscn_problem_object->bSetF(3);
	//pc_mscn_problem_object->bSetM(2);
//	pc_mscn_problem_object->bSetS(3);
//	pc_mscn_problem_object->vGenerateInstance(1);
	//	pc_problem_object->vPrintInstance();

	CProblem *pc_problem_object = pc_mscn_problem_object;
	CRandomSearch * pc_search = new CRandomSearch(pc_problem_object, 13);
	CDiffEvol * pc_diff_evol = new CDiffEvol(pc_problem_object, 1337);

	COptimizer *pc_optimizer;
	CTimer c_timer;


	double d_time_passed = 0;
	c_timer.vSetStartNow();
	pc_optimizer = pc_search;
	pc_optimizer->vInitialize();

	while (d_time_passed <= MAX_TIME) {
		pc_optimizer->vRunIteration();
		//	pc_optimizer->pvGetCurrentBest();
		c_timer.vSetTimePassed(&d_time_passed);
		if (d_time_passed > 100) {
			cout << " xD ";
		}
	}

	cout << "\nBY DIFF:\n";
	d_time_passed = 0;
	c_timer.vSetStartNow();
	pc_optimizer = pc_diff_evol;
	pc_optimizer->vInitialize();

	while (d_time_passed <= MAX_TIME) {
		pc_optimizer->vRunIteration();
		//	pc_optimizer->pvGetCurrentBest();
		c_timer.vSetTimePassed(&d_time_passed);
	}


}
/*
for (int i = 0; i < 1; i++) {
	cout << "PROBA NR " << i << ": " << endl;
	cout << "BY RANDOM:\n";
	pc_optimizer = pc_search;
	double * pd_best_by_random = pc_optimizer->pdFindBestSolution(i);
	if (pc_problem_object->bConstraintsSatisfied(pd_best_by_random, s_error_code)) {
		pc_problem_object->vPrintSolution(pd_best_by_random);
		cout << "\nPROFIT: " << pc_problem_object->dGetQuality(pd_best_by_random, b_is_success) << endl;
	}
	else {
		cout << "RANDOM SOL IS BAD: " << s_error_code << endl;
	}
}
}*/
/*
cout << "\nBY DIFF:\n";
pc_optimizer = pc_diff_evol;
double * pd_best_by_diff = pc_optimizer->pdFindBestSolution(i);
if (pc_problem_object->bConstraintsSatisfied(pd_best_by_diff, s_error_code)) {
	pc_problem_object->vPrintSolution(pd_best_by_diff);
	cout << "\nPROFIT: " << pc_problem_object->dGetQuality(pd_best_by_diff, b_is_success) << endl;
}
else {
	cout << "DIFF SOL IS BAD: " << s_error_code << endl;
}
delete pd_best_by_diff;
delete pd_best_by_random;
}

delete pc_search;
delete pc_diff_evol;
delete pc_problem_object;
}*/

