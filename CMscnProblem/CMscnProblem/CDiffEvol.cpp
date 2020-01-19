#include "CDiffEvol.h"


CDiffEvol::CDiffEvol(CProblem *pcProblem) {
	pc_problem = pcProblem;
	i_iterations_counter = 0;

	i_genotype_size = pc_problem->iGetSolutionArrayLen();
}


CDiffEvol::~CDiffEvol() {
	delete [] pc_current_population;
}

void CDiffEvol::vInitialize(int iSeed) {
	CRandom c_generator(iSeed);
	bool b_is_success;
	string s_error_code;

	d_best_quality = INT_MIN;
	pc_current_population = new CIndividual[POPULATION_SIZE];
	i_current_pop_size = POPULATION_SIZE;

	for (int i = 0; i < POPULATION_SIZE; i++) {
		pc_current_population[i].vSetGenotype(CRandomSolutionGenerator::pd_random_solution(c_generator, pc_problem, STARTING_VALUES_DIVIDER)); //zmien na c_rand_gen
		pc_current_population[i].vSetGenotypeSize(i_genotype_size);
		pc_current_population[i].vSetFitness((*pc_problem).dGetQuality(pc_current_population[i].pdGetGenotype(), b_is_success));
	};

	pd_current_best = new double[i_genotype_size];

//	if (pc_problem->bConstraintsSatisfied(pd_current_best, s_error_code)) {
//		d_best_quality = pc_problem->dGetQuality(pd_current_best, b_is_success);
//	}
}

bool CDiffEvol::bCheckStopCondition() {
	return i_iterations_counter < NUMBER_OF_ITERATIONS;
}

double * CDiffEvol::pdFindBestSolution(int iSeed) {
	vInitialize(iSeed);
	while (bCheckStopCondition()) {
		for (int i = 0; i < ITERATIONS_BEFORE_POPULATION_SIZE_CHANGE; i++) {
			vRunIteration();
		}
		v_change_population_size(POPULATION_SIZE / 2);

		for (int i = 0; i < ITERATIONS_BEFORE_POPULATION_SIZE_CHANGE; i++) {
			vRunIteration();
		}
		v_change_population_size(POPULATION_SIZE);
	}
	return pd_current_best;
}

bool CDiffEvol::bAreIndividualsDifferent(CIndividual* cInd1, CIndividual* cInd2, CIndividual* cInd3, CIndividual* cInd4) {
	bool b_are_12_the_same = true;
	bool b_are_23_the_same = true;
	bool b_are_34_the_same = true;
	bool b_are_13_the_same = true;
	bool b_are_14_the_same = true;
	bool b_are_24_the_same = true;
	int i = INDEX_OF_FIRST_DATA_IN_SOLUTION;
	while (b_are_12_the_same || b_are_13_the_same || 
		   b_are_14_the_same || b_are_23_the_same || 
		   b_are_24_the_same || b_are_34_the_same || 
		   i < i_genotype_size) {
		if (b_are_12_the_same) {
			b_are_12_the_same = (cInd1->dGetGeneAtIndex(i) == cInd2->dGetGeneAtIndex(i));
		}
		if (b_are_23_the_same) {
			b_are_23_the_same = (cInd2->dGetGeneAtIndex(i) == cInd3->dGetGeneAtIndex(i));
		}
		if (b_are_34_the_same) {
			b_are_34_the_same = (cInd3->dGetGeneAtIndex(i) == cInd4->dGetGeneAtIndex(i));
		}
		if (b_are_13_the_same) {
			b_are_13_the_same = (cInd1->dGetGeneAtIndex(i) == cInd3->dGetGeneAtIndex(i));
		}
		if (b_are_14_the_same) {
			b_are_14_the_same = (cInd1->dGetGeneAtIndex(i) == cInd4->dGetGeneAtIndex(i));
		}
		if (b_are_24_the_same) {
			b_are_24_the_same = (cInd2->dGetGeneAtIndex(i) == cInd4->dGetGeneAtIndex(i));
		}
		i++;
	}
	if (b_are_12_the_same || b_are_13_the_same || b_are_14_the_same || b_are_23_the_same || b_are_24_the_same || b_are_34_the_same) {
	//	cout << "XD";
		return false;
	}
	else {
		return true;
	}
}

void CDiffEvol::v_find_3_different_individuals(int iIndId, CIndividual** ppcInd1, CIndividual** ppcInd2, CIndividual** ppcInd3) {
	int id_ind_base;
	int id_ind_add1;
	int id_ind_add2;

	do {
		id_ind_base = c_rand_gen.i_random(0, i_current_pop_size - 1);
	} while (id_ind_base == iIndId);
	do {
		id_ind_add1 = c_rand_gen.i_random(0, i_current_pop_size - 1);
	} while (id_ind_add1 == iIndId || id_ind_add1 == id_ind_base);
	do {
		id_ind_add2 = c_rand_gen.i_random(0, i_current_pop_size - 1);
	} while (id_ind_add2 == iIndId || id_ind_add2 == id_ind_base || id_ind_add2 == id_ind_add1);

	*ppcInd1 = &pc_current_population[id_ind_base];
	*ppcInd2 = &pc_current_population[id_ind_add1];
	*ppcInd3 = &pc_current_population[id_ind_add2];
}

void CDiffEvol::v_crossover(CIndividual* pcNewInd, CIndividual** ppcIndBase, CIndividual** ppcInd1, CIndividual** ppcInd2, int iGeneOffset) {
	double dNewGene = (**ppcIndBase).dGetGeneAtIndex(iGeneOffset) +
		DIFF_WEIGHT *
		((**ppcInd1).dGetGeneAtIndex(iGeneOffset) - (**ppcInd2).dGetGeneAtIndex(iGeneOffset));

	bool b_is_success;
	double d_min_val = pc_problem->dGetMin(iGeneOffset, b_is_success);
	double d_max_val = pc_problem->dGetMax(iGeneOffset, b_is_success);

	if (dNewGene > d_min_val && dNewGene < d_min_val) {
		(*pcNewInd).vSetGeneAtIndex(iGeneOffset, dNewGene);
	}
	else {
		(*pcNewInd).vSetGeneAtIndex(iGeneOffset, (**ppcIndBase).dGetGeneAtIndex(iGeneOffset));
		//naprawa powinna byc mocniejsza
	}
}

void CDiffEvol::v_set_new_quality(CIndividual* pcNewInd, int iParentId) {
	bool b_is_success;
	(*pcNewInd).vSetFitness(pc_problem->dGetQuality((*pcNewInd).pdGetGenotype(), b_is_success));
	i_iterations_counter++;
}

void CDiffEvol::v_replace_ind_if_child_is_better(CIndividual* pcNewInd, int iParentId, bool &bWasFoundTheBest) {
	string s_error_code;
	if (pc_problem->bConstraintsSatisfied( (*pcNewInd).pdGetGenotype(), s_error_code) ) {
		
		if ((*pcNewInd).dGetFitness() >= pc_current_population[iParentId].dGetFitness() ||
			!pc_problem->bConstraintsSatisfied(pd_current_best, s_error_code)) { 

			pc_current_population[iParentId] = *pcNewInd;

			if ((*pcNewInd).dGetFitness() > d_best_quality) {
				for (int i = 0; i < i_genotype_size; i++) {
					pd_current_best[i] = pc_current_population[iParentId].dGetGeneAtIndex(i);
				}

				d_best_quality = (*pcNewInd).dGetFitness();
				cout << d_best_quality << endl; // wyswietla kolejno znalezione najlepsze rozwiazania.
				bWasFoundTheBest = true;	// to wywal
			}
			else {
				bWasFoundTheBest = false;	// to wywal
			}
		}
		else {
			delete pcNewInd;
		}
	}
}

void CDiffEvol::vRunIteration() {
	bool b_was_found_the_best;
	for (int i = 0; i < i_current_pop_size; i++) {
		CIndividual* pc_ind_base = nullptr;
		CIndividual* pc_ind_add1 = nullptr;
		CIndividual*  pc_ind_add2 = nullptr;
		v_find_3_different_individuals(i, &pc_ind_base, &pc_ind_add1, &pc_ind_add2);

		if (bAreIndividualsDifferent(&pc_current_population[i], pc_ind_base, pc_ind_add1, pc_ind_add2)) {
			CIndividual* c_element_new = new CIndividual(i_genotype_size);
		//	c_element_new->vSetGeneAtIndex(0, pc_problem->iGetD());
		//	c_element_new->vSetGeneAtIndex(1, pc_problem->iGetF());
		//	c_element_new->vSetGeneAtIndex(2, pc_problem->iGetM());
		//	c_element_new->vSetGeneAtIndex(3, pc_problem->iGetS());
			for (int i_gene_offset = 0; i_gene_offset < i_genotype_size; i_gene_offset++) { // i_gen_offset byl INDEXOFFIRSTDATA
				if (c_rand_gen.d_random(0, 1) < CROSS_PROBABILITY) {
					v_crossover(c_element_new, &pc_ind_base, &pc_ind_add1, &pc_ind_add2, i_gene_offset);
				}
				else {
					c_element_new->vSetGeneAtIndex(i_gene_offset, pc_current_population[i].dGetGeneAtIndex(i_gene_offset));
				}
			}

			v_set_new_quality(c_element_new, i); 
			v_replace_ind_if_child_is_better(c_element_new, i, b_was_found_the_best);

		}
		else {
			i_iterations_counter++;
		}
	}
}

void CDiffEvol::v_change_population_size(int iNewSize) {
	CIndividual * pc_new_population = new CIndividual[iNewSize];
	if (iNewSize == i_current_pop_size) {
		return;
	}

	if (iNewSize < i_current_pop_size) { // zmniejszamy
		for (int i = 0; i < iNewSize; i++) {
			pc_new_population[i] = pc_current_population[i];
			//pc_new_population[i] = CIndividual(pc_current_population[i]);
		}
	}
	else {		// zwiekszamy
		for (int i = 0; i < i_current_pop_size; i++) {
			pc_new_population[i] = pc_current_population[i];
		}
		for (int i = i_current_pop_size; i < iNewSize; i++) {
		//	RAND GEN
				pc_new_population[i].vSetGenotype(CRandomSolutionGenerator::pd_random_solution(c_rand_gen, pc_problem, STARTING_VALUES_DIVIDER));
		}

	}
	i_current_pop_size = iNewSize;

	pc_current_population = pc_new_population;
};

