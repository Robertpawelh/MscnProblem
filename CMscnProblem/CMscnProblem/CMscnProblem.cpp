#include "CMscnProblem.h"

CMscnProblem::CMscnProblem(){
	i_num_of_suppliers = BASIC_NUM_OFF_SUPPLIERS;
	i_num_of_factories = BASIC_NUM_OFF_FACTORIES;
	i_num_of_warehouses = BASIC_NUM_OFF_WAREHOUSES;
	i_num_of_shops = BASIC_NUM_OFF_SHOPS;

	pc_max_cap_of_supp = new CArray(i_num_of_suppliers);
	pc_max_cap_of_fact = new CArray(i_num_of_factories);
	pc_max_cap_of_ware = new CArray(i_num_of_warehouses);
	pc_max_cap_of_shop = new CArray(i_num_of_shops);
	
	c_transp_cost_supp_to_fact = CMatrix(i_num_of_suppliers, i_num_of_factories); //ptr?
	c_transp_cost_fact_to_ware = CMatrix(i_num_of_factories, i_num_of_warehouses);
	c_transp_cost_ware_to_shop = CMatrix(i_num_of_warehouses, i_num_of_shops);

	pc_contract_cost_supp = new CArray(i_num_of_suppliers);
	pc_contract_cost_fact = new CArray(i_num_of_factories);
	pc_contract_cost_ware = new CArray(i_num_of_warehouses);

	pc_income = new CArray(i_num_of_shops);
}

