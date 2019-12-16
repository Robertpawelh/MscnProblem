#include "pch.h"
#include "CMscnProblem.h"

int main() {
	CMscnProblem c_problem_object;
	cout << c_problem_object.bRead("test_2.txt");
	double * d_sample_solution;
	d_sample_solution = new double[18];
	for (int i = 0; i < 4; i++) {
		d_sample_solution[i] = 2;
	}
	d_sample_solution[3] = 3;
	for (int i = 4; i < 18; i++) {
		d_sample_solution[i] = 65536/(2*i);
	}

	bool isSuccess;
	cout << "\nPROFIT: " << c_problem_object.dGetQuality(d_sample_solution, isSuccess) << endl;
	cout << endl << "WHY SO BAD? IS IT A CORRECT SOLUTION? " << c_problem_object.bConstraintsSatisfied(d_sample_solution) << endl;
	cout << endl << "MIN AT 11 INDEX: " << c_problem_object.dGetMin(d_sample_solution, 11) << endl;
	cout << endl << "MAX AT 11 INDEX: " << c_problem_object.dGetMax(d_sample_solution, 11) << endl;
	c_problem_object.bSave("plik.txt");
	return 0;

}