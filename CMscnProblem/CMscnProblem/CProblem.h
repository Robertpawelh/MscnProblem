#pragma once
#include <string>


using namespace std;

class CProblem{
public:
	CProblem() {};
	virtual ~CProblem() {};

	
	virtual double dGetMin(int iId, bool &bIsSuccess) = 0;
	virtual double dGetMax(int iId, bool &bIsSuccess) = 0;
	virtual double dGetQuality(double *pdSolution, bool &bIsSuccess) = 0;
	virtual double iGetSolutionArrayLen() = 0;

	virtual void vPrintInstance() = 0;
	virtual void vPrintSolution(double * pdSolution) = 0;
};