CMscnProblem::~CMscnProblem() {};
	/*
	delete[] c_max_cap_of_supp;
	delete[] c_max_cap_of_fact;
	delete[] c_max_cap_of_ware;
	delete[] c_max_cap_of_shop;

//	delete[] c_transp_cost_supp_to_fact; should be ptr?

	delete[] c_contract_cost_supp;
	delete[] c_contract_cost_fact;
	delete[] c_contract_cost_ware;

	delete[] c_income;

	/*
	for (int i = 0; i < 2 * i_num_of_suppliers; i++) {
		delete[] ppd_xdminmax[i];
	}
	delete[] ppd_xdminmax;

	for (int i = 0; i < 2 * i_num_of_factories; i++) {
		delete[] ppd_xfminmax[i];
	}
	delete[] ppd_xfminmax;

	for (int i = 0; i < 2 * i_num_of_warehouses; i++) {
		delete[] ppd_xmminmax[i];
	}
	delete[] ppd_xmminmax;
	
}

bool CMscnProblem::bSetNumOfSuppliers(const int iVal) {
	if (iVal < 0 || iVal == i_num_of_suppliers) {
		return false;
	}

	double* pd_new_sd = new double[iVal];
	double* pd_new_ud = new double[iVal];
	double** ppd_new_cd = new double*[iVal];
	double** ppd_new_xdminmax = new double*[2 * iVal];

	int i_loop_len = (iVal < i_num_of_suppliers) ? iVal : i_num_of_suppliers;
	for (int i = 0; i < i_loop_len; i++) {
		pd_new_sd[i] = c_max_cap_of_supp[i];
		pd_new_ud[i] = c_contract_cost_supp[i];
		ppd_new_cd[i] = c_transp_cost_supp_to_fact[i];
		ppd_new_xdminmax[i] = ppd_xdminmax[i];
	}

	for (int i = i_loop_len; i < 2 * i_loop_len; i++) {
		ppd_new_xdminmax[i] = ppd_xdminmax[i];
	}

	if (i_num_of_suppliers < iVal) {
		for (int i = i_num_of_suppliers; i < iVal; i++) {
			ppd_new_cd[i] = new double[i_num_of_factories];
		}
		for (int i = 2 * i_num_of_suppliers; i < 2 * iVal; i++) {
			ppd_new_xdminmax[i] = new double[i_num_of_factories];
		}
	}

	for (int i = iVal; i < i_num_of_suppliers; i++) {
		delete[] c_transp_cost_supp_to_fact[i];
	}

	delete[] c_max_cap_of_supp;
	delete[] c_contract_cost_supp;
	delete[] c_transp_cost_supp_to_fact;
	c_max_cap_of_supp = pd_new_sd;
	c_contract_cost_supp = pd_new_ud;
	c_transp_cost_supp_to_fact = ppd_new_cd;

	for (int i = 2 * iVal; i < 2 * i_num_of_suppliers; i++) {
		delete[] ppd_xdminmax[i];
	}
	delete[] ppd_xdminmax;
	ppd_xdminmax = ppd_new_xdminmax;

	i_num_of_suppliers = iVal;
	return true;
}

bool CMscnProblem::bSetNumOfFactories(const int iVal) {
	if (iVal < 0 || iVal == i_num_of_factories) {
		return false;
	}

	double* pd_new_sf = new double[iVal];
	double* pd_new_uf = new double[iVal];
	double** ppd_new_cf = new double*[iVal];
	double** ppd_new_cd = new double*[i_num_of_suppliers];
	double** ppd_new_xdminmax = new double*[2 * i_num_of_suppliers];
	double** ppd_new_xfminmax = new double*[2 * iVal];

	for (int i = 0; i < i_num_of_suppliers; i++) {
		ppd_new_cd[i] = new double[iVal];
	}
	for (int i = 0; i < 2 * i_num_of_suppliers; i++) {
		ppd_new_xdminmax[i] = new double[iVal];
	}

	int i_loop_len = (iVal < i_num_of_factories) ? iVal : i_num_of_factories;

	for (int i = 0; i < i_num_of_suppliers; i++) {
		for (int j = 0; j < i_loop_len; j++) {
			ppd_new_cd[i][j] = c_transp_cost_supp_to_fact[i][j];
			ppd_new_xdminmax[i][j] = ppd_xdminmax[i][j];
		}
	}

	for (int i = i_num_of_suppliers; i < 2 * i_num_of_suppliers; i++) {
		for (int j = 0; j < i_loop_len; j++) {
			ppd_new_xdminmax[i][j] = ppd_xdminmax[i][j];
		}
	}

	for (int i = 0; i < i_loop_len; i++) {
		pd_new_sf[i] = c_max_cap_of_fact[i];
		pd_new_uf[i] = c_contract_cost_fact[i];
		ppd_new_cf[i] = c_transp_cost_fact_to_ware[i];
		ppd_new_xfminmax[i] = ppd_xfminmax[i];
	}

	for (int i = i_loop_len; i < 2 * i_loop_len; i++) {
		ppd_new_xfminmax[i] = ppd_xfminmax[i];
	}

	if (i_num_of_factories < iVal) {

		for (int i = i_num_of_factories; i < iVal; i++) {
			ppd_new_cf[i] = new double[i_num_of_warehouses];
		}
		for (int i = 2 * i_num_of_factories; i < 2 * iVal; i++) {
			ppd_new_xfminmax[i] = new double[i_num_of_warehouses];
		}
	}

	for (int i = 0; i < i_num_of_suppliers; i++) {
		delete[] c_transp_cost_supp_to_fact[i];
	}

	for (int i = iVal; i < i_num_of_factories; i++) {
		delete[] c_transp_cost_fact_to_ware[i];
	}

	delete[] c_max_cap_of_fact;
	delete[] c_contract_cost_fact;
	delete[] c_transp_cost_fact_to_ware;
	delete[] c_transp_cost_supp_to_fact;
	c_max_cap_of_fact = pd_new_sf;
	c_contract_cost_fact = pd_new_uf;
	c_transp_cost_supp_to_fact = ppd_new_cd;
	c_transp_cost_fact_to_ware = ppd_new_cf;

	for (int i = 0; i < 2 * i_num_of_suppliers; i++) {
		delete[] ppd_xdminmax[i];
	}

	for (int i = 2 * iVal; i < 2 * i_num_of_factories; i++) {
		delete[] ppd_xfminmax[i];
	}

	delete[] ppd_xfminmax;
	delete[] ppd_xdminmax;
	ppd_xfminmax = ppd_new_xfminmax;
	ppd_xdminmax = ppd_new_xdminmax;

	i_num_of_factories = iVal;

	return true;
}

bool CMscnProblem::bSetNumOfWarehouses(const int iVal) {
	if (iVal < 0 || iVal == i_num_of_warehouses) {
		return false;
	}

	double* pd_new_sm = new double[iVal];
	double* pd_new_um = new double[iVal];
	double** ppd_new_cm = new double*[iVal];
	double** ppd_new_cf = new double*[i_num_of_factories];
	double** ppd_new_xfminmax = new double*[2 * i_num_of_factories];
	double** ppd_new_xmminmax = new double*[2 * iVal];

	for (int i = 0; i < i_num_of_factories; i++) {
		ppd_new_cf[i] = new double[iVal];
	}
	for (int i = 0; i < 2 * i_num_of_factories; i++) {
		ppd_new_xfminmax[i] = new double[iVal];
	}

	int i_loop_len = (iVal < i_num_of_warehouses) ? iVal : i_num_of_warehouses;

	for (int i = 0; i < i_num_of_factories; i++) {
		for (int j = 0; j < i_loop_len; j++) {
			ppd_new_cf[i][j] = c_transp_cost_fact_to_ware[i][j];
			ppd_new_xfminmax[i][j] = ppd_xfminmax[i][j];
		}
	}

	for (int i = i_num_of_factories; i < 2 * i_num_of_factories; i++) {
		for (int j = 0; j < i_loop_len; j++) {
			ppd_new_xfminmax[i][j] = ppd_xfminmax[i][j];
		}
	}


	for (int i = 0; i < i_loop_len; i++) {
		pd_new_sm[i] = c_max_cap_of_ware[i];
		pd_new_um[i] = c_contract_cost_ware[i];
		ppd_new_cm[i] = c_transp_cost_ware_to_shop[i];
		ppd_new_xmminmax[i] = ppd_xmminmax[i];
	}

	for (int i = i_loop_len; i < 2 * i_loop_len; i++) {
		ppd_new_xmminmax[i] = ppd_xmminmax[i];
	}

	if (i_num_of_warehouses < iVal) {

		for (int i = i_num_of_warehouses; i < iVal; i++) {
			ppd_new_cm[i] = new double[i_num_of_shops];
		}
		for (int i = 2 * i_num_of_warehouses; i < 2 * iVal; i++) {
			ppd_new_xmminmax[i] = new double[i_num_of_shops];
		}
	}

	for (int i = 0; i < i_num_of_factories; i++) {
		delete c_transp_cost_fact_to_ware[i];
	}

	for (int i = iVal; i < i_num_of_warehouses; i++) {
		delete[] c_transp_cost_ware_to_shop[i];
	}

	delete[] c_max_cap_of_ware;
	delete[] c_contract_cost_ware;
	delete[] c_transp_cost_ware_to_shop;
	delete[] c_transp_cost_fact_to_ware;
	c_max_cap_of_ware = pd_new_sm;
	c_contract_cost_ware = pd_new_um;
	c_transp_cost_fact_to_ware = ppd_new_cf;
	c_transp_cost_ware_to_shop = ppd_new_cm;

	for (int i = 0; i < 2 * i_num_of_factories; i++) {
		delete[] ppd_xfminmax[i];
	}

	for (int i = 2 * iVal; i < 2 * i_num_of_warehouses; i++) {
		delete[] ppd_xmminmax[i];
	}

	delete[] ppd_xmminmax;
	delete[] ppd_xfminmax;
	ppd_xmminmax = ppd_new_xmminmax;
	ppd_xfminmax = ppd_new_xfminmax;

	i_num_of_warehouses = iVal;

	return true;
}

bool CMscnProblem::bSetNumOfShops(const int iVal) {
	if (iVal < 0 || iVal == i_num_of_shops) {
		return false;
	}

	double* pd_new_ss = new double[iVal];
	double** ppd_new_cm = new double*[i_num_of_warehouses];
	double** ppd_new_xmminmax = new double*[2 * i_num_of_warehouses];
	double *pd_new_p = new double[iVal];

	for (int i = 0; i < i_num_of_warehouses; i++) {
		ppd_new_cm[i] = new double[iVal];
	}
	for (int i = 0; i < 2 * i_num_of_warehouses; i++) {
		ppd_new_xmminmax[i] = new double[iVal];
	}

	int i_loop_len = (iVal < i_num_of_shops) ? iVal : i_num_of_shops;

	for (int i = 0; i < i_num_of_warehouses; i++) {
		for (int j = 0; j < i_loop_len; j++) {
			ppd_new_cm[i][j] = c_transp_cost_ware_to_shop[i][j];
			ppd_new_xmminmax[i][j] = ppd_xmminmax[i][j];
		}
	}

	for (int i = i_num_of_warehouses; i < 2 * i_num_of_warehouses; i++) {
		for (int j = 0; j < i_loop_len; j++) {
			ppd_new_xmminmax[i][j] = ppd_xmminmax[i][j];
		}
	}


	for (int i = 0; i < i_loop_len; i++) {
		pd_new_ss[i] = c_max_cap_of_shop[i];
		pd_new_p[i] = c_income[i];
	}

	for (int i = 0; i < i_num_of_warehouses; i++) {
		delete c_transp_cost_ware_to_shop[i];
	}

	delete[] c_max_cap_of_shop;
	delete[] c_income;
	delete[] c_transp_cost_ware_to_shop;
	c_max_cap_of_shop = pd_new_ss;
	c_income = pd_new_p;
	c_transp_cost_ware_to_shop = ppd_new_cm;

	for (int i = 0; i < 2 * i_num_of_warehouses; i++) {
		delete[] ppd_xmminmax[i];
	}

	delete[] ppd_xmminmax;
	ppd_xmminmax = ppd_new_xmminmax;

	i_num_of_shops = iVal;

	return true;
}
*/
/*
bool CMscnProblem::bSetValInCf(int iRow, int iColumn, double dVal) {
	if (iRow < 0 || iRow >= i_num_of_factories || iColumn < 0 || iColumn >= i_num_of_warehouses) {
		return false;
	}
	c_transp_cost_fact_to_ware[iRow][iColumn] = dVal;
	return true;
}

bool CMscnProblem::bSetValInCm(int iRow, int iColumn, double dVal) {
	if (iRow < 0 || iRow >= i_num_of_warehouses || iColumn < 0 || iColumn >= i_num_of_shops) {
		return false;
	}
	c_transp_cost_ware_to_shop[iRow][iColumn] = dVal;
	return true;
}


bool CMscnProblem::bSetValInSd(int iIndex, double dVal) {
	if (iIndex < 0 || iIndex >= i_num_of_suppliers) {
		return false;
	}
	pd_max_cap_of_supp[iIndex] = dVal;
	return true;
}

bool CMscnProblem::bSetValInSf(int iIndex, double dVal) {
	if (iIndex < 0 || iIndex >= i_num_of_factories) {
		return false;
	}
	pd_max_cap_of_fact[iIndex] = dVal;
	return true;
}

bool CMscnProblem::bSetValInSm(int iIndex, double dVal) {
	if (iIndex < 0 || iIndex >= i_num_of_warehouses) {
		return false;
	}
	pd_max_cap_of_ware[iIndex] = dVal;
	return true;
}

bool CMscnProblem::bSetValInSs(int iIndex, double dVal) {
	if (iIndex < 0 || iIndex >= i_num_of_shops) {
		return false;
	}
	pd_max_cap_of_shop[iIndex] = dVal;
	return true;
}

bool CMscnProblem::bSetValInUd(int iIndex, double dVal) {
	if (iIndex < 0 || iIndex >= i_num_of_suppliers) {
		return false;
	}
	pd_contract_cost_sup[iIndex] = dVal;
	return true;
}

bool CMscnProblem::bSetValInUf(int iIndex, double dVal) {
	if (iIndex < 0 || iIndex >= i_num_of_factories) {
		return false;
	}
	pd_contract_cost_fact[iIndex] = dVal;
	return true;
}

bool CMscnProblem::bSetValInUm(int iIndex, double dVal) {
	if (iIndex < 0 || iIndex >= i_num_of_warehouses) {
		return false;
	}
	pd_contract_cost_ware[iIndex] = dVal;
	return true;
}

bool CMscnProblem::bSetValInP(int iIndex, double dVal) {
	if (iIndex < 0 || iIndex >= i_num_of_shops) {
		return false;
	}
	pd_income[iIndex] = dVal;
	return true;
}

bool CMscnProblem::bSetValInXdminmax(int iRow, int iColumn, double dVal) {
	if (iRow < 0 || iRow >= 2 * i_num_of_suppliers || iColumn < 0 || iColumn >= i_num_of_factories) {
		return false;
	}
	ppd_xdminmax[iRow][iColumn] = dVal;
	return true;
}

bool CMscnProblem::bSetValInXfminmax(int iRow, int iColumn, double dVal) {
	if (iRow < 0 || iRow >= 2 * i_num_of_factories || iColumn < 0 || iColumn >= i_num_of_warehouses) {
		return false;
	}
	ppd_xfminmax[iRow][iColumn] = dVal;
	return true;
}

bool CMscnProblem::bSetValInXmminmax(int iRow, int iColumn, double dVal) {
	if (iRow < 0 || iRow >= 2 * i_num_of_warehouses || iColumn < 0 || iColumn >= i_num_of_shops) {
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
		if (iId-- == 0) return i_num_of_suppliers;
		if (iId-- == 0) return i_num_of_factories;
		if (iId-- == 0) return i_num_of_warehouses;
		if (iId-- == 0) return i_num_of_shops;
	}

	if (iId >= i_num_of_suppliers * i_num_of_factories) {
		iId -= i_num_of_suppliers * i_num_of_factories;
	}
	else {
		bIsSuccess = true;
		return ppd_xdminmax[2 * (iId / i_num_of_factories)][iId%i_num_of_factories];
	}

	if (iId >= i_num_of_factories * i_num_of_warehouses) {
		iId -= i_num_of_factories * i_num_of_warehouses;
	}
	else {
		bIsSuccess = true;
		return ppd_xfminmax[2 * (iId / i_num_of_warehouses)][iId%i_num_of_warehouses];
	}

	if (iId >= i_num_of_warehouses * i_num_of_shops) {
		iId -= i_num_of_warehouses * i_num_of_shops;
	}
	else {
		bIsSuccess = true;
		return ppd_xmminmax[2 * (iId / i_num_of_shops)][iId%i_num_of_shops];
	}
	bIsSuccess = false;
	return -1;
}
*/

double CMscnProblem::dGetMax(int iId, bool &bIsSuccess) {
	if (iId >= NUMBER_OF_PRODUCTION_LEVELS) {
		iId -= NUMBER_OF_PRODUCTION_LEVELS;
	}

	else {
		bIsSuccess = true;
		if (iId-- == 0) return i_num_of_suppliers;
		if (iId-- == 0) return i_num_of_factories;
		if (iId-- == 0) return i_num_of_warehouses;
		if (iId-- == 0) return i_num_of_shops;
	}

	if (iId >= i_num_of_suppliers) {
		iId -= i_num_of_suppliers;
	}
	else {
		bIsSuccess = true;
		return (*pc_max_cap_of_supp)[iId];
	}

	if (iId >= i_num_of_factories) {
		iId -= i_num_of_factories;
	}
	else {
		bIsSuccess = true;
		return (*pc_max_cap_of_fact)[iId];//c_xfmax[iId];//[1 + 2 * (iId / i_num_of_warehouses)][iId%i_num_of_warehouses];
	}

	if (iId >= i_num_of_warehouses) {
		iId -= i_num_of_warehouses;
	}
	else {
		bIsSuccess = true;
		return (*pc_max_cap_of_ware)[iId];//c_xfmax[iId];//[1 + 2 * (iId / i_num_of_warehouses)][iId%i_num_of_warehouses];
	}

	if (iId >= i_num_of_shops) {
		bIsSuccess = false;
		return -1;
	}
	else {
		bIsSuccess = true;
		return (*pc_max_cap_of_shop)[iId];//c_xfmax[iId];//[1 + 2 * (iId / i_num_of_warehouses)][iId%i_num_of_warehouses];
	}


}



double CMscnProblem::d_calc_transp_cost_for_matrix(int & iId, double * pdSolution, CMatrix *pdCostMatrix, int iX, int iY){ //upewnij sie czy nie kopiuje
	double d_transport_cost = 0;
	for (int i = 0; i < iX; i++) {
		for (int j = 0; j < iY; j++) {
			d_transport_cost += (*pdCostMatrix)(i,j) * pdSolution[iId++];
		}
	}
	return d_transport_cost;
}

double CMscnProblem::d_calc_transp_cost(double* pdSolution) {
	double d_transport_cost = 0;
	int i_id_solution = NUMBER_OF_PRODUCTION_LEVELS;
	
	d_transport_cost += d_calc_transp_cost_for_matrix(i_id_solution, pdSolution, &c_transp_cost_supp_to_fact, i_num_of_suppliers, i_num_of_factories);
	d_transport_cost += d_calc_transp_cost_for_matrix(i_id_solution, pdSolution, &c_transp_cost_fact_to_ware, i_num_of_factories, i_num_of_warehouses);
	d_transport_cost += d_calc_transp_cost_for_matrix(i_id_solution, pdSolution, &c_transp_cost_ware_to_shop, i_num_of_warehouses, i_num_of_shops);

	return d_transport_cost;
}

double CMscnProblem::d_calc_contract_cost_for_array(int & iId, double * pdSolution, CArray *pcCostArray, int iX, int iY) {
	double d_contract_cost = 0;
	for (int i = 0; i < iX; i++) {
		bool b_signed_contract = false;
		int j = 0;
		while (j < iY && !b_signed_contract) {
			b_signed_contract = (pdSolution[iId] > 0);
			j++;
		}
		if (b_signed_contract) {
			d_contract_cost += (*pcCostArray)[i];
		}
	}
	return d_contract_cost;
}
double CMscnProblem::d_calc_contract_cost(double* pdSolution) {
	double d_contract_cost = 0;
	int i_id_in_solution = NUMBER_OF_PRODUCTION_LEVELS;

	d_contract_cost += d_calc_contract_cost_for_array(i_id_in_solution, pdSolution, pc_contract_cost_supp, i_num_of_suppliers, i_num_of_factories);
	d_contract_cost += d_calc_contract_cost_for_array(i_id_in_solution, pdSolution, pc_contract_cost_fact, i_num_of_factories, i_num_of_warehouses);
	d_contract_cost += d_calc_contract_cost_for_array(i_id_in_solution, pdSolution, pc_contract_cost_ware, i_num_of_warehouses, i_num_of_shops);

	return d_contract_cost;
}

double CMscnProblem::d_calc_income(double * pdSolution) {
	double d_income = 0;
	int i_counter = NUMBER_OF_PRODUCTION_LEVELS + i_num_of_suppliers * i_num_of_factories + i_num_of_factories * i_num_of_warehouses;

	for (int i = 0; i < i_num_of_warehouses; i++) {
		for (int j = 0; j < i_num_of_shops; j++) {
			d_income += (*pc_income)[j] * pdSolution[i_counter++];
		}
	}
	return d_income;
}

double CMscnProblem::d_calc_profit(double* pdSolution) {
	return d_calc_income(pdSolution) - d_calc_transp_cost(pdSolution) - d_calc_contract_cost(pdSolution);
}

double CMscnProblem::dGetQuality(double * pdSolution, bool &bIsSuccess) {
//	bIsSuccess = bConstraintsSatisfied;
	//vRepairIncorrectSolution(pdSolution);
	return d_calc_profit(pdSolution);
}

/*
void CMscnProblem::vRepairIncorrectSolution(double * pdSolution) {
	bool b_is_success;
	double d_current_sum_xd = 0;
	double d_current_sum_xf = 0;
	double d_current_sum_xm = 0;
	double d_sum_from_d_to_f = 0;
	double d_sum_from_f_to_m = 0;
	double d_total_sum_xm = 0;

	int i_counter = NUMBER_OF_PRODUCTION_LEVELS;

	double d_sum_from_m_to_s = 0;

	for (int i = 0; i < i_num_of_suppliers; i++) {

		for (int j = 0; j < i_num_of_factories; j++) {
			if (pdSolution[i_counter] >= 0) {
				d_current_sum_xd += pdSolution[i_counter];
				i_counter++;
			}
			else {
				pdSolution[i_counter] = dGetMin(i_counter, b_is_success);
				d_current_sum_xd += pdSolution[i_counter];
				i_counter++;
			}
		}

		while (d_current_sum_xd > pd_max_cap_of_supp[i]) {
			i_counter -= i_num_of_factories;	

			for (int j = 0; j < i_num_of_factories; j++) {
				if (pdSolution[i_counter] * REDUCTION_PARAMETER > dGetMin(i_counter, b_is_success)) {
					d_current_sum_xd -= pdSolution[i_counter] * (1 - REDUCTION_PARAMETER);
					pdSolution[i_counter] *= REDUCTION_PARAMETER;
					i_counter++;
				}
				else {
					d_current_sum_xd -= (pdSolution[i_counter] - dGetMin(i_counter, b_is_success));
					pdSolution[i_counter] = dGetMin(i_counter, b_is_success);
					i_counter++;
				}
			}
		}

		d_current_sum_xd = 0;
	}

	for (int i = 0; i < i_num_of_factories; i++) {
		for (int j = 0; j < i_num_of_warehouses; j++) {
			if (pdSolution[i_counter] >= 0) {
				d_current_sum_xf += pdSolution[i_counter];
				i_counter++;
			}
			else {
				pdSolution[i_counter] = dGetMin(i_counter, b_is_success);
				d_current_sum_xf += pdSolution[i_counter];
				i_counter++;
			}
		}

		while (d_current_sum_xf > pd_max_cap_of_fact[i]) {
			i_counter -= i_num_of_warehouses;

			for (int j = 0; j < i_num_of_warehouses; j++) {
				if (pdSolution[i_counter] * REDUCTION_PARAMETER > dGetMin(i_counter, b_is_success)) {
					d_current_sum_xf -= pdSolution[i_counter] * (1 - REDUCTION_PARAMETER);
					pdSolution[i_counter] *= REDUCTION_PARAMETER;
					i_counter++;
				}
				else {
					d_current_sum_xf -= (pdSolution[i_counter] - dGetMin(i_counter, b_is_success));
					pdSolution[i_counter] = dGetMin(i_counter, b_is_success);
					i_counter++;
				}
			}
		}

		d_current_sum_xf = 0;
	}

	for (int i = 0; i < i_num_of_warehouses; i++) {
		for (int j = 0; j < i_num_of_shops; j++) {
			if (pdSolution[i_counter] >= 0) {
				d_current_sum_xm += pdSolution[i_counter];
				i_counter++;
			}
			else {
				pdSolution[i_counter] = dGetMin(i_counter, b_is_success);
				d_current_sum_xm += pdSolution[i_counter];
				i_counter++;
			}
		}

		while (d_current_sum_xm > pd_max_cap_of_ware[i]) {
			i_counter -= i_num_of_shops;

			for (int j = 0; j < i_num_of_shops; j++) {
				if (pdSolution[i_counter] * REDUCTION_PARAMETER > dGetMin(i_counter, b_is_success)) {
					d_current_sum_xm -= pdSolution[i_counter] * (1 - REDUCTION_PARAMETER);
					pdSolution[i_counter] *= REDUCTION_PARAMETER;
					i_counter++;
				}
				else {
					d_current_sum_xm -= (pdSolution[i_counter] - dGetMin(i_counter, b_is_success));
					pdSolution[i_counter] = dGetMin(i_counter, b_is_success);
					i_counter++;
				}
			}
		}

		d_current_sum_xm = 0;
	}

	d_current_sum_xm = 0;
	i_counter = NUMBER_OF_PRODUCTION_LEVELS + i_num_of_suppliers * i_num_of_factories + i_num_of_factories * i_num_of_warehouses;

	for (int i = 0; i < i_num_of_shops; i++) {
		for (int j = 0; j < i_num_of_warehouses; j++) {
			d_current_sum_xm += pdSolution[i_counter + i_num_of_shops * j];
		}


		while (d_current_sum_xm > pd_max_cap_of_shop[i]) {

			for (int j = 0; j < i_num_of_warehouses; j++) {
				if (pdSolution[i_counter + i_num_of_warehouses * j] * REDUCTION_PARAMETER > dGetMin(i_counter + i_num_of_warehouses * j, b_is_success)) {
					d_current_sum_xm -= pdSolution[i_counter + i_num_of_warehouses * j] * (1 - REDUCTION_PARAMETER);
					pdSolution[i_counter + i_num_of_warehouses * j] *= REDUCTION_PARAMETER;
				}
				else {
					d_current_sum_xm -= (pdSolution[i_counter + i_num_of_warehouses * j] - dGetMin(i_counter + i_num_of_warehouses * j, b_is_success));
					pdSolution[i_counter + i_num_of_warehouses * j] = dGetMin(i_counter + i_num_of_warehouses * j, b_is_success);
				}

			}
		}

		d_current_sum_xm = 0;
	}

	for (int i = 0; i < i_num_of_warehouses; i++) {
		for (int j = 0; j < i_num_of_factories; j++) {
			d_sum_from_f_to_m += pdSolution[NUMBER_OF_PRODUCTION_LEVELS + i_num_of_suppliers * i_num_of_factories + i + j * i_num_of_factories];
		}

		for (int j = 0; j < i_num_of_shops; j++) {
			d_sum_from_m_to_s += pdSolution[NUMBER_OF_PRODUCTION_LEVELS + i_num_of_suppliers * i_num_of_factories + i_num_of_factories * i_num_of_warehouses + i * i_num_of_shops + j];
		}

		while (d_sum_from_f_to_m < d_sum_from_m_to_s) {

			for (int j = 0; j < i_num_of_factories; j++) {		// zwieksza
				i_counter = NUMBER_OF_PRODUCTION_LEVELS + i_num_of_suppliers * i_num_of_factories + i + j * i_num_of_factories;
				if (pdSolution[i_counter] == 0) {
					pdSolution[i_counter] = (dGetMax(i_counter, b_is_success) - dGetMin(i_counter, b_is_success)) / 2;
				}

				if (pdSolution[i_counter] * INCREASE_PARAMETER < dGetMax(i_counter, b_is_success)) {
					d_sum_from_f_to_m += pdSolution[i_counter] * (INCREASE_PARAMETER - 1);
					pdSolution[i_counter] *= INCREASE_PARAMETER;
					i_counter++;
				}
				else {
					d_sum_from_f_to_m += (dGetMax(i_counter, b_is_success) - pdSolution[i_counter]);
					pdSolution[i_counter] = dGetMax(i_counter, b_is_success);
					i_counter++;
				}
			}

			if (d_sum_from_f_to_m < d_sum_from_m_to_s) {	//zmniejsza
				for (int j = 0; j < i_num_of_shops; j++) {
					i_counter = NUMBER_OF_PRODUCTION_LEVELS + i_num_of_suppliers * i_num_of_factories + i_num_of_factories * i_num_of_warehouses + i * i_num_of_shops + j;
					if (pdSolution[i_counter] * REDUCTION_PARAMETER > dGetMin(i_counter, b_is_success)) {
						d_sum_from_m_to_s -= pdSolution[i_counter] * (1 - REDUCTION_PARAMETER);
						pdSolution[i_counter] *= REDUCTION_PARAMETER;
						i_counter++;
					}
					else {
						d_sum_from_m_to_s -= pdSolution[i_counter] - dGetMin(i_counter, b_is_success);
						pdSolution[i_counter] = dGetMin(i_counter, b_is_success);
						i_counter++;
					}
				}
			}


		}
		d_sum_from_f_to_m = 0;
		d_sum_from_m_to_s = 0;
	}

	for (int i = 0; i < i_num_of_factories; i++) {
		for (int j = 0; j < i_num_of_suppliers; j++) {
			d_sum_from_d_to_f += pdSolution[NUMBER_OF_PRODUCTION_LEVELS + i + j * i_num_of_factories];
		}

		for (int j = 0; j < i_num_of_warehouses; j++) {
			d_sum_from_f_to_m += pdSolution[NUMBER_OF_PRODUCTION_LEVELS + i_num_of_suppliers * i_num_of_factories + i * i_num_of_warehouses + j];
		}

		while (d_sum_from_d_to_f < d_sum_from_f_to_m) {
			for (int j = 0; j < i_num_of_suppliers; j++) {
				i_counter = NUMBER_OF_PRODUCTION_LEVELS + i + j * i_num_of_factories;
				if (pdSolution[i_counter] == 0) {
					pdSolution[i_counter] = (dGetMax(i_counter, b_is_success) - dGetMin(i_counter, b_is_success)) / 2;
				}
				if (pdSolution[i_counter] * INCREASE_PARAMETER < dGetMax(i_counter, b_is_success)) {
					d_sum_from_d_to_f += pdSolution[i_counter] * (INCREASE_PARAMETER - 1);
					pdSolution[i_counter] *= INCREASE_PARAMETER;
					i_counter++;
				}
				else {
					d_sum_from_d_to_f += (dGetMax(i_counter, b_is_success) - pdSolution[i_counter]);
					pdSolution[i_counter] = dGetMax(i_counter, b_is_success);
					i_counter++;
				}
			}
		}
		d_sum_from_d_to_f = 0;
		d_sum_from_f_to_m = 0;
	}
}
*/

bool CMscnProblem::bConstraintsSatisfied(double * pdSolution, string & sErrorCode) { // do poprawienia
	sErrorCode = "";
	if (pdSolution == NULL) {
		sErrorCode = NULL_ERROR;
		return false;
	}

	int i_counter = 0;
	if (i_num_of_suppliers != pdSolution[i_counter++] ||
		i_num_of_factories != pdSolution[i_counter++] ||
		i_num_of_warehouses != pdSolution[i_counter++] ||
		i_num_of_shops != pdSolution[i_counter++]) {
		sErrorCode = LENGTH_ERROR;
		return false;
	}

	double d_sum_supplier_sends = 0;
	double d_sum_factory_sends = 0;
	double d_sum_warehouse_sends = 0;
	double d_total_sum_xd = 0;
	double d_total_sum_xf = 0;
	double d_total_sum_xm = 0;

	for (int i = 0; i < i_num_of_suppliers; i++) {
		for (int j = 0; j < i_num_of_factories; j++) {	
			if (pdSolution[i_counter] >= 0) {
				d_sum_supplier_sends += pdSolution[i_counter];
				i_counter++;
			}
			else {
				sErrorCode = NEGATIVE_VAL_ERROR;
				return false;
			}
		}

		if (d_sum_supplier_sends > (*pc_max_cap_of_supp)[i]) {
			//sErrorCode.append(BIGGER_THAN_PRODUCED_ERROR,"supplier");
			return false;
		}
		d_sum_supplier_sends = 0;
	}

	for (int i = 0; i < i_num_of_factories; i++) {
		for (int j = 0; j < i_num_of_warehouses; j++) {
			if (pdSolution[i_counter] >= 0) {
				d_sum_factory_sends += pdSolution[i_counter];
				i_counter++;
			}
			else {
				sErrorCode = NEGATIVE_VAL_ERROR;
				return false;
			}
		}

		if (d_sum_factory_sends > (*pc_max_cap_of_fact)[i]) {
		//	sErrorCode.append(BIGGER_THAN_PRODUCED_ERROR, "factory");
			return false;
		}

		d_sum_factory_sends = 0;
	}

	for (int i = 0; i < i_num_of_warehouses; i++) {
		for (int j = 0; j < i_num_of_shops; j++) {
			if (pdSolution[i_counter] >= 0) {
				d_sum_warehouse_sends += pdSolution[i_counter];
				i_counter++;
			}
			else {
				sErrorCode = NEGATIVE_VAL_ERROR;
				return false;
			}
		}

		if (d_sum_warehouse_sends > (*pc_max_cap_of_ware)[i]) {
			//sErrorCode.append(BIGGER_THAN_PRODUCED_ERROR, "warehouse");
			return false;
		}
		d_sum_warehouse_sends = 0;
	}

	d_sum_warehouse_sends = 0;
	i_counter = NUMBER_OF_PRODUCTION_LEVELS + i_num_of_suppliers * i_num_of_factories + i_num_of_factories * i_num_of_warehouses;

	for (int i = 0; i < i_num_of_shops; i++) {
		for (int j = 0; j < i_num_of_warehouses; j++) {
			d_sum_warehouse_sends += pdSolution[i_counter + i_num_of_warehouses * i + j];
		}

		if (d_sum_warehouse_sends > (*pc_max_cap_of_shop)[i]) {
			sErrorCode = BIGGER_THAN_PRODUCED_ERROR;
			return false;
		}

		d_sum_warehouse_sends = 0;
		i_counter++;
	}

	if (d_total_sum_xd < d_total_sum_xf || d_total_sum_xf < d_total_sum_xm) {
		sErrorCode = SUM_ERROR;
		return false;
	}


	i_counter = NUMBER_OF_PRODUCTION_LEVELS;
	return true;
}

bool CMscnProblem::bSaveProblemInstance(string sFileName) {
	FILE* pf_file = fopen(sFileName.c_str(), "w+");
	if (pf_file == NULL) {
		return false;
	}
	fprintf(pf_file, "%s %i", "D", i_num_of_suppliers);
	fprintf(pf_file, "%s %i", "\nF", i_num_of_factories);
	fprintf(pf_file, "%s %i", "\nM", i_num_of_warehouses);
	fprintf(pf_file, "%s %i", "\nS", i_num_of_shops);

	fprintf(pf_file, "%s", "\nsd");
	for (int i = 0; i < i_num_of_suppliers; i++) {
		fprintf(pf_file, "\n%lf", pc_max_cap_of_supp[i]);
	}

	fprintf(pf_file, "%s", "\nsf");
	for (int i = 0; i < i_num_of_factories; i++) {
		fprintf(pf_file, "\n%lf", pc_max_cap_of_fact[i]);
	}

	fprintf(pf_file, "%s", "\nsm");
	for (int i = 0; i < i_num_of_warehouses; i++) {
		fprintf(pf_file, "\n%lf", pc_max_cap_of_ware[i]);
	}

	fprintf(pf_file, "%s", "\nss");
	for (int i = 0; i < i_num_of_shops; i++) {
		fprintf(pf_file, "\n%lf", pc_max_cap_of_shop[i]);
	}

	fprintf(pf_file, "%s", "\ncd");
	for (int i = 0; i < i_num_of_suppliers; i++) {
		for (int j = 0; j < i_num_of_factories; j++) {
			fprintf(pf_file, "\n%lf", c_transp_cost_supp_to_fact(i,j));
		}
	}

	fprintf(pf_file, "%s", "\ncf");
	for (int i = 0; i < i_num_of_factories; i++) {
		for (int j = 0; j < i_num_of_warehouses; j++) {
			fprintf(pf_file, "\n%lf", c_transp_cost_fact_to_ware(i,j));
		}
	}

	fprintf(pf_file, "%s", "\ncm");
	for (int i = 0; i < i_num_of_warehouses; i++) {
		for (int j = 0; j < i_num_of_shops; j++) {
			fprintf(pf_file, "\n%lf", c_transp_cost_ware_to_shop(i,j));
		}
	}

	fprintf(pf_file, "%s", "\nud");
	for (int i = 0; i < i_num_of_suppliers; i++) {
		fprintf(pf_file, "\n%lf", pc_contract_cost_supp[i]);
	}

	fprintf(pf_file, "%s", "\nuf");
	for (int i = 0; i < i_num_of_factories; i++) {
		fprintf(pf_file, "\n%lf", pc_contract_cost_fact[i]);
	}

	fprintf(pf_file, "%s", "\num");
	for (int i = 0; i < i_num_of_warehouses; i++) {
		fprintf(pf_file, "\n%lf", pc_contract_cost_ware[i]);
	}

	fprintf(pf_file, "%s", "\np");
	for (int i = 0; i < i_num_of_shops; i++) {
		fprintf(pf_file, "\n%lf", pc_income[i]);
	}
	/*
	fprintf(pf_file, "%s", "\nxdminmax");
	for (int i = 0; i < 2 * i_num_of_suppliers; i += 2) {
		for (int j = 0; j < i_num_of_factories; j++) {
			fprintf(pf_file, "\n%lf ", ppd_xdminmax[i][j]);
			fprintf(pf_file, "%lf", ppd_xdminmax[i + 1][j]);
		}
	}

	fprintf(pf_file, "%s", "\nxfminmax");
	for (int i = 0; i < 2 * i_num_of_factories; i += 2) {
		for (int j = 0; j < i_num_of_warehouses; j++) {
			fprintf(pf_file, "\n%lf ", ppd_xfminmax[i][j]);
			fprintf(pf_file, "%lf", ppd_xfminmax[i + 1][j]);
		}
	}

	fprintf(pf_file, "%s", "\nxmminmax");
	for (int i = 0; i < 2 * i_num_of_warehouses; i += 2) {
		for (int j = 0; j < i_num_of_shops; j++) {
			fprintf(pf_file, "\n%lf ", ppd_xmminmax[i][j]);
			fprintf(pf_file, "%lf", ppd_xmminmax[i + 1][j]);
		}
	}
	*/
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
	for (int i = 0; i < i_num_of_suppliers; i++) {
		for (int j = 0; j < i_num_of_factories; j++) {
			fprintf(pf_file, "\n%lf ", pdSolution[i_counter++]);	//tu moge nieco poprawic te odstepy. w powyzszej funkcji chyba tez
		}
	}

	fprintf(pf_file, "%s", "\nxf\n");
	for (int i = 0; i < i_num_of_factories; i++) {
		for (int j = 0; j < i_num_of_warehouses; j++) {
			fprintf(pf_file, "\n%lf ", pdSolution[i_counter++]);
		}
	}

	fprintf(pf_file, "%s", "\nxm");
	for (int i = 0; i < i_num_of_warehouses; i++) {
		for (int j = 0; j < i_num_of_shops; j++) {
			fprintf(pf_file, "\n%lf ", pdSolution[i_counter++]);
		}
	}
	fclose(pf_file);
	return true;
};
/*
bool CMscnProblem::bReadProblemInstance(string sFileName) {
	FILE* pf_file = fopen(sFileName.c_str(), "r");
	if (pf_file == NULL) {
		return false;
	}

	char c_val[DESC_IN_FILE_SIZE];
	int i_num;
	fscanf(pf_file, "%[^0-9] %i", c_val, &i_num);
	bSetNumOfSuppliers(i_num);
	fscanf(pf_file, "%[^0-9] %i", c_val, &i_num);
	bSetNumOfFactories(i_num);
	fscanf(pf_file, "%[^0-9] %i", c_val, &i_num);
	bSetNumOfWarehouses(i_num);
	fscanf(pf_file, "%[^0-9] %i", c_val, &i_num);
	bSetNumOfShops(i_num);

	c_max_cap_of_supp.bReadValFromFile(pf_file);
	c_max_cap_of_fact.bReadValFromFile(pf_file);
	c_max_cap_of_ware.bReadValFromFile(pf_file);
	c_max_cap_of_shop.bReadValFromFile(pf_file);

	c_transp_cost_supp_to_fact.bReadValFromFile(pf_file);
	c_transp_cost_fact_to_ware.bReadValFromFile(pf_file);
	c_transp_cost_ware_to_shop.bReadValFromFile(pf_file);

	c_contract_cost_supp.bReadValFromFile(pf_file);
	c_contract_cost_fact.bReadValFromFile(pf_file);
	c_contract_cost_ware.bReadValFromFile(pf_file);
	c_income.bReadValFromFile(pf_file);

	/*
	for (int i = 0; i < 2 * i_num_of_suppliers; i += 2) {
		for (int j = 0; j < i_num_of_factories; j++) {
			fscanf(pf_file, "%[^0-9] %lf", c_val, &d_num);
			bSetValInXdminmax(i, j, d_num);
			fscanf(pf_file, "%[^0-9] %lf", c_val, &d_num);
			bSetValInXdminmax(i + 1, j, d_num);
		}
	}

	for (int i = 0; i < 2 * i_num_of_factories; i += 2) {
		for (int j = 0; j < i_num_of_warehouses; j++) {
			fscanf(pf_file, "%[^0-9] %lf", c_val, &d_num);
			bSetValInXfminmax(i, j, d_num);
			fscanf(pf_file, "%[^0-9] %lf", c_val, &d_num);
			bSetValInXfminmax(i + 1, j, d_num);
		}
	}

	for (int i = 0; i < 2 * i_num_of_warehouses; i += 2) {
		for (int j = 0; j < i_num_of_shops; j++) {
			fscanf(pf_file, "%[^0-9] %lf", c_val, &d_num);
			bSetValInXmminmax(i, j, d_num);
			fscanf(pf_file, "%[^0-9] %lf", c_val, &d_num);
			bSetValInXmminmax(i + 1, j, d_num);
		}
	}
	fclose(pf_file);
	return true;
}
*/
double* CMscnProblem::pdReadSolution(string sFileName) {
	FILE* pf_file = fopen(sFileName.c_str(), "r");
	if (pf_file == NULL) {
		return nullptr;
	}

	double * pd_solution = new double[NUMBER_OF_PRODUCTION_LEVELS + i_num_of_factories * i_num_of_suppliers + i_num_of_suppliers * i_num_of_warehouses + i_num_of_warehouses * i_num_of_shops];
	char c_val[DESC_IN_FILE_SIZE];
	int i_counter = 0;
	fscanf(pf_file, "%[^0-9] %lf", c_val, &pd_solution[i_counter++]);
	fscanf(pf_file, "%[^0-9] %lf", c_val, &pd_solution[i_counter++]);
	fscanf(pf_file, "%[^0-9] %lf", c_val, &pd_solution[i_counter++]);
	fscanf(pf_file, "%[^0-9] %lf", c_val, &pd_solution[i_counter++]);

	for (int i = 0; i < i_num_of_factories * i_num_of_suppliers + i_num_of_suppliers * i_num_of_warehouses + i_num_of_warehouses * i_num_of_shops; i++) {
		fscanf(pf_file, "%[^0-9] %lf", c_val, &pd_solution[i_counter + i]);
	}

	fclose(pf_file);
	return pd_solution;
}

void CMscnProblem::vGenerateInstance(int iInstanceSeed) {
	CRandom c_random_gen(iInstanceSeed);
	pc_max_cap_of_supp->vFillRandomly(&c_random_gen, MIN_SD, MAX_SD);
	pc_max_cap_of_fact->vFillRandomly(&c_random_gen, MIN_SF, MAX_SF);
	pc_max_cap_of_ware->vFillRandomly(&c_random_gen, MIN_SM, MAX_SM);
	pc_max_cap_of_shop->vFillRandomly(&c_random_gen, MIN_SS, MAX_SS);

	c_transp_cost_supp_to_fact.vFillRandomly(&c_random_gen, MIN_CD, MAX_CD);
	c_transp_cost_fact_to_ware.vFillRandomly(&c_random_gen, MIN_CF, MAX_CF);
	c_transp_cost_ware_to_shop.vFillRandomly(&c_random_gen, MIN_CM, MAX_CM);

	pc_contract_cost_supp->vFillRandomly(&c_random_gen, MIN_UD, MAX_CD);
	pc_contract_cost_fact->vFillRandomly(&c_random_gen, MIN_UF, MAX_CF);
	pc_contract_cost_ware->vFillRandomly(&c_random_gen, MIN_UM, MAX_CM);
	pc_income->vFillRandomly(&c_random_gen, MIN_P, MAX_P);

	/*
	for (int i = 0; i < 2 * i_num_of_suppliers; i += 2) {
		for (int j = 0; j < i_num_of_factories; j++) {
			bSetValInXdminmax(i, j, 0);
			bSetValInXdminmax(i + 1, j, min(c_max_cap_of_supp[i / 2], c_max_cap_of_fact[j]));
		}
	}

	for (int i = 0; i < 2 * i_num_of_factories; i += 2) {
		for (int j = 0; j < i_num_of_warehouses; j++) {
			double d_d_to_f_max = 0;
			for (int k = 1; k < 2 * i_num_of_suppliers; k += 2) {
				d_d_to_f_max += ppd_xdminmax[k][i / 2];
			}

			bSetValInXfminmax(i, j, 0);
			double d_max_correct_val = min(c_max_cap_of_fact[i / 2], c_max_cap_of_ware[j]);
			bSetValInXfminmax(i + 1, j, min(d_max_correct_val, d_d_to_f_max));
		}
	}
	for (int i = 0; i < 2 * i_num_of_warehouses; i += 2) {
		for (int j = 0; j < i_num_of_shops; j++) {
			double d_f_to_m_max = 0;
			for (int k = 1; k < 2 * i_num_of_factories; k += 2) {
				d_f_to_m_max += ppd_xfminmax[k][i / 2];
			}

			bSetValInXmminmax(i, j, 0);
			double d_max_correct_val = min(c_max_cap_of_ware[i / 2], c_max_cap_of_shop[j]);
			bSetValInXmminmax(i + 1, j, min(d_max_correct_val, d_f_to_m_max));
		}
	}
	*/
}

void CMscnProblem::vPrintInstance() {
	for (int i = 0; i < i_num_of_suppliers; i++) {
		cout << "sd[" << i << +"]: " << (*pc_max_cap_of_supp)[i] << "\n";
	}

	for (int i = 0; i < i_num_of_factories; i++) {
		cout << "sf[" << i << +"]: " << (*pc_max_cap_of_fact)[i] << "\n";
	}

	for (int i = 0; i < i_num_of_warehouses; i++) {
		cout << "sm[" << i << +"]: " << (*pc_max_cap_of_ware)[i] << "\n";
	}

	for (int i = 0; i < i_num_of_shops; i++) {
		cout << "ss[" << i << +"]: " << (*pc_max_cap_of_shop)[i] << "\n";
	}

	for (int i = 0; i < i_num_of_suppliers; i++) {
		for (int j = 0; j < i_num_of_factories; j++) {
			cout << "cd[" << i << "][" << j << "]: " << c_transp_cost_supp_to_fact(i,j) << "\n";
		}
	}

	for (int i = 0; i < i_num_of_factories; i++) {
		for (int j = 0; j < i_num_of_warehouses; j++) {
			cout << "cf[" << i << "][" << j << "]: " << c_transp_cost_fact_to_ware(i,j) << "\n";
		}
	}

	for (int i = 0; i < i_num_of_warehouses; i++) {
		for (int j = 0; j < i_num_of_shops; j++) {
			cout << "cm[" << i << "][" << j << "]: " << c_transp_cost_ware_to_shop(i, j) << "\n";
		}
	}

	for (int i = 0; i < i_num_of_suppliers; i++) {
		cout << "ud[" << i << "]: " << (*pc_contract_cost_supp)[i] << "\n";
	}

	for (int i = 0; i < i_num_of_factories; i++) {
		cout << "uf[" << i << "]: " << (*pc_contract_cost_fact)[i] << "\n";
	}

	for (int i = 0; i < i_num_of_warehouses; i++) {
		cout << "um[" << i << "]: " << (*pc_contract_cost_ware)[i] << "\n";
	}

	for (int i = 0; i < i_num_of_shops; i++) {
		cout << "p[" << i << "]: " << (*pc_income)[i] << "\n";
	}

	/*
	for (int i = 0; i < 2 * i_num_of_suppliers; i += 2) {
		for (int j = 0; j < i_num_of_factories; j++) {
			cout << "xdminmax[" << i << ", " << j << "]: " << ppd_xdminmax[i][j] << "\n";
			cout << "xdminmax[" << i + 1 << ", " << j << "]: " << ppd_xdminmax[i + 1][j] << "\n";
		}
	}
	for (int i = 0; i < 2 * i_num_of_factories; i += 2) {
		for (int j = 0; j < i_num_of_warehouses; j++) {
			cout << "xfminmax[" << i << ", " << j << "]: " << ppd_xfminmax[i][j] << "\n";
			cout << "xfminmax[" << i + 1 << ", " << j << "]: " << ppd_xfminmax[i + 1][j] << "\n";
		}
	}
	for (int i = 0; i < 2 * i_num_of_warehouses; i += 2) {
		for (int j = 0; j < i_num_of_shops; j++) {
			cout << "xmminmax[" << i << ", " << j << "]: " << ppd_xmminmax[i][j] << "\n";
			cout << "xmminmax[" << i + 1 << ", " << j << "]: " << ppd_xmminmax[i + 1][j] << "\n";
		}
	}
	*/
}

void CMscnProblem::vPrintSolution(double * pdSolution) {
	int i_counter = 0;
	cout << "D " << pdSolution[i_counter++];
	cout << "\nF " << pdSolution[i_counter++];
	cout << "\nM " << pdSolution[i_counter++];
	cout << "\nS " << pdSolution[i_counter++];

	cout << "\nxd";
	for (int i = 0; i < i_num_of_suppliers; i++) {
		cout << "\nDostawca " << i << " -> Fabryki" << endl;
		for (int j = 0; j < i_num_of_factories; j++) {
			cout << pdSolution[i_counter++] << "    ";
		}
	}

	cout << "\nxf";
	for (int i = 0; i < i_num_of_factories; i++) {
		cout << "\nFabryka " << i << " -> Magazyny" << endl;
		for (int j = 0; j < i_num_of_warehouses; j++) {
			cout << pdSolution[i_counter++] << "    ";
		}
	}

	cout << "\nxm";
	for (int i = 0; i < i_num_of_warehouses; i++) {
		cout << "\nMagazyn " << i << " -> Sklepy" << endl;
		for (int j = 0; j < i_num_of_shops; j++) {
			cout << pdSolution[i_counter++] << "    ";
		}
	}
};