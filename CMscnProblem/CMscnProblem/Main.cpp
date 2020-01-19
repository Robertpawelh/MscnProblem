#include "CMscnProblem.h"
#include "CRandomSearch.h"
#include "CDiffEvol.h"

int main() {
	bool b_is_success;
	string s_error_code;
	//CMscnProblem *pc_problem_object = new CMscnProblem();
	CMscnProblem *pc_mscn_problem_object = new CMscnProblem();
	pc_mscn_problem_object->bReadProblemInstance("test_2.txt");

	CProblem *pc_problem_object = pc_mscn_problem_object;
	//pc_problem_object->bSetD(4);
	//pc_problem_object->bSetF(3);
	//pc_problem_object->bSetM(3);
	//pc_problem_object->bSetS(2);
	//pc_problem_object->vGenerateInstance(1);
//	pc_problem_object->vPrintInstance();

	CRandomSearch * pc_search = new CRandomSearch(pc_problem_object);
	CDiffEvol * pc_diff_evol = new CDiffEvol(pc_problem_object);

	COptimizer *pc_optimizer;

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
}
