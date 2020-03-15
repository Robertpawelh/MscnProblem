#include "CMscnProblem.h"

CMscnProblem::CMscnProblem() {
	i_num_of_suppliers = BASIC_NUM_OFF_SUPPLIERS;
	i_num_of_factories = BASIC_NUM_OFF_FACTORIES;
	i_num_of_warehouses = BASIC_NUM_OFF_WAREHOUSES;
	i_num_of_shops = BASIC_NUM_OFF_SHOPS;

	pc_max_cap_of_supp = new CArray(i_num_of_suppliers);
	pc_max_cap_of_fact = new CArray(i_num_of_factories);
	pc_max_cap_of_ware = new CArray(i_num_of_warehouses);
	pc_max_cap_of_shop = new CArray(i_num_of_shops);

	pc_transp_cost_supp_to_fact = new CMatrix(i_num_of_suppliers, i_num_of_factories);
	pc_transp_cost_fact_to_ware = new CMatrix(i_num_of_factories, i_num_of_warehouses);
	pc_transp_cost_ware_to_shop = new CMatrix(i_num_of_warehouses, i_num_of_shops);

	pc_contract_cost_supp = new CArray(i_num_of_suppliers);
	pc_contract_cost_fact = new CArray(i_num_of_factories);
	pc_contract_cost_ware = new CArray(i_num_of_warehouses);

	pc_income = new CArray(i_num_of_shops);
}

CMscnProblem::~CMscnProblem() {
	delete pc_max_cap_of_supp;
	delete pc_max_cap_of_fact;
	delete pc_max_cap_of_ware;
	delete pc_max_cap_of_shop;

	delete pc_transp_cost_supp_to_fact;
	delete pc_transp_cost_fact_to_ware;
	delete pc_transp_cost_ware_to_shop;


	delete pc_contract_cost_supp;
	delete pc_contract_cost_fact;
	delete pc_contract_cost_ware;

	delete pc_income;
}

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
		return (*pc_max_cap_of_fact)[iId];
	}

	if (iId >= i_num_of_warehouses) {
		iId -= i_num_of_warehouses;
	}
	else {
		bIsSuccess = true;
		return (*pc_max_cap_of_ware)[iId];
	}

	if (iId >= i_num_of_shops) {
		bIsSuccess = false;
		return -1;
	}
	else {
		bIsSuccess = true;
		return (*pc_max_cap_of_shop)[iId];
	}

}

double CMscnProblem::d_calc_transp_cost_for_matrix(int iId, double * pdSolution, CMatrix *pdCostMatrix, int iX, int iY) { //upewnij sie czy nie kopiuje
	double d_transport_cost = 0;
	for (int i = 0; i < iX; i++) {
		for (int j = 0; j < iY; j++) {
			d_transport_cost += (*pdCostMatrix)(i, j) * pdSolution[iId++];
		}
	}
	return d_transport_cost;
}

double CMscnProblem::d_calc_transp_cost(double* pdSolution) { //sprawdz czy dobrze liczy
	double d_transport_cost = 0;
	int i_id_solution = NUMBER_OF_PRODUCTION_LEVELS;

	d_transport_cost += d_calc_transp_cost_for_matrix(i_id_solution, 
						pdSolution, pc_transp_cost_supp_to_fact, i_num_of_suppliers, i_num_of_factories);
	i_id_solution += i_num_of_suppliers * i_num_of_factories;
	d_transport_cost += d_calc_transp_cost_for_matrix(i_id_solution,
						pdSolution, pc_transp_cost_fact_to_ware, i_num_of_factories, i_num_of_warehouses);
	i_id_solution += i_num_of_factories * i_num_of_warehouses;
	d_transport_cost += d_calc_transp_cost_for_matrix(i_id_solution,
						pdSolution, pc_transp_cost_ware_to_shop, i_num_of_warehouses, i_num_of_shops);

	return d_transport_cost;
}

double CMscnProblem::d_calc_contract_cost_for_array(int iId, double * pdSolution, CArray *pcCostArray, int iX, int iY) {
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
	int i_id_solution = NUMBER_OF_PRODUCTION_LEVELS;

	d_contract_cost += d_calc_contract_cost_for_array(i_id_solution, pdSolution, pc_contract_cost_supp, i_num_of_suppliers, i_num_of_factories);
	i_id_solution += i_num_of_suppliers * i_num_of_factories;
	d_contract_cost += d_calc_contract_cost_for_array(i_id_solution, pdSolution, pc_contract_cost_fact, i_num_of_factories, i_num_of_warehouses);
	i_id_solution += i_num_of_factories * i_num_of_warehouses;
	d_contract_cost += d_calc_contract_cost_for_array(i_id_solution, pdSolution, pc_contract_cost_ware, i_num_of_warehouses, i_num_of_shops);

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
	string s_error_code = "";
		bIsSuccess = bConstraintsSatisfied (pdSolution, s_error_code);
	return d_calc_profit(pdSolution);
}


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
			sErrorCode = BIGGER_THAN_PRODUCED_ERROR;
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
			sErrorCode=BIGGER_THAN_PRODUCED_ERROR;
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
			sErrorCode=BIGGER_THAN_PRODUCED_ERROR;
			return false;
		}
		d_sum_warehouse_sends = 0;
	}

	d_sum_warehouse_sends = 0;
	i_counter = NUMBER_OF_PRODUCTION_LEVELS + i_num_of_suppliers * i_num_of_factories + i_num_of_factories * i_num_of_warehouses;

	for (int i = 0; i < i_num_of_shops; i++) {
		for (int j = 0; j < i_num_of_warehouses; j++) {
			d_sum_warehouse_sends += pdSolution[i_counter + i_num_of_warehouses * i + j]; //?
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
			fprintf(pf_file, "\n%lf", (*pc_transp_cost_supp_to_fact)(i, j));
		}
	}

	fprintf(pf_file, "%s", "\ncf");
	for (int i = 0; i < i_num_of_factories; i++) {
		for (int j = 0; j < i_num_of_warehouses; j++) {
			fprintf(pf_file, "\n%lf", (*pc_transp_cost_fact_to_ware)(i, j));
		}
	}

	fprintf(pf_file, "%s", "\ncm");
	for (int i = 0; i < i_num_of_warehouses; i++) {
		for (int j = 0; j < i_num_of_shops; j++) {
			fprintf(pf_file, "\n%lf", (*pc_transp_cost_ware_to_shop)(i, j));
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
			fprintf(pf_file, "\n%lf ", pdSolution[i_counter++]);	// odstepy
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

	pc_transp_cost_supp_to_fact->vFillRandomly(&c_random_gen, MIN_CD, MAX_CD);
	pc_transp_cost_fact_to_ware->vFillRandomly(&c_random_gen, MIN_CF, MAX_CF);
	pc_transp_cost_ware_to_shop->vFillRandomly(&c_random_gen, MIN_CM, MAX_CM);

	pc_contract_cost_supp->vFillRandomly(&c_random_gen, MIN_UD, MAX_CD);
	pc_contract_cost_fact->vFillRandomly(&c_random_gen, MIN_UF, MAX_CF);
	pc_contract_cost_ware->vFillRandomly(&c_random_gen, MIN_UM, MAX_CM);
	pc_income->vFillRandomly(&c_random_gen, MIN_P, MAX_P);
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
			cout << "cd[" << i << "][" << j << "]: " << (*pc_transp_cost_supp_to_fact)(i, j) << "\n";
		}
	}

	for (int i = 0; i < i_num_of_factories; i++) {
		for (int j = 0; j < i_num_of_warehouses; j++) {
			cout << "cf[" << i << "][" << j << "]: " << (*pc_transp_cost_fact_to_ware)(i, j) << "\n";
		}
	}

	for (int i = 0; i < i_num_of_warehouses; i++) {
		for (int j = 0; j < i_num_of_shops; j++) {
			cout << "cm[" << i << "][" << j << "]: " << (*pc_transp_cost_ware_to_shop)(i, j) << "\n";
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