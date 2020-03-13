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
	double * sumToS = new double[pcProblem->iGetNumOfSuppliers()];
	double * sumToF = new double[pcProblem->iGetNumOfFactories()];
	double * sumToM = new double[pcProblem->iGetNumOfWarehouses()];
	for (int i = 0; i < pcProblem->iGetNumOfSuppliers(); i++) {
		sumToS[i] = pcProblem->dGetMax(NUMBER_OF_PRODUCTION_LEVELS + i, b_is_success);
	}
	for (int i = 0; i < pcProblem->iGetNumOfFactories(); i++) {
		sumToF[i] = 0;
	}
	for (int i = 0; i < pcProblem->iGetNumOfWarehouses(); i++) {
		sumToM[i] = 0;
	}

	int i_solution_data_len = pcProblem->iGetSolutionLen();

	int max_len = pcProblem->iGetNumOfSuppliers() + pcProblem->iGetNumOfFactories() + pcProblem->iGetNumOfShops() + pcProblem->iGetNumOfWarehouses() + NUMBER_OF_PRODUCTION_LEVELS;
	double * pd_max_cap = new double[max_len];
	for (int i = 0; i < max_len; i++) {
		pd_max_cap[i] = pcProblem->dGetMax(i, b_is_success);
	}
	double * pd_solution = new double[i_solution_data_len];
	int i_counter = 0;

	pd_solution[i_counter++] = pcProblem->iGetNumOfSuppliers();
	pd_solution[i_counter++] = pcProblem->iGetNumOfFactories();
	pd_solution[i_counter++] = pcProblem->iGetNumOfWarehouses();
	pd_solution[i_counter++] = pcProblem->iGetNumOfShops();

	for (int i = 0; i < pcProblem->iGetNumOfSuppliers(); i++) {
		for (int j = 0; j < pcProblem->iGetNumOfFactories(); j++) {
			double d_max_val = min(pd_max_cap[i_counter + i], sumToS[i]);
			pd_solution[i * pcProblem->iGetNumOfFactories() + j + i_counter] = cGenerator.d_random(0, d_max_val);
			sumToF[j] += pd_solution[i * pcProblem->iGetNumOfFactories() + j + i_counter];
			sumToS[i] -= pd_solution[i * pcProblem->iGetNumOfFactories() + j + i_counter];
			pd_max_cap[i_counter + i] -= pd_solution[i * pcProblem->iGetNumOfFactories() + j + i_counter];
		}
	};	
	i_counter += pcProblem->iGetNumOfSuppliers() * pcProblem->iGetNumOfFactories();


	for (int i = 0; i < pcProblem->iGetNumOfFactories(); i++) {
		for (int j = 0; j < pcProblem->iGetNumOfWarehouses(); j++) {
			double d_max_val = min(pd_max_cap[i + pcProblem->iGetNumOfSuppliers() + NUMBER_OF_PRODUCTION_LEVELS],
				sumToF[i]);
			pd_solution[i * pcProblem->iGetNumOfWarehouses() + j + i_counter] = cGenerator.d_random(0, d_max_val);

			sumToM[j] += pd_solution[i * pcProblem->iGetNumOfWarehouses() + j + i_counter];
			sumToF[i] -= pd_solution[i * pcProblem->iGetNumOfWarehouses() + j + i_counter];
			pd_max_cap[i + pcProblem->iGetNumOfSuppliers() + NUMBER_OF_PRODUCTION_LEVELS] -= 
				pd_solution[i * pcProblem->iGetNumOfWarehouses() + j + i_counter];
		}
	}
	i_counter += pcProblem->iGetNumOfFactories() * pcProblem->iGetNumOfWarehouses();


	for (int i = 0; i < pcProblem->iGetNumOfWarehouses(); i++) {
		for (int j = 0; j < pcProblem->iGetNumOfShops(); j++) {
			double d_max_val = min(pd_max_cap[i + pcProblem->iGetNumOfSuppliers() + pcProblem->iGetNumOfFactories()  + NUMBER_OF_PRODUCTION_LEVELS],
				sumToM[i]);
			d_max_val = min(d_max_val, pd_max_cap[j + pcProblem->iGetNumOfWarehouses() + pcProblem->iGetNumOfSuppliers() + pcProblem->iGetNumOfFactories() + NUMBER_OF_PRODUCTION_LEVELS]);
			pd_solution[i * pcProblem->iGetNumOfShops() + j + i_counter] = cGenerator.d_random(0, d_max_val);

			sumToM[i] -= pd_solution[i * pcProblem->iGetNumOfShops() + j + i_counter];

			pd_max_cap[i + pcProblem->iGetNumOfSuppliers() + pcProblem->iGetNumOfFactories() + NUMBER_OF_PRODUCTION_LEVELS] -=
				pd_solution[i * pcProblem->iGetNumOfShops() + j + i_counter];

			pd_max_cap[j + pcProblem->iGetNumOfWarehouses() + pcProblem->iGetNumOfSuppliers() + pcProblem->iGetNumOfFactories() + NUMBER_OF_PRODUCTION_LEVELS] -=
				pd_solution[i * pcProblem->iGetNumOfShops() + j + i_counter];

		}
	}

	return pd_solution;
}
