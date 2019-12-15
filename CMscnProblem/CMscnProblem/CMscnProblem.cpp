#include "pch.h"
#include "CMscnProblem.h"

CMscnProblem::CMscnProblem() {
}

CMscnProblem::CMscnProblem(string sFilename) {
}


CMscnProblem::~CMscnProblem() {
}


bool CMscnProblem::bSetD(const int iVal) {	//SPRAWDZ CZY TO DZIALA. JESLI TAK TO DOPIERO WTEDY ZMIEN PONIZSZE METODY NA TA.
	if (iVal < 0 || iVal > i_D) {
		return false;
	}

	double* pd_new_sd = new double[iVal];

	for (int i = 0; i < iVal; i++) {
		pd_new_sd[i] = pd_sd[i];
	}
	delete[] pd_sd;
	pd_sd = pd_new_sd;


	double** ppd_new_cd;
	ppd_new_cd = new double*[iVal];

	for (int i = 0; i < iVal; i++) {
		ppd_new_cd[i] = ppd_cd[i];
	}
	delete [] ppd_cd;
	for (int i = iVal; i < i_D; i++) {
		delete [] ppd_cd[i];
	}

	ppd_cd = ppd_new_cd;
	i_D = iVal;

	return true;
}

bool CMscnProblem::bSetF(const int iVal) {
	return true;
}

bool CMscnProblem::bSetM(const int iVal) {
	return false;
}

bool CMscnProblem::bSetS(const int iVal) {
	return false;
}

bool CMscnProblem::bSetValInCd(int iRow, int iColumn, double dVal){
	if (iRow < 0 || iRow >= i_D || iColumn < 0 || iColumn >= i_F) {
		return false;
	}
	ppd_cd[iRow][iColumn] = dVal;
	return true;
}

bool CMscnProblem::bSetValInCf(int iRow, int iColumn, double dVal)
{
	return false;
}

bool CMscnProblem::bSetValInCm(int iRow, int iColumn, double dVal)
{
	return false;
}


bool CMscnProblem::bSetValInSd(int iIndex, double dVal)
{
	return false;
}

bool CMscnProblem::bSetValInSf(int iIndex, double dVal)
{
	return false;
}

bool CMscnProblem::bSetValInSm(int iIndex, double dVal)
{
	return false;
}

bool CMscnProblem::bSetValInSs(int iIndex, double dVal){
	return false;
}

double CMscnProblem::dCalculateTransportCost(){
	double d_sum = 0;

	for (int i = 0; i < i_D; i++) {
		for (int j = 0; j < i_F; j++) {
			d_sum += ppd_cd[i][j] * ppd_xd[i][j];
		}
	}

	for (int i = 0; i < i_F; i++) {
		for (int j = 0; j < i_M; j++) {
			d_sum += ppd_cd[i][j] * ppd_xd[i][j];
		}
	}

	for (int i = 0; i < i_M; i++) {
		for (int j = 0; j < i_S; j++) {
			d_sum += ppd_cd[i][j] * ppd_xd[i][j];
		}
	}
	return d_sum;
}

double CMscnProblem::dCalculateContractCost(){
	double d_sum = 0;

	for (int i = 0; i < i_D; i++) {
		double d_count_of_element = 0;
		for (int j = 0; j < i_F; j++) {
			d_count_of_element + ppd_xd[i][j];
		}
		d_sum += pd_ud[i] * d_count_of_element;
	}

	for (int i = 0; i < i_F; i++) {
		double d_count_of_element = 0;
		for (int j = 0; j < i_M; j++) {
			d_count_of_element + ppd_xd[i][j];
		}
		d_sum += pd_ud[i] * d_count_of_element;
	}

	for (int i = 0; i < i_M; i++) {
		double d_count_of_element = 0;
		for (int j = 0; j < i_S; j++) {
			d_count_of_element + ppd_xd[i][j];
		}
		d_sum += pd_ud[i] * d_count_of_element;
	}

	return d_sum;
}


double CMscnProblem::dCalculateIncome(){
	double d_sum = 0;
	for (int i = 0; i < i_M; i++) {
		for (int j = 0; j < i_S; j++) {
			d_sum += pd_p[i] * ppd_xd[i][j];
		}
	}
}

double CMscnProblem::dCalculateProfit() {
	return dCalculateIncome() - dCalculateTransportCost() - dCalculateContractCost();
}

double CMscnProblem::dGetQuality(double * pdSolution, bool &isSuccess) {
	if (pdSolution == NULL) { // jak sprawdzac dlugosc? 
		isSuccess = false;
	}
	int count = 0;
	for (count; count <= i_D; count++) {
		if (pdSolution[count] > 0) {
			
		}
	}
	for (count; count <= i_D + i_F; count++) {
	}
	for (count; count <= i_D + i_F + i_M; count++) {
	}
	return false;
}


bool CMscnProblem::bConstraintsSatisfied(double * pdSolution) {
	return false;
}

bool CMscnProblem::bSave() {
	return false;
}

bool CMscnProblem::bRead(string sFileName) {
	FILE* pf_file = fopen(sFileName.c_str(), "r");
	if (pf_file == NULL) {
		return false;
	}

	// tu upewnij sie czy wskaznik moze byc
	char c_char;
	/**
	do {
		fscanf(pf_file, "%s", &c_char); //upewnij sie czy c
		switch (c_char) { // przerob to jednak na ify albo cos innego
		case 'D' :
			fscanf(pf_file, "%i", &c_char); //upewnij sie czy i
			i_F = c_char;
			break;
		case 'F':
			fscanf(pf_file, "%i", &c_char);
			i_D = c_char;
			break;
		case 'M':
			fscanf(pf_file, "%i", &c_char);
			i_F = c_char;
			break;
		case 'S':
			fscanf(pf_file, "%i", &c_char);
			i_F = c_char;
			break;
		case 'sd':
			pd_sd = new double[i_D];
			for (int i = 0; i < i_D; i++) {
				fscanf(pf_file, "%d", &pd_sd[i]); //tutaj sprawdzanie czy jest doublem trzeba zrobic
			}
			break;
		case 'sf':
			pd_sf = new double[i_F];
			for (int i = 0; i < i_F; i++) {
				fscanf(pf_file, "%d", &pd_sf[i]); //tutaj sprawdzanie czy jest doublem trzeba zrobic
			}
			break;
		case 'sm':
			pd_sm = new double[i_M];
			for (int i = 0; i < i_M; i++) {
				fscanf(pf_file, "%d", &pd_sm[i]); //tutaj sprawdzanie czy jest doublem trzeba zrobic
			}
			break;
		case 'ss':
			pd_ss = new double[i_S];
			for (int i = 0; i < i_S; i++) {
				fscanf(pf_file, "%d", &pd_ss[i]); //tutaj sprawdzanie czy jest doublem trzeba zrobic
			}
			break;
		case 'cd':
			break;
		case '\n':
			break;
		default:
			fclose(pf_file);
			return false;
		}
	} while (c_char != EOF);
	*/
	return true;
}

