#include "pch.h"
#include "CMscnProblem.h"

int main() {
	CMscnProblem c_problem_object;
	c_problem_object.bSetD(2);
	c_problem_object.bSetF(2);
	c_problem_object.bSetM(2);
	c_problem_object.bSetS(2);
	c_problem_object.vGenerateInstance(1);
	cout << c_problem_object.bReadProblemInstance("test_2.txt"); //sprawedz czy zapisuje wieksze poprawnie
	bool bIsSuccess;
	string sErrorCode;
	//sprawdz czy masz sprawdzanie odpowiednich sum w programie 
	double * pd_sample_solution;
	pd_sample_solution = c_problem_object.pdReadSolution("sol_2.txt"); //sprawedz czy zapisuje wieksze poprawnie
	c_problem_object.bConstraintsSatisfied(pd_sample_solution, sErrorCode);
	cout << "Kod bledu: " << sErrorCode << endl;
	cout << "\nPROFIT: " << c_problem_object.dGetQuality(pd_sample_solution, bIsSuccess) << endl;
	cout << "IS SUCCESS: " << bIsSuccess;
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

}