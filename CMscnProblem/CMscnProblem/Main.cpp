#include "pch.h"
#include "CMscnProblem.h"

int main(){
	CMscnProblem c_problem_object;
	cout << c_problem_object.bRead("sampletest.txt");
	double * d_sample_solution;
	d_sample_solution = new double[7];
	for (int i = 0; i < 7; i++) {
		d_sample_solution[i] = 1;
	}
	bool isSuccess;
	cout << "\nPROFIT: " << c_problem_object.dGetQuality(d_sample_solution, isSuccess);
	cout << endl << c_problem_object.bConstraintsSatisfied(d_sample_solution);
	return 0;
}