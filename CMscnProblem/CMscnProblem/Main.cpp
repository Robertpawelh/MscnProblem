#include "pch.h"
#include "CMscnProblem.h"
#include "CRandomSearch.h"

int main() {

//	c_problem_object.bSetD(2);
//	c_problem_object.bSetF(2);
//	c_problem_object.bSetM(2);
//	c_problem_object.bSetS(2);


	/*
	cout << c_problem_object.bReadProblemInstance("test_2.txt"); //sprawedz czy zapisuje wieksze poprawnie
	bool bIsSuccess;
	string sErrorCode;
	double * pd_sample_solution;
	pd_sample_solution = c_problem_object.pdReadSolution("sol_2.txt"); //sprawedz czy zapisuje wieksze poprawnie
	*/
	//c_problem_object.bConstraintsSatisfied(pd_sample_solution, sErrorCode);
	//cout << "Kod bledu: " << sErrorCode << endl;
	//cout << "\nPROFIT: " << c_problem_object.dGetQuality(pd_sample_solution, bIsSuccess) << endl;
	//cout << "IS SUCCESS: " << bIsSuccess;
/*	cout << endl;
	int x = 0;
	c_problem_object.bConstraintsSatisfied(pd_sample_solution, sErrorCode);
	cout << "Kod bledu: " << sErrorCode << endl;
	cout << "\nPROFIT: " << c_problem_object.dGetQuality(pd_sample_solution, isSuccess) << endl;
	*/
	//c_problem_object.bSaveProblemInstance("testsave.txt");			//sprawedz czy zapisuje wieksze poprawnie
	/*
																	//c_problem_object.bSaveSolution("testsol.txt", pd_sample_solution); //sprawdz czy zapisuje wieksze poprawnie

	cout << endl << "QUAL: " << c_problem_object.dGetQuality(pd_sample_solution, isSuccess) << endl;
	CRandom c_rand_generator (10);
	cout << c_rand_generator.i_random(0, 5) << endl;
*/	
//	delete[] pd_sample_solution;
	bool b_is_success;
	CMscnProblem *c_problem_object = new CMscnProblem(); //przy d, f, m, s = 1 minmaxy sie psuhja
	c_problem_object->bSetD(8);
	c_problem_object->bSetF(2);
	c_problem_object->bSetM(3);
	c_problem_object->bSetS(2);
	c_problem_object->vGenerateInstance(10);
	//c_problem_object->vPrintInstance();
	CRandomSearch c_search(c_problem_object);
	for (int i = 0; i < 10; i++) {
		cout << "PROBA NR " << i << ": " << endl;
		double * pd_best = c_search.pd_findBestSolution(i);
	//	cout << c_problem_object->dGetQuality(pd_best, b_is_success) << endl;
	}

}