#include "pch.h"
#include "CMscnProblem.h"

CMscnProblem::CMscnProblem()
{
}


CMscnProblem::~CMscnProblem()
{
}

bool CMscnProblem::bSetCd()
{
	return false;
}

bool CMscnProblem::bSetCf()
{
	return false;
}

bool CMscnProblem::bSetCm()
{
	return false;
}

bool CMscnProblem::bSetSd()
{
	return false;
}

bool CMscnProblem::bSetSf()
{
	return false;
}

bool CMscnProblem::bSetSm()
{
	return false;
}

bool CMscnProblem::bSetSs()
{
	return false;
}

double CMscnProblem::dGetQuality(double * pdSolution)
{
	return 0.0;
}

bool CMscnProblem::bConstraintsSatisfied(double * pdSolution)
{
	return false;
}

void CMscnProblem::vSave()
{
}

void CMscnProblem::vRead(string sFileName)
{
}
