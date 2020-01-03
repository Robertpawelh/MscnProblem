#pragma once
#include <iostream>
#include <string>
#include <stdio.h>
#include "CRandom.h"

#define INDEX_OF_FIRST_DATA_IN_SOLUTION 4
#define DESC_IN_FILE_SIZE 16
#define NULL_ERROR "pdSolution is NULL"
#define LENGTH_ERROR "length of solution is incorrect"
#define NEGATIVE_VAL_ERROR "negative value in solution"
#define BIGGER_THAN_PRODUCED_ERROR "sum of ordered is bigger than sum of produced"
#define SUM_ERROR "sum of xd < sum of xf OR sum of xf < sum of xm"
#define MIN_MAX_ERROR "value in solution isn't in minmax range"
using namespace std;

class CMscnProblem {
private:
	int i_D;
	int i_F;
	int i_M;
	int i_S;
	double* pd_sd;
	double* pd_sf;
	double* pd_sm;
	double* pd_ss;

	double** ppd_cd;
	double** ppd_cf;
	double** ppd_cm;

	double* pd_ud;
	double* pd_uf;
	double* pd_um;
	double* pd_p;

	double** ppd_xdminmax;
	double** ppd_xfminmax;
	double** ppd_xmminmax;

public:
	CMscnProblem();
	~CMscnProblem();

	bool bSetD(const int iVal);
	bool bSetF(const int iVal);
	bool bSetM(const int iVal);
	bool bSetS(const int iVal);

	bool bSetValInCd(int iRow, int iColumn, double dVal);
	bool bSetValInCf(int iRow, int iColumn, double dVal);
	bool bSetValInCm(int iRow, int iColumn, double dVal);

	bool bSetValInSd(int iIndex, double dVal);
	bool bSetValInSf(int iIndex, double dVal);
	bool bSetValInSm(int iIndex, double dVal);
	bool bSetValInSs(int iIndex, double dVal);

	bool bSetValInUd(int iIndex, double dVal);
	bool bSetValInUf(int iIndex, double dVal);
	bool bSetValInUm(int iIndex, double dVal);

	bool bSetValInP(int iIndex, double dVal);

	bool bSetValInXdminmax(int iRow, int iColumn, double dVal);
	bool bSetValInXfminmax(int iRow, int iColumn, double dVal);
	bool bSetValInXmminmax(int iRow, int iColumn, double dVal);

	double dGetMin(int iId, bool &bIsSuccess);
	double dGetMax(int iId, bool &bIsSuccess);
	double dCalculateTransportCost(double * pdSolution, bool & bIsSuccess);
	double dCalculateContractCost(double * pdSolution);
	double dCalculateIncome(double * pdSolution);
	double dCalculateProfit(double * pdSolution, bool & bIsSuccess);

	double dGetQuality(double *pdSolution, bool &isSuccess);
	bool bConstraintsSatisfied(double *pdSolution, string & sErrorCode);
	bool bSaveProblemInstance(string sFileName);
	bool bSaveSolution(string sFileName, double *pdSolution);
	double* pdReadSolution(string sFileName);
	bool bReadProblemInstance(string sFileName);

	void vGenerateInstance(int iInstanceSeed);
};

