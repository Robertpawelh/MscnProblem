#include "CMscnProblem.h"

CMscnProblem::CMscnProblem() {
	i_D = 1;
	i_F = 1;
	i_M = 1;
	i_S = 1;

	pd_sd = new double[i_D];
	pd_sf = new double[i_F];
	pd_sm = new double[i_M];
	pd_ss = new double[i_S];

	ppd_cd = new double*[i_D];
	for (int i = 0; i < i_D; i++) {
		ppd_cd[i] = new double[i_F];
	}
	ppd_cf = new double*[i_F];
	for (int i = 0; i < i_F; i++) {
		ppd_cf[i] = new double[i_M];
	}
	ppd_cm = new double*[i_M];
	for (int i = 0; i < i_M; i++) {
		ppd_cm[i] = new double[i_S];
	}

	pd_ud = new double[i_D];
	pd_uf = new double[i_F];
	pd_um = new double[i_M];

	pd_p = new double[i_S];

	ppd_xdminmax = new double*[2 * i_D];
	for (int i = 0; i < 2 * i_D; i++) {
		ppd_xdminmax[i] = new double[i_F];
	}
	ppd_xfminmax = new double*[2 * i_F];
	for (int i = 0; i < 2 * i_F; i++) {
		ppd_xfminmax[i] = new double[i_M];
	}
	ppd_xmminmax = new double*[2 * i_M];
	for (int i = 0; i < 2 * i_M; i++) {
		ppd_xmminmax[i] = new double[i_S];
	}
}

CMscnProblem::~CMscnProblem() {
	delete[] pd_sd;
	delete[] pd_sf;
	delete[] pd_sm;
	delete[] pd_ss;

	for (int i = 0; i < i_D; i++) {
		delete[] ppd_cd[i];
	}
	delete[] ppd_cd;

	for (int i = 0; i < i_F; i++) {
		delete[] ppd_cf[i];
	}
	delete[] ppd_cf;

	for (int i = 0; i < i_M; i++) {
		delete[] ppd_cm[i];
	}
	delete[] ppd_cm;

	delete[] pd_ud;
	delete[] pd_uf;
	delete[] pd_um;

	delete[] pd_p;

	for (int i = 0; i < 2 * i_D; i++) {
		delete[] ppd_xdminmax[i];
	}
	delete[] ppd_xdminmax;

	for (int i = 0; i < 2 * i_F; i++) {
		delete[] ppd_xfminmax[i];
	}
	delete[] ppd_xfminmax;

	for (int i = 0; i < 2 * i_M; i++) {
		delete[] ppd_xmminmax[i];
	}
	delete[] ppd_xmminmax;
}

bool CMscnProblem::bSetD(const int iVal) {
	if (iVal < 0 || iVal == i_D) {
		return false;
	}

	double* pd_new_sd = new double[iVal];
	double* pd_new_ud = new double[iVal];
	double** ppd_new_cd = new double*[iVal];
	double** ppd_new_xdminmax = new double*[2 * iVal];

	int i_loop_len = (iVal < i_D) ? iVal : i_D;
	for (int i = 0; i < i_loop_len; i++) {
		pd_new_sd[i] = pd_sd[i];
		pd_new_ud[i] = pd_ud[i];
		ppd_new_cd[i] = ppd_cd[i];
		ppd_new_xdminmax[i] = ppd_xdminmax[i];
	}

	for (int i = i_loop_len; i < 2 * i_loop_len; i++) {
		ppd_new_xdminmax[i] = ppd_xdminmax[i];
	}

	if (i_D < iVal) {
		for (int i = i_D; i < iVal; i++) {
			ppd_new_cd[i] = new double[i_F];
		}
		for (int i = 2 * i_D; i < 2 * iVal; i++) {
			ppd_new_xdminmax[i] = new double[i_F];
		}
	}

	for (int i = iVal; i < i_D; i++) {
		delete[] ppd_cd[i];
	}

	delete[] pd_sd;
	delete[] pd_ud;
	delete[] ppd_cd;
	pd_sd = pd_new_sd;
	pd_ud = pd_new_ud;
	ppd_cd = ppd_new_cd;

	for (int i = 2 * iVal; i < 2 * i_D; i++) {
		delete[] ppd_xdminmax[i];
	}
	delete[] ppd_xdminmax;
	ppd_xdminmax = ppd_new_xdminmax;

	i_D = iVal;
	return true;
}

bool CMscnProblem::bSetF(const int iVal) {
	if (iVal < 0 || iVal == i_F) {
		return false;
	}

	double* pd_new_sf = new double[iVal];
	double* pd_new_uf = new double[iVal];
	double** ppd_new_cf = new double*[iVal];
	double** ppd_new_cd = new double*[i_D];
	double** ppd_new_xdminmax = new double*[2 * i_D];
	double** ppd_new_xfminmax = new double*[2 * iVal];

	for (int i = 0; i < i_D; i++) {
		ppd_new_cd[i] = new double[iVal];
	}
	for (int i = 0; i < 2 * i_D; i++) {
		ppd_new_xdminmax[i] = new double[iVal];
	}

	int i_loop_len = (iVal < i_F) ? iVal : i_F;

	for (int i = 0; i < i_D; i++) {
		for (int j = 0; j < i_loop_len; j++) {
			ppd_new_cd[i][j] = ppd_cd[i][j];
			ppd_new_xdminmax[i][j] = ppd_xdminmax[i][j];
		}
	}

	for (int i = i_D; i < 2 * i_D; i++) {
		for (int j = 0; j < i_loop_len; j++) {
			ppd_new_xdminmax[i][j] = ppd_xdminmax[i][j];
		}
	}

	for (int i = 0; i < i_loop_len; i++) {
		pd_new_sf[i] = pd_sf[i];
		pd_new_uf[i] = pd_uf[i];
		ppd_new_cf[i] = ppd_cf[i];
		ppd_new_xfminmax[i] = ppd_xfminmax[i];
	}

	for (int i = i_loop_len; i < 2 * i_loop_len; i++) {
		ppd_new_xfminmax[i] = ppd_xfminmax[i];
	}

	if (i_F < iVal) {

		for (int i = i_F; i < iVal; i++) {
			ppd_new_cf[i] = new double[i_M];
		}
		for (int i = 2 * i_F; i < 2 * iVal; i++) {
			ppd_new_xfminmax[i] = new double[i_M];
		}
	}

	for (int i = 0; i < i_D; i++) {
		delete[] ppd_cd[i];
	}

	for (int i = iVal; i < i_F; i++) {
		delete[] ppd_cf[i];
	}

	delete[] pd_sf;
	delete[] pd_uf;
	delete[] ppd_cf;
	delete[] ppd_cd;
	pd_sf = pd_new_sf;
	pd_uf = pd_new_uf;
	ppd_cd = ppd_new_cd;
	ppd_cf = ppd_new_cf;

	for (int i = 0; i < 2 * i_D; i++) {
		delete[] ppd_xdminmax[i];
	}

	for (int i = 2 * iVal; i < 2 * i_F; i++) {
		delete[] ppd_xfminmax[i];
	}

	delete[] ppd_xfminmax;
	delete[] ppd_xdminmax;
	ppd_xfminmax = ppd_new_xfminmax;
	ppd_xdminmax = ppd_new_xdminmax;

	i_F = iVal;

	return true;
}

bool CMscnProblem::bSetM(const int iVal) {
	if (iVal < 0 || iVal == i_M) {
		return false;
	}

	double* pd_new_sm = new double[iVal];
	double* pd_new_um = new double[iVal];
	double** ppd_new_cm = new double*[iVal];
	double** ppd_new_cf = new double*[i_F];
	double** ppd_new_xfminmax = new double*[2 * i_F];
	double** ppd_new_xmminmax = new double*[2 * iVal];

	for (int i = 0; i < i_F; i++) {
		ppd_new_cf[i] = new double[iVal];
	}
	for (int i = 0; i < 2 * i_F; i++) {
		ppd_new_xfminmax[i] = new double[iVal];
	}

	int i_loop_len = (iVal < i_M) ? iVal : i_M;

	for (int i = 0; i < i_F; i++) {
		for (int j = 0; j < i_loop_len; j++) {
			ppd_new_cf[i][j] = ppd_cf[i][j];
			ppd_new_xfminmax[i][j] = ppd_xfminmax[i][j];
		}
	}

	for (int i = i_F; i < 2 * i_F; i++) {
		for (int j = 0; j < i_loop_len; j++) {
			ppd_new_xfminmax[i][j] = ppd_xfminmax[i][j];
		}
	}


	for (int i = 0; i < i_loop_len; i++) {
		pd_new_sm[i] = pd_sm[i];
		pd_new_um[i] = pd_um[i];
		ppd_new_cm[i] = ppd_cm[i];
		ppd_new_xmminmax[i] = ppd_xmminmax[i];
	}

	for (int i = i_loop_len; i < 2 * i_loop_len; i++) {
		ppd_new_xmminmax[i] = ppd_xmminmax[i];
	}

	if (i_M < iVal) {

		for (int i = i_M; i < iVal; i++) {
			ppd_new_cm[i] = new double[i_S];
		}
		for (int i = 2 * i_M; i < 2 * iVal; i++) {
			ppd_new_xmminmax[i] = new double[i_S];
		}
	}

	for (int i = 0; i < i_F; i++) {
		delete ppd_cf[i];
	}

	for (int i = iVal; i < i_M; i++) {
		delete[] ppd_cm[i];
	}

	delete[] pd_sm;
	delete[] pd_um;
	delete[] ppd_cm;
	delete[] ppd_cf;
	pd_sm = pd_new_sm;
	pd_um = pd_new_um;
	ppd_cf = ppd_new_cf;
	ppd_cm = ppd_new_cm;

	for (int i = 0; i < 2 * i_F; i++) {
		delete[] ppd_xfminmax[i];
	}

	for (int i = 2 * iVal; i < 2 * i_M; i++) {
		delete[] ppd_xmminmax[i];
	}

	delete[] ppd_xmminmax;
	delete[] ppd_xfminmax;
	ppd_xmminmax = ppd_new_xmminmax;
	ppd_xfminmax = ppd_new_xfminmax;

	i_M = iVal;

	return true;
}

bool CMscnProblem::bSetS(const int iVal) {
	if (iVal < 0 || iVal == i_S) {
		return false;
	}

	double* pd_new_ss = new double[iVal];
	double** ppd_new_cm = new double*[i_M];
	double** ppd_new_xmminmax = new double*[2 * i_M];
	double *pd_new_p = new double[iVal];

	for (int i = 0; i < i_M; i++) {
		ppd_new_cm[i] = new double[iVal];
	}
	for (int i = 0; i < 2 * i_M; i++) {
		ppd_new_xmminmax[i] = new double[iVal];
	}

	int i_loop_len = (iVal < i_S) ? iVal : i_S;

	for (int i = 0; i < i_M; i++) {
		for (int j = 0; j < i_loop_len; j++) {
			ppd_new_cm[i][j] = ppd_cm[i][j];
			ppd_new_xmminmax[i][j] = ppd_xmminmax[i][j];
		}
	}

	for (int i = i_M; i < 2 * i_M; i++) {
		for (int j = 0; j < i_loop_len; j++) {
			ppd_new_xmminmax[i][j] = ppd_xmminmax[i][j];
		}
	}


	for (int i = 0; i < i_loop_len; i++) {
		pd_new_ss[i] = pd_ss[i];
		pd_new_p[i] = pd_p[i];
	}

	for (int i = 0; i < i_M; i++) {
		delete ppd_cm[i];
	}

	delete[] pd_ss;
	delete[] pd_p;
	delete[] ppd_cm;
	pd_ss = pd_new_ss;
	pd_p = pd_new_p;
	ppd_cm = ppd_new_cm;

	for (int i = 0; i < 2 * i_M; i++) {
		delete[] ppd_xmminmax[i];
	}

	delete[] ppd_xmminmax;
	ppd_xmminmax = ppd_new_xmminmax;

	i_S = iVal;

	return true;
}

bool CMscnProblem::bSetValInCd(int iRow, int iColumn, double dVal) {
	if (iRow < 0 || iRow >= i_D || iColumn < 0 || iColumn >= i_F) {
		return false;
	}
	ppd_cd[iRow][iColumn] = dVal;
	return true;
}

bool CMscnProblem::bSetValInCf(int iRow, int iColumn, double dVal) {
	if (iRow < 0 || iRow >= i_F || iColumn < 0 || iColumn >= i_M) {
		return false;
	}
	ppd_cf[iRow][iColumn] = dVal;
	return true;
}

bool CMscnProblem::bSetValInCm(int iRow, int iColumn, double dVal) {
	if (iRow < 0 || iRow >= i_M || iColumn < 0 || iColumn >= i_S) {
		return false;
	}
	ppd_cm[iRow][iColumn] = dVal;
	return true;
}


bool CMscnProblem::bSetValInSd(int iIndex, double dVal) {
	if (iIndex < 0 || iIndex >= i_D) {
		return false;
	}
	pd_sd[iIndex] = dVal;
	return true;
}

bool CMscnProblem::bSetValInSf(int iIndex, double dVal) {
	if (iIndex < 0 || iIndex >= i_F) {
		return false;
	}
	pd_sf[iIndex] = dVal;
	return true;
}

bool CMscnProblem::bSetValInSm(int iIndex, double dVal) {
	if (iIndex < 0 || iIndex >= i_M) {
		return false;
	}
	pd_sm[iIndex] = dVal;
	return true;
}

bool CMscnProblem::bSetValInSs(int iIndex, double dVal) {
	if (iIndex < 0 || iIndex >= i_S) {
		return false;
	}
	pd_ss[iIndex] = dVal;
	return true;
}

bool CMscnProblem::bSetValInUd(int iIndex, double dVal) {
	if (iIndex < 0 || iIndex >= i_D) {
		return false;
	}
	pd_ud[iIndex] = dVal;
	return true;
}

bool CMscnProblem::bSetValInUf(int iIndex, double dVal) {
	if (iIndex < 0 || iIndex >= i_F) {
		return false;
	}
	pd_uf[iIndex] = dVal;
	return true;
}

bool CMscnProblem::bSetValInUm(int iIndex, double dVal) {
	if (iIndex < 0 || iIndex >= i_M) {
		return false;
	}
	pd_um[iIndex] = dVal;
	return true;
}

bool CMscnProblem::bSetValInP(int iIndex, double dVal) {
	if (iIndex < 0 || iIndex >= i_S) {
		return false;
	}
	pd_p[iIndex] = dVal;
	return true;
}

bool CMscnProblem::bSetValInXdminmax(int iRow, int iColumn, double dVal) {
	if (iRow < 0 || iRow >= 2 * i_D || iColumn < 0 || iColumn >= i_F) {
		return false;
	}
	ppd_xdminmax[iRow][iColumn] = dVal;
	return true;
}

bool CMscnProblem::bSetValInXfminmax(int iRow, int iColumn, double dVal) {
	if (iRow < 0 || iRow >= 2 * i_F || iColumn < 0 || iColumn >= i_M) {
		return false;
	}
	ppd_xfminmax[iRow][iColumn] = dVal;
	return true;
}

bool CMscnProblem::bSetValInXmminmax(int iRow, int iColumn, double dVal) {
	if (iRow < 0 || iRow >= 2 * i_M || iColumn < 0 || iColumn >= i_S) {
		return false;
	}
	ppd_xmminmax[iRow][iColumn] = dVal;
	return true;
}

double CMscnProblem::dGetMin(int iId, bool &bIsSuccess) {
	if (iId >= INDEX_OF_FIRST_DATA_IN_SOLUTION) {
		iId -= INDEX_OF_FIRST_DATA_IN_SOLUTION;
	}

	else {
		bIsSuccess = true;
		if (iId-- == 0) return i_D;
		if (iId-- == 0) return i_F;
		if (iId-- == 0) return i_M;
		if (iId-- == 0) return i_S;
	}

	if (iId >= i_D * i_F) {
		iId -= i_D * i_F;
	}
	else {
		bIsSuccess = true;
		return ppd_xdminmax[2 * (iId / i_F)][iId%i_F];
	}

	if (iId >= i_F * i_M) {
		iId -= i_F * i_M;
	}
	else {
		bIsSuccess = true;
		return ppd_xfminmax[2 * (iId / i_M)][iId%i_M];
	}

	if (iId >= i_M * i_S) {
		iId -= i_M * i_S;
	}
	else {
		bIsSuccess = true;
		return ppd_xmminmax[2 * (iId / i_S)][iId%i_S];
	}
	bIsSuccess = false;
	return -1;
}

double CMscnProblem::dGetMax(int iId, bool &bIsSuccess) {
	if (iId >= INDEX_OF_FIRST_DATA_IN_SOLUTION) {
		iId -= INDEX_OF_FIRST_DATA_IN_SOLUTION;
	}

	else {
		bIsSuccess = true;
		if (iId-- == 0) return i_D;
		if (iId-- == 0) return i_F;
		if (iId-- == 0) return i_M;
		if (iId-- == 0) return i_S;
	}

	if (iId >= i_D * i_F) {
		iId -= i_D * i_F;
	}
	else {
		bIsSuccess = true;
		return ppd_xdminmax[1 + 2 * (iId / i_F)][iId%i_F];
	}

	if (iId >= i_F * i_M) {
		iId -= i_F * i_M;
	}
	else {
		bIsSuccess = true;
		return ppd_xfminmax[1 + 2 * (iId / i_M)][iId%i_M];
	}

	if (iId >= i_M * i_S) {
		iId -= i_M * i_S;
	}
	else {
		bIsSuccess = true;
		return ppd_xmminmax[1 + 2 * (iId / i_S)][iId%i_S];
	}

	bIsSuccess = false;
	return -1;
}

double CMscnProblem::dCalculateTransportCost(double* pdSolution, bool & bIsSuccess) {
	double d_transport_cost = 0;
	int i_counter = INDEX_OF_FIRST_DATA_IN_SOLUTION;
	for (int i = 0; i < i_D; i++) {
		for (int j = 0; j < i_F; j++) {
			if (pdSolution[i_counter] < 0) {
				bIsSuccess = false;
			}
			d_transport_cost += ppd_cd[i][j] * pdSolution[i_counter++];
		}
	}

	for (int i = 0; i < i_F; i++) {
		for (int j = 0; j < i_M; j++) {
			if (pdSolution[i_counter] < 0) {
				bIsSuccess = false;
			}
			d_transport_cost += ppd_cf[i][j] * pdSolution[i_counter++];
		}
	}

	for (int i = 0; i < i_M; i++) {
		for (int j = 0; j < i_S; j++) {
			if (pdSolution[i_counter] < 0) {
				bIsSuccess = false;
			}
			d_transport_cost += ppd_cm[i][j] * pdSolution[i_counter++];
		}
	}
	return d_transport_cost;
}

double CMscnProblem::dCalculateContractCost(double* pdSolution) {
	double d_contract_cost = 0;
	int i_counter = INDEX_OF_FIRST_DATA_IN_SOLUTION;

	for (int i = 0; i < i_D; i++) {
		int i_count_of_element = 0;
		int j = 0;
		while (j < i_F && i_count_of_element == 0) {
			i_count_of_element += pdSolution[i_counter++];
			j++;
		}
		if (i_count_of_element > 0) {
			d_contract_cost += pd_ud[i];
		}
	}

	for (int i = 0; i < i_F; i++) {
		int i_count_of_element = 0;
		int j = 0;
		while (j < i_M && i_count_of_element == 0) {
			i_count_of_element += pdSolution[i_counter++];
			j++;
		}
		if (i_count_of_element > 0) {
			d_contract_cost += pd_uf[i];
		}
	}

	for (int i = 0; i < i_M; i++) {
		int i_count_of_element = 0;
		int j = 0;
		while (j < i_S && i_count_of_element == 0) {
			i_count_of_element += pdSolution[i_counter++];
			j++;
		}
		if (i_count_of_element > 0) {
			d_contract_cost += pd_um[i];
		}
	}

	return d_contract_cost;
}


double CMscnProblem::dCalculateIncome(double * pdSolution) {
	double d_income = 0;
	int i_counter = INDEX_OF_FIRST_DATA_IN_SOLUTION + i_D * i_F + i_F * i_M;

	for (int i = 0; i < i_M; i++) {
		for (int j = 0; j < i_S; j++) {
			d_income += pd_p[j] * pdSolution[i_counter++];
		}
	}
	return d_income;
}

double CMscnProblem::dCalculateProfit(double* pdSolution, bool & bIsSuccess) {
	return dCalculateIncome(pdSolution) - dCalculateTransportCost(pdSolution, bIsSuccess) - dCalculateContractCost(pdSolution);
}

double CMscnProblem::dGetQuality(double * pdSolution, bool &bIsSuccess) {
	bIsSuccess = true;

	if (pdSolution == NULL) {
		bIsSuccess = false;
	}

	if (pdSolution[0] != i_D) {
		pdSolution[0] = i_D;
		bIsSuccess = false;
	}
	if (pdSolution[1] != i_F) {
		pdSolution[1] = i_F;
		bIsSuccess = false;
	}
	if (pdSolution[2] != i_M) {
		pdSolution[2] = i_M;
		bIsSuccess = false;
	}
	if (pdSolution[3] != i_S) {
		pdSolution[3] = i_S;
		bIsSuccess = false;
	}

	string xD = "";
	vRepairBadSolution(&pdSolution);
	bConstraintsSatisfied(pdSolution, xD);
	cout << xD << endl;
	return dCalculateProfit(pdSolution, bIsSuccess);
}

void CMscnProblem::vRepairBadSolution(double ** pdSolution) {
	bool b_is_success;
	double d_current_sum_xd = 0;
	double d_current_sum_xf = 0;
	double d_current_sum_xm = 0;
	double d_sum_from_d_to_f = 0;
	double d_sum_from_f_to_m = 0;
	double d_total_sum_xm = 0;

	int i_counter = INDEX_OF_FIRST_DATA_IN_SOLUTION;

	double d_sum_from_m_to_s = 0;

	for (int i = 0; i < i_D; i++) {

		for (int j = 0; j < i_F; j++) {
			if (*pdSolution[i_counter] >= 0) {
				d_current_sum_xd += *pdSolution[i_counter];
				i_counter++;
			}
			else {
				*pdSolution[i_counter] = dGetMin(i_counter, b_is_success); //sprawdz czy zmienia
				d_current_sum_xd += *pdSolution[i_counter];
				i_counter++;
			}
		}

		while (d_current_sum_xd > pd_sd[i]) {
			i_counter -= i_F;		// cofamy o iteracje F

			for (int j = 0; j < i_F; j++) {
				if (*pdSolution[i_counter] * REDUCTION_PARAMETER > dGetMin(i_counter, b_is_success)) {
					d_current_sum_xd -= *pdSolution[i_counter] * (1 - REDUCTION_PARAMETER);
					*pdSolution[i_counter] *= REDUCTION_PARAMETER;
					i_counter++;
				}
				else {
					d_current_sum_xd -= (*pdSolution[i_counter] - dGetMin(i_counter, b_is_success));
					*pdSolution[i_counter] = dGetMin(i_counter, b_is_success);
					i_counter++;
				}
			}
		}

		//d_total_sum_xd += d_current_sum_xd;
		d_current_sum_xd = 0;
	}

	for (int i = 0; i < i_F; i++) {
		for (int j = 0; j < i_M; j++) {
			if (*pdSolution[i_counter] >= 0) {
				d_current_sum_xf += *pdSolution[i_counter];
				i_counter++;
			}
			else {
				*pdSolution[i_counter] = dGetMin(i_counter, b_is_success); //sprawdz czy zmienia
				d_current_sum_xf += *pdSolution[i_counter];
				i_counter++;
			}
		}

		while (d_current_sum_xf > pd_sf[i]) {
			i_counter -= i_M;		// cofamy o iteracje F

			for (int j = 0; j < i_M; j++) {
				if (*pdSolution[i_counter] * REDUCTION_PARAMETER > dGetMin(i_counter, b_is_success)) {
					d_current_sum_xf -= *pdSolution[i_counter] * (1 - REDUCTION_PARAMETER);
					*pdSolution[i_counter] *= REDUCTION_PARAMETER;
					i_counter++;
				}
				else {
					d_current_sum_xf -= (*pdSolution[i_counter] - dGetMin(i_counter, b_is_success));
					*pdSolution[i_counter] = dGetMin(i_counter, b_is_success);
					i_counter++;
				}
			}
		}

		//d_total_sum_xf += d_current_sum_xf;
		d_current_sum_xf = 0;
	}

	for (int i = 0; i < i_M; i++) {
		for (int j = 0; j < i_S; j++) {
			if (*pdSolution[i_counter] >= 0) {
				d_current_sum_xm += *pdSolution[i_counter];
				i_counter++;
			}
			else {
				*pdSolution[i_counter] = dGetMin(i_counter, b_is_success); //sprawdz czy zmienia
				d_current_sum_xm += *pdSolution[i_counter];
				i_counter++;
			}
		}

		while (d_current_sum_xm > pd_sm[i]) {
			i_counter -= i_S;		// cofamy o iteracje F

			for (int j = 0; j < i_S; j++) {
				if (*pdSolution[i_counter] * REDUCTION_PARAMETER > dGetMin(i_counter, b_is_success)) {
					d_current_sum_xm -= *pdSolution[i_counter] * (1 - REDUCTION_PARAMETER);
					*pdSolution[i_counter] *= REDUCTION_PARAMETER;
					i_counter++;
				}
				else {
					d_current_sum_xm -= (*pdSolution[i_counter] - dGetMin(i_counter, b_is_success));
					*pdSolution[i_counter] = dGetMin(i_counter, b_is_success);
					i_counter++;
				}
			}
		}

		//d_total_sum_xm += d_current_sum_xm;
		d_current_sum_xm = 0;
	}

	d_current_sum_xm = 0;
	i_counter = INDEX_OF_FIRST_DATA_IN_SOLUTION + i_D * i_F + i_F * i_M;

	for (int i = 0; i < i_S; i++) {
		for (int j = 0; j < i_M; j++) {
			d_current_sum_xm += *pdSolution[i_counter + i_M * j];
		}


		while (d_current_sum_xm > pd_ss[i]) {
			//	i_counter -= -i_M;		// cofamy o iteracje F

			for (int j = 0; j < i_M; j++) {
				if (*pdSolution[i_counter + i_M * j] * REDUCTION_PARAMETER > dGetMin(i_counter + i_M * j, b_is_success)) {
					d_current_sum_xm -= *pdSolution[i_counter + i_M * j] * (1 - REDUCTION_PARAMETER);
					*pdSolution[i_counter + i_M * j] *= REDUCTION_PARAMETER;
				}
				else {
					d_current_sum_xm -= (*pdSolution[i_counter + i_M * j] - dGetMin(i_counter + i_M * j, b_is_success));
					*pdSolution[i_counter + i_M * j] = dGetMin(i_counter + i_M * j, b_is_success);
				}

			}
		}

		d_current_sum_xm = 0;
		i_counter++;
	}

	for (int i = 0; i < i_M; i++) {
		for (int j = 0; j < i_F; j++) {
			d_sum_from_f_to_m += *pdSolution[INDEX_OF_FIRST_DATA_IN_SOLUTION + i_D * i_F + i + j * i_F];
		}

		for (int j = 0; j < i_S; j++) {
			d_sum_from_m_to_s += *pdSolution[INDEX_OF_FIRST_DATA_IN_SOLUTION + i_D * i_F + i_F * i_M + i * i_M + j];
		}

		while (d_sum_from_f_to_m < d_sum_from_m_to_s) {
			for (int j = 0; j < i_F; j++) {
				i_counter = INDEX_OF_FIRST_DATA_IN_SOLUTION + i_D * i_F + i + j * i_F;
				if (*pdSolution[i_counter] * INCREASE_PARAMETER < dGetMax(i_counter, b_is_success)) {
					d_sum_from_f_to_m += *pdSolution[i_counter] * (INCREASE_PARAMETER - 1);
					*pdSolution[i_counter] *= INCREASE_PARAMETER;
					i_counter++;
				}
				else {
					d_sum_from_f_to_m += (dGetMax(i_counter, b_is_success) - *pdSolution[i_counter]);
					*pdSolution[i_counter] = dGetMax(i_counter, b_is_success);
					i_counter++;
				}
			}
		}
	}

	d_sum_from_f_to_m = 0;

	for (int i = 0; i < i_F; i++) {
		for (int j = 0; j < i_D; j++) {
			d_sum_from_d_to_f += *pdSolution[INDEX_OF_FIRST_DATA_IN_SOLUTION + i + j * i_F];
		}

		for (int j = 0; j < i_M; j++) {
			d_sum_from_f_to_m += *pdSolution[INDEX_OF_FIRST_DATA_IN_SOLUTION + i_D * i_F + i * i_M + j];
		}

		while (d_sum_from_d_to_f < d_sum_from_f_to_m) {
	//		cout << d_sum_from_d_to_f << "   " << d_sum_from_f_to_m << endl;
			for (int j = 0; j < i_D; j++) {
				i_counter = INDEX_OF_FIRST_DATA_IN_SOLUTION + i + j * i_F;
				if (*pdSolution[i_counter] * INCREASE_PARAMETER < dGetMax(i_counter, b_is_success)) {
					d_sum_from_d_to_f += *pdSolution[i_counter] * (INCREASE_PARAMETER - 1);
					*pdSolution[i_counter] *= INCREASE_PARAMETER;
					i_counter++;
				}
				else {
					d_sum_from_d_to_f += (dGetMax(i_counter, b_is_success) - *pdSolution[i_counter]);
					*pdSolution[i_counter] = dGetMax(i_counter, b_is_success);
					i_counter++;
				}
			}
		}
	}
}


