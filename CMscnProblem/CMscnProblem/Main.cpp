#include "pch.h"
#include "CMscnProblem.h"

int main() {
	CMscnProblem c_problem_object;

//	cout << c_problem_object.bReadProblemInstance("sampletest.txt"); //sprawedz czy zapisuje wieksze poprawnie
	bool isSuccess;
	//sprawdz czy masz sprawdzanie odpowiednich sum w programie 
	double * pd_sample_solution;
	pd_sample_solution = c_problem_object.pdReadSolution("samplesolution.txt"); //sprawedz czy zapisuje wieksze poprawnie

//	cout << "\nPROFIT: " << c_problem_object.dGetQuality(pd_sample_solution, isSuccess) << endl;

	//c_problem_object.bSaveProblemInstance("testsave.txt");			//sprawedz czy zapisuje wieksze poprawnie
	//c_problem_object.bSaveSolution("testsol.txt", pd_sample_solution); //sprawdz czy zapisuje wieksze poprawnie
	delete [] pd_sample_solution;
	
	CRandom c_rand_generator (10);
	cout << c_rand_generator.i_random(0,5) << endl;
	cout << c_rand_generator.i_random(0, 5) << endl;
	cout << c_rand_generator.i_random(0, 5) << endl;
	cout << c_rand_generator.i_random(0, 5) << endl;
	cout << c_rand_generator.i_random(0, 5) << endl;
	return 0;

}