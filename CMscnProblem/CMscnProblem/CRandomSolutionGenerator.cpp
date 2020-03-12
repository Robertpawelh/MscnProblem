#include "CRandomSolutionGenerator.h"

double* CRandomSolutionGenerator::pd_random_solution(CRandom &cGenerator, CMscnProblem * pcProblem) {//CProblem* pcProblem) {
	/*

	bool b_is_success;
	double * pd_maxvalues = new double [i_solution_data_len];
	// co z pierwszymi 4?
	for (int i = 0; i < i_solution_data_len; i++) {
		pd_maxvalues[i] = pcProblem->dGetMax(i, b_is_success);
	}

	for (int i = 0; i < i_solution_data_len; i++) {
		double d_min_val = 0;//pcProblem->dGetMin(i, b_is_success);
		double d_max_val = pd_maxvalues[i];//10;//pcProblem->dGetMax(i, b_is_success);
		updateMaxes();
		pd_solution[i] = cGenerator.d_random(d_min_val, d_max_val);
	}
	*/	
	bool b_is_success;
	double * sumToF = new double[pcProblem->iGetNumOfFactories()];
	double * sumToM = new double[pcProblem->iGetNumOfWarehouses()];
	for (int i = 0; i < pcProblem->iGetNumOfFactories(); i++) {
		sumToF[i] = 0;
	}
	for (int i = 0; i < pcProblem->iGetNumOfWarehouses(); i++) {
		sumToM[i] = 0;
	}

	int i_solution_data_len = pcProblem->iGetSolutionLen();
	double * pd_solution = new double[i_solution_data_len];
	int i_counter = 0;

	int first_loop_size = pcProblem->iGetNumOfSuppliers() * pcProblem->iGetNumOfFactories();
	for (int i = 0; i < first_loop_size; i++) {
		double d_max_val = pcProblem->dGetMax(i % pcProblem->iGetNumOfFactories(), b_is_success);
		pd_solution[i] = cGenerator.d_random(0, d_max_val);
		sumToF[i % (pcProblem->iGetNumOfSuppliers())] += pd_solution[i];
	};
	i_counter += first_loop_size;
	int second_loop_size = pcProblem->iGetNumOfFactories() * pcProblem->iGetNumOfWarehouses();
	for (int i = 0; i < second_loop_size; i++) {
		double d_max_val = max( (pcProblem->dGetMax(i % pcProblem->iGetNumOfWarehouses(), b_is_success)), 
							    (sumToF[i % pcProblem->iGetNumOfFactories()]));

		pd_solution[i_counter] = cGenerator.d_random(0, d_max_val);
		sumToM[i_counter % pcProblem->iGetNumOfFactories()] += pd_solution[i];
	}

	i_counter += second_loop_size;
	int third_loop_size = pcProblem->iGetNumOfWarehouses() * pcProblem->iGetNumOfShops();
	for (int i = 0; i < third_loop_size; i++) {
		double d_max_val = max( (pcProblem->dGetMax(i % pcProblem->iGetNumOfShops(), b_is_success)), 
							    (sumToM[i % pcProblem->iGetNumOfWarehouses()]));
		pd_solution[i_counter] = cGenerator.d_random(0, d_max_val);
	}

	return pd_solution;
}
