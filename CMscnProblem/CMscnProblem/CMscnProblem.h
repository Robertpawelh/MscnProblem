#pragma once
#include <iostream>
#include <string>

using namespace std;

class CMscnProblem{
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
	double* p_ud;
	double* p_uf;
	double* p_um;
	double* p_p;
	double** pp_xdminmax;
	double** pp_xfminmax;
	double** pp_xmminmax;

public:
	CMscnProblem();
	CMscnProblem(string sFilename);
	~CMscnProblem();

	bool bSetCd();
	bool bSetCf();
	bool bSetCm();
	bool bSetSd();
	bool bSetSf();
	bool bSetSm();
	bool bSetSs();
	
	double dGetQuality(double *pdSolution);
	bool bConstraintsSatisfied(double *pdSolution);
	void vSave();
	void vRead(string sFileName);
};

