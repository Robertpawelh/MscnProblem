#pragma once
#include <iostream>
#include <stdio.h>
#include "CRandom.h"
#include "CProblem.h"
#include "CMatrix.h"
#include "CArray.h"

#define BASIC_NUM_OFF_SUPPLIERS 3
#define BASIC_NUM_OFF_FACTORIES 5
#define BASIC_NUM_OFF_WAREHOUSES 7
#define BASIC_NUM_OFF_SHOPS 4

#define REDUCTION_PARAMETER 0.85
#define INCREASE_PARAMETER 1.05

#define NUMBER_OF_PRODUCTION_LEVELS 4
#define DESC_IN_FILE_SIZE 16
#define NULL_ERROR "pdSolution is NULL"
#define LENGTH_ERROR "length of solution is incorrect"
#define NEGATIVE_VAL_ERROR "negative value in solution"
#define BIGGER_THAN_PRODUCED_ERROR "sum of ordered is bigger than sum of produced"
#define SUM_ERROR "sum of xd < sum of xf OR sum of xf < sum of xm"
#define MIN_MAX_ERROR "value in solution isn't in minmax range"

#define MIN_CD 10
#define MAX_CD 100
#define MIN_CF 10
#define MAX_CF 200
#define MIN_CM 10
#define MAX_CM 300

#define MIN_UD 10
#define MAX_UD 400
#define MIN_UF 10
#define MAX_UF 400
#define MIN_UM 10
#define MAX_UM 400

#define MIN_P 100
#define MAX_P 700

#define MIN_SD 1
#define MAX_SD 1024
#define MIN_SF 2
#define MAX_SF 512
#define MIN_SM 4
#define MAX_SM 256
#define MIN_SS 8
#define MAX_SS 128

using namespace std;

class CMscnProblem : public CProblem {
private:
	int i_num_of_suppliers;
	int i_num_of_factories;
	int i_num_of_warehouses;
	int i_num_of_shops;

	CArray *pc_max_cap_of_supp;
	CArray *pc_max_cap_of_fact;
	CArray *pc_max_cap_of_ware;
	CArray *pc_max_cap_of_shop;

	CMatrix *pc_transp_cost_supp_to_fact;
	CMatrix *pc_transp_cost_fact_to_ware;
	CMatrix *pc_transp_cost_ware_to_shop;

	CArray *pc_contract_cost_supp;
	CArray *pc_contract_cost_fact;
	CArray *pc_contract_cost_ware;
	CArray *pc_income;

	double d_calc_transp_cost_for_matrix(int iId, double * pdSolution, CMatrix *pcCostMatrix, int iX, int iY);
	double d_calc_transp_cost(double * pdSolution);
	double d_calc_contract_cost_for_array(int iId, double * pdSolution, CArray *pcCostArray, int iX, int iY);
	double d_calc_contract_cost(double * pdSolution);
	double d_calc_income(double * pdSolution);
	double d_calc_profit(double * pdSolution);
//	void vRepairIncorrectSolution(double * pdSolution);

public:
	CMscnProblem();
	~CMscnProblem();

	//bool bSetNumOfSuppliers(const int iVal);
	//bool bSetNumOfFactories(const int iVal);
	//bool bSetNumOfWarehouses(const int iVal);
	//bool bSetNumOfShops(const int iVal);
	/*
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
	*/
	int iGetNumOfSuppliers() { return i_num_of_suppliers; };
	int iGetNumOfFactories() { return i_num_of_factories; };
	int iGetNumOfWarehouses() { return i_num_of_warehouses; };
	int iGetNumOfShops() { return i_num_of_shops; };

	//double dGetMin(int iId, bool &bIsSuccess);
	double dGetMax(int iId, bool &bIsSuccess);

	double dGetQuality(double *pdSolution, bool &bIsSuccess);

	bool bConstraintsSatisfied(double *pdSolution, string & sErrorCode);

	double iGetSolutionLen() {
		return NUMBER_OF_PRODUCTION_LEVELS + 
			i_num_of_suppliers * i_num_of_factories + 
			i_num_of_factories * i_num_of_warehouses + 
			i_num_of_warehouses * i_num_of_shops;
	};

	bool bSaveProblemInstance(string sFileName);
	bool bSaveSolution(string sFileName, double *pdSolution);

	double* pdReadSolution(string sFileName);
	//bool bReadProblemInstance(string sFileName);

	void vPrintInstance();
	void vPrintSolution(double * pdSolution);

	void vGenerateInstance(int iInstanceSeed);
};