bool CMscnProblem::bConstraintsSatisfied(double * pdSolution, string & sErrorCode) {
	sErrorCode = "";
	if (pdSolution == NULL) {
		sErrorCode = NULL_ERROR;
		return false;
	}

	int i_counter = 0;
	if (i_D != pdSolution[i_counter++] ||
		i_F != pdSolution[i_counter++] ||
		i_M != pdSolution[i_counter++] ||
		i_S != pdSolution[i_counter++]) {
		sErrorCode = LENGTH_ERROR;
		return false;
	}

	double d_current_sum_xd = 0;
	double d_current_sum_xf = 0;
	double d_current_sum_xm = 0;
	double d_total_sum_xd = 0;
	double d_total_sum_xf = 0;
	double d_total_sum_xm = 0;

	for (int i = 0; i < i_D; i++) {
		for (int j = 0; j < i_F; j++) {			// po co mi tutaj ten j?
			if (pdSolution[i_counter] >= 0) {
				d_current_sum_xd += pdSolution[i_counter];
				i_counter++;
			}
			else {
				sErrorCode = NEGATIVE_VAL_ERROR;
				return false;
			}
		}

		if (d_current_sum_xd > pd_sd[i]) {
			sErrorCode = BIGGER_THAN_PRODUCED_ERROR;
			return false;
		}
		d_total_sum_xd += d_current_sum_xd;
		d_current_sum_xd = 0;
	}

	for (int i = 0; i < i_F; i++) {
		for (int j = 0; j < i_M; j++) {
			if (pdSolution[i_counter] >= 0) {
				d_current_sum_xf += pdSolution[i_counter];
				i_counter++;
			}
			else {
				sErrorCode = NEGATIVE_VAL_ERROR;
				return false;
			}
		}

		if (d_current_sum_xf > pd_sf[i]) {
			sErrorCode = BIGGER_THAN_PRODUCED_ERROR;
			return false;
		}
		d_total_sum_xf += d_current_sum_xf;
		d_current_sum_xf = 0;
	}

	for (int i = 0; i < i_M; i++) {
		for (int j = 0; j < i_S; j++) {
			if (pdSolution[i_counter] >= 0) {
				d_current_sum_xm += pdSolution[i_counter];
				i_counter++;
			}
			else {
				sErrorCode = NEGATIVE_VAL_ERROR;
				return false;
			}
		}

		if (d_current_sum_xm > pd_sm[i]) {
			sErrorCode = BIGGER_THAN_PRODUCED_ERROR;
			return false;
		}
		d_total_sum_xm += d_current_sum_xm;
		d_current_sum_xm = 0;
	}

	d_current_sum_xm = 0;
	i_counter = INDEX_OF_FIRST_DATA_IN_SOLUTION + i_D * i_F + i_F * i_M;

	for (int i = 0; i < i_S; i++) {
		for (int j = 0; j < i_M; j++) {
			d_current_sum_xm += pdSolution[i_counter + i_M * j];
		}

		if (d_current_sum_xm > pd_ss[i]) {
			sErrorCode = BIGGER_THAN_PRODUCED_ERROR;
			return false;
		}

		d_current_sum_xm = 0;
		i_counter++;
	}

	if (d_total_sum_xd < d_total_sum_xf || d_total_sum_xf < d_total_sum_xm) {
		sErrorCode = SUM_ERROR;
		return false;
	}


	i_counter = INDEX_OF_FIRST_DATA_IN_SOLUTION;
	for (int i = 0; i < 2 * i_D; i += 2) {
		for (int j = 0; j < i_F; j++) {
			if (pdSolution[i_counter] < ppd_xdminmax[i][j] || pdSolution[i_counter] > ppd_xdminmax[i + 1][j]) {
				sErrorCode = MIN_MAX_ERROR;
				return false;
			}
			i_counter++;
		}
	}

	for (int i = 0; i < 2 * i_F; i += 2) {
		for (int j = 0; j < i_M; j++) {
			if (pdSolution[i_counter] < ppd_xfminmax[i][j] || pdSolution[i_counter] > ppd_xfminmax[i + 1][j]) {
				sErrorCode = MIN_MAX_ERROR;
				return false;
			}
			i_counter++;
		}
	}

	for (int i = 0; i < 2 * i_M; i += 2) {
		for (int j = 0; j < i_S; j++) {
			if (pdSolution[i_counter] < ppd_xmminmax[i][j] || pdSolution[i_counter] > ppd_xmminmax[i + 1][j]) {
				sErrorCode = MIN_MAX_ERROR;
				return false;
			}
			i_counter++;
		}
	}

	return true;
}

double CMscnProblem::iGetSolutionArrayLen() {
	return INDEX_OF_FIRST_DATA_IN_SOLUTION + i_D * i_F + i_F * i_M + i_M * i_S;
}

bool CMscnProblem::bSaveProblemInstance(string sFileName) {
	FILE* pf_file = fopen(sFileName.c_str(), "w+");
	if (pf_file == NULL) {
		return false;
	}
	fprintf(pf_file, "%s %i", "D", i_D);
	fprintf(pf_file, "%s %i", "\nF", i_F);
	fprintf(pf_file, "%s %i", "\nM", i_M);
	fprintf(pf_file, "%s %i", "\nS", i_S);

	fprintf(pf_file, "%s", "\nsd");
	for (int i = 0; i < i_D; i++) {
		fprintf(pf_file, "\n%lf", pd_sd[i]);
	}

	fprintf(pf_file, "%s", "\nsf");
	for (int i = 0; i < i_F; i++) {
		fprintf(pf_file, "\n%lf", pd_sf[i]);
	}

	fprintf(pf_file, "%s", "\nsm");
	for (int i = 0; i < i_M; i++) {
		fprintf(pf_file, "\n%lf", pd_sm[i]);
	}

	fprintf(pf_file, "%s", "\nss");
	for (int i = 0; i < i_S; i++) {
		fprintf(pf_file, "\n%lf", pd_ss[i]);
	}

	fprintf(pf_file, "%s", "\ncd");
	for (int i = 0; i < i_D; i++) {
		for (int j = 0; j < i_F; j++) {
			fprintf(pf_file, "\n%lf", ppd_cd[i][j]);
		}
	}

	fprintf(pf_file, "%s", "\ncf");
	for (int i = 0; i < i_F; i++) {
		for (int j = 0; j < i_M; j++) {
			fprintf(pf_file, "\n%lf", ppd_cf[i][j]);
		}
	}

	fprintf(pf_file, "%s", "\ncm");
	for (int i = 0; i < i_M; i++) {
		for (int j = 0; j < i_S; j++) {
			fprintf(pf_file, "\n%lf", ppd_cm[i][j]);
		}
	}

	fprintf(pf_file, "%s", "\nud");
	for (int i = 0; i < i_D; i++) {
		fprintf(pf_file, "\n%lf", pd_ud[i]);
	}

	fprintf(pf_file, "%s", "\nuf");
	for (int i = 0; i < i_F; i++) {
		fprintf(pf_file, "\n%lf", pd_uf[i]);
	}

	fprintf(pf_file, "%s", "\num");
	for (int i = 0; i < i_M; i++) {
		fprintf(pf_file, "\n%lf", pd_um[i]);
	}

	fprintf(pf_file, "%s", "\np");
	for (int i = 0; i < i_S; i++) {
		fprintf(pf_file, "\n%lf", pd_p[i]);
	}

	fprintf(pf_file, "%s", "\nxdminmax");
	for (int i = 0; i < 2 * i_D; i += 2) {
		for (int j = 0; j < i_F; j++) {
			fprintf(pf_file, "\n%lf ", ppd_xdminmax[i][j]);
			fprintf(pf_file, "%lf", ppd_xdminmax[i + 1][j]);
		}
	}

	fprintf(pf_file, "%s", "\nxfminmax");
	for (int i = 0; i < 2 * i_F; i += 2) {
		for (int j = 0; j < i_M; j++) {
			fprintf(pf_file, "\n%lf ", ppd_xfminmax[i][j]);
			fprintf(pf_file, "%lf", ppd_xfminmax[i + 1][j]);
		}
	}

	fprintf(pf_file, "%s", "\nxmminmax");
	for (int i = 0; i < 2 * i_M; i += 2) {
		for (int j = 0; j < i_S; j++) {
			fprintf(pf_file, "\n%lf ", ppd_xmminmax[i][j]);
			fprintf(pf_file, "%lf", ppd_xmminmax[i + 1][j]);
		}
	}
	return true;
}

bool CMscnProblem::bSaveSolution(string sFileName, double* pdSolution) {
	FILE* pf_file = fopen(sFileName.c_str(), "w+");
	if (pf_file == NULL) {
		return false;
	}
	int i_counter = 0;
	fprintf(pf_file, "%s %i", "D", pdSolution[i_counter++]);
	fprintf(pf_file, "%s %i", "\nF", pdSolution[i_counter++]);
	fprintf(pf_file, "%s %i", "\nM", pdSolution[i_counter++]);
	fprintf(pf_file, "%s %i", "\nS", pdSolution[i_counter++]);

	fprintf(pf_file, "%s", "\nxd");
	for (int i = 0; i < i_D; i++) {
		for (int j = 0; j < i_F; j++) {
			fprintf(pf_file, "\n%lf ", pdSolution[i_counter++]);	//tu moge nieco poprawic te odstepy. w powyzszej funkcji chyba tez
		}
	}

	fprintf(pf_file, "%s", "\nxf\n");
	for (int i = 0; i < i_F; i++) {
		for (int j = 0; j < i_M; j++) {
			fprintf(pf_file, "\n%lf ", pdSolution[i_counter++]);
		}
	}

	fprintf(pf_file, "%s", "\nxm");
	for (int i = 0; i < i_M; i++) {
		for (int j = 0; j < i_S; j++) {
			fprintf(pf_file, "\n%lf ", pdSolution[i_counter++]);
		}
	}
	fclose(pf_file);
	return true;
};


bool CMscnProblem::bReadProblemInstance(string sFileName) {
	FILE* pf_file = fopen(sFileName.c_str(), "r");
	if (pf_file == NULL) {
		return false;
	}

	char c_val[DESC_IN_FILE_SIZE];
	int i_num;
	double d_num;
	fscanf(pf_file, "%[^0-9] %i", c_val, &i_num);
	bSetD(i_num);
	fscanf(pf_file, "%[^0-9] %i", c_val, &i_num);
	bSetF(i_num);
	fscanf(pf_file, "%[^0-9] %i", c_val, &i_num);
	bSetM(i_num);
	fscanf(pf_file, "%[^0-9] %i", c_val, &i_num);
	bSetS(i_num);

	for (int i = 0; i < i_D; i++) {
		fscanf(pf_file, "%[^0-9] %lf", c_val, &d_num);
		bSetValInSd(i, d_num);
	}

	for (int i = 0; i < i_F; i++) {
		fscanf(pf_file, "%[^0-9] %lf", c_val, &d_num);
		bSetValInSf(i, d_num);
	}

	for (int i = 0; i < i_M; i++) {
		fscanf(pf_file, "%[^0-9] %lf", c_val, &d_num);
		bSetValInSm(i, d_num);
	}

	for (int i = 0; i < i_S; i++) {
		fscanf(pf_file, "%[^0-9] %lf", c_val, &d_num);
		bSetValInSs(i, d_num);
	}

	for (int i = 0; i < i_D; i++) {
		for (int j = 0; j < i_F; j++) {
			fscanf(pf_file, "%[^0-9] %lf", c_val, &d_num);
			bSetValInCd(i, j, d_num);
		}
	}

	for (int i = 0; i < i_F; i++) {
		for (int j = 0; j < i_M; j++) {
			fscanf(pf_file, "%[^0-9] %lf", c_val, &d_num);
			bSetValInCf(i, j, d_num);
		}
	}

	for (int i = 0; i < i_M; i++) {
		for (int j = 0; j < i_S; j++) {
			fscanf(pf_file, "%[^0-9] %lf", c_val, &d_num);
			bSetValInCm(i, j, d_num);
		}
	}

	for (int i = 0; i < i_D; i++) {
		fscanf(pf_file, "%[^0-9] %lf", c_val, &d_num);
		bSetValInUd(i, d_num);
	}

	for (int i = 0; i < i_F; i++) {
		fscanf(pf_file, "%[^0-9] %lf", c_val, &d_num);
		bSetValInUf(i, d_num);
	}

	for (int i = 0; i < i_M; i++) {
		fscanf(pf_file, "%[^0-9] %lf", c_val, &d_num);
		bSetValInUm(i, d_num);
	}

	for (int i = 0; i < i_S; i++) {
		fscanf(pf_file, "%[^0-9] %lf", c_val, &d_num);
		bSetValInP(i, d_num);
	}

	for (int i = 0; i < 2 * i_D; i += 2) {
		for (int j = 0; j < i_F; j++) {
			fscanf(pf_file, "%[^0-9] %lf", c_val, &d_num);
			bSetValInXdminmax(i, j, d_num);
			fscanf(pf_file, "%[^0-9] %lf", c_val, &d_num);
			bSetValInXdminmax(i + 1, j, d_num);
		}
	}

	for (int i = 0; i < 2 * i_F; i += 2) {
		for (int j = 0; j < i_M; j++) {
			fscanf(pf_file, "%[^0-9] %lf", c_val, &d_num);
			bSetValInXfminmax(i, j, d_num);
			fscanf(pf_file, "%[^0-9] %lf", c_val, &d_num);
			bSetValInXfminmax(i + 1, j, d_num);
		}
	}

	for (int i = 0; i < 2 * i_M; i += 2) {
		for (int j = 0; j < i_S; j++) {
			fscanf(pf_file, "%[^0-9] %lf", c_val, &d_num);
			bSetValInXmminmax(i, j, d_num);
			fscanf(pf_file, "%[^0-9] %lf", c_val, &d_num);
			bSetValInXmminmax(i + 1, j, d_num);
		}
	}

	fclose(pf_file);
	return true;
}

double* CMscnProblem::pdReadSolution(string sFileName) {
	FILE* pf_file = fopen(sFileName.c_str(), "r");
	if (pf_file == NULL) {
		return nullptr;
	}

	double * pd_solution = new double[INDEX_OF_FIRST_DATA_IN_SOLUTION + i_F * i_D + i_D * i_M + i_M * i_S];
	char c_val[DESC_IN_FILE_SIZE];
	int i_counter = 0;
	fscanf(pf_file, "%[^0-9] %lf", c_val, &pd_solution[i_counter++]);
	fscanf(pf_file, "%[^0-9] %lf", c_val, &pd_solution[i_counter++]);
	fscanf(pf_file, "%[^0-9] %lf", c_val, &pd_solution[i_counter++]);
	fscanf(pf_file, "%[^0-9] %lf", c_val, &pd_solution[i_counter++]);

	for (int i = 0; i < i_F * i_D + i_D * i_M + i_M * i_S; i++) {
		fscanf(pf_file, "%[^0-9] %lf", c_val, &pd_solution[i_counter + i]);
	}

	fclose(pf_file);
	return pd_solution;
}

void CMscnProblem::vGenerateInstance(int iInstanceSeed) {
	CRandom random(iInstanceSeed);
	for (int i = 0; i < i_D; i++) {
		bSetValInSd(i, random.d_random(MIN_SD, MAX_SD));
	}

	for (int i = 0; i < i_F; i++) {
		bSetValInSf(i, random.d_random(MIN_SF, MAX_SF));
	}

	for (int i = 0; i < i_M; i++) {
		bSetValInSm(i, random.d_random(MIN_SM, MAX_SM));
	}

	for (int i = 0; i < i_S; i++) {
		bSetValInSs(i, random.d_random(MIN_SS, MAX_SS));
	}

	for (int i = 0; i < i_D; i++) {
		for (int j = 0; j < i_F; j++) {
			bSetValInCd(i, j, random.d_random(MIN_CD, MAX_CD));
		}
	}

	for (int i = 0; i < i_F; i++) {
		for (int j = 0; j < i_M; j++) {
			bSetValInCf(i, j, random.d_random(MIN_CF, MAX_CF));
		}
	}

	for (int i = 0; i < i_M; i++) {
		for (int j = 0; j < i_S; j++) {
			bSetValInCm(i, j, random.d_random(MIN_CM, MAX_CM));
		}
	}

	for (int i = 0; i < i_D; i++) {
		bSetValInUd(i, random.d_random(MIN_UD, MAX_UD));
	}

	for (int i = 0; i < i_F; i++) {
		bSetValInUf(i, random.d_random(MIN_UF, MAX_UF));
	}

	for (int i = 0; i < i_M; i++) {
		bSetValInUm(i, random.d_random(MIN_UM, MAX_UM));
	}

	for (int i = 0; i < i_S; i++) {
		bSetValInP(i, random.d_random(MIN_P, MAX_P));
	}

	for (int i = 0; i < 2 * i_D; i += 2) {
		for (int j = 0; j < i_F; j++) {
			bSetValInXdminmax(i, j, 0);
			bSetValInXdminmax(i + 1, j, min(pd_sd[i / 2], pd_sf[j]));
		}
	}

	for (int i = 0; i < 2 * i_F; i += 2) {
		for (int j = 0; j < i_M; j++) {
			double d_d_to_f_max = 0;
			for (int k = 1; k < 2 * i_D; k += 2) {
				d_d_to_f_max += ppd_xdminmax[k][i / 2];
			}

			bSetValInXfminmax(i, j, 0);
			double d_max_correct_val = min(pd_sf[i / 2], pd_sm[j]);
			bSetValInXfminmax(i + 1, j, min(d_max_correct_val, d_d_to_f_max));
		}
	}
	for (int i = 0; i < 2 * i_M; i += 2) {
		for (int j = 0; j < i_S; j++) {
			double d_f_to_m_max = 0;
			for (int k = 1; k < 2 * i_F; k += 2) {
				d_f_to_m_max += ppd_xfminmax[k][i / 2];
			}

			bSetValInXmminmax(i, j, 0);
			double d_max_correct_val = min(pd_sm[i / 2], pd_ss[j]);
			bSetValInXmminmax(i + 1, j, min(d_max_correct_val, d_f_to_m_max));
		}
	}
}

void CMscnProblem::vPrintInstance() {
	for (int i = 0; i < i_D; i++) {
		cout << "sd[" << i << +"]: " << pd_sd[i] << "\n";
	}

	for (int i = 0; i < i_F; i++) {
		cout << "sf[" << i << +"]: " << pd_sf[i] << "\n";
	}

	for (int i = 0; i < i_M; i++) {
		cout << "sm[" << i << +"]: " << pd_sm[i] << "\n";
	}

	for (int i = 0; i < i_S; i++) {
		cout << "ss[" << i << +"]: " << pd_ss[i] << "\n";
	}

	for (int i = 0; i < i_D; i++) {
		for (int j = 0; j < i_F; j++) {
			cout << "cd[" << i << "][" << j << "]: " << ppd_cd[i][j] << "\n";
		}
	}

	for (int i = 0; i < i_F; i++) {
		for (int j = 0; j < i_M; j++) {
			cout << "cf[" << i << "][" << j << "]: " << ppd_cf[i][j] << "\n";
		}
	}

	for (int i = 0; i < i_M; i++) {
		for (int j = 0; j < i_S; j++) {
			cout << "cm[" << i << "][" << j << "]: " << ppd_cm[i][j] << "\n";
		}
	}

	for (int i = 0; i < i_D; i++) {
		cout << "ud[" << i << "]: " << pd_ud[i] << "\n";
	}

	for (int i = 0; i < i_F; i++) {
		cout << "uf[" << i << "]: " << pd_uf[i] << "\n";
	}

	for (int i = 0; i < i_M; i++) {
		cout << "um[" << i << "]: " << pd_um[i] << "\n";
	}

	for (int i = 0; i < i_S; i++) {
		cout << "p[" << i << "]: " << pd_p[i] << "\n";
	}

	for (int i = 0; i < 2 * i_D; i += 2) {
		for (int j = 0; j < i_F; j++) {
			cout << "xdminmax[" << i << ", " << j << "]: " << ppd_xdminmax[i][j] << "\n";
			cout << "xdminmax[" << i + 1 << ", " << j << "]: " << ppd_xdminmax[i + 1][j] << "\n";
		}
	}
	for (int i = 0; i < 2 * i_F; i += 2) {
		for (int j = 0; j < i_M; j++) {
			cout << "xfminmax[" << i << ", " << j << "]: " << ppd_xfminmax[i][j] << "\n";
			cout << "xfminmax[" << i + 1 << ", " << j << "]: " << ppd_xfminmax[i + 1][j] << "\n";
		}
	}
	for (int i = 0; i < 2 * i_M; i += 2) {
		for (int j = 0; j < i_S; j++) {
			cout << "xmminmax[" << i << ", " << j << "]: " << ppd_xmminmax[i][j] << "\n";
			cout << "xmminmax[" << i + 1 << ", " << j << "]: " << ppd_xmminmax[i + 1][j] << "\n";
		}
	}

}

void CMscnProblem::vPrintSolution(double * pdSolution) {
	int i_counter = 0;
	cout << "D " << pdSolution[i_counter++];
	cout << "\nF " << pdSolution[i_counter++];
	cout << "\nM " << pdSolution[i_counter++];
	cout << "\nS " << pdSolution[i_counter++];

	cout << "\nxd";
	for (int i = 0; i < i_D; i++) {
		cout << "\nDostawca " << i << " -> Fabryki" << endl;
		for (int j = 0; j < i_F; j++) {
			cout << pdSolution[i_counter++] << "    ";
		}
	}

	cout << "\nxf";
	for (int i = 0; i < i_F; i++) {
		cout << "\nFabryka " << i << " -> Magazyny" << endl;
		for (int j = 0; j < i_M; j++) {
			cout << pdSolution[i_counter++] << "    ";
		}
	}

	cout << "\nxm";
	for (int i = 0; i < i_M; i++) {
		cout << "\nMagazyn " << i << " -> Sklepy" << endl;
		for (int j = 0; j < i_S; j++) {
			cout << pdSolution[i_counter++] << "    ";
		}
	}
};