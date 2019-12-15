#include "pch.h"
#include "CMscnProblem.h"

int main(){
	CMscnProblem c_problem_object;
	std::cout << c_problem_object.bRead("sampletest.txt");
	return 0;
}