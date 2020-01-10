#include "pch.h"
#include "CDiffEvol.h"


CDiffEvol::CDiffEvol(CMscnProblem *pcProblem) {
	pc_problem = pcProblem;
}


CDiffEvol::~CDiffEvol() {
}

bool CDiffEvol::b_check_stop_condition(int iCounter) {
	return iCounter > NUMBER_OF_ITERATIONS;
}

double * CDiffEvol::pdFindBestSolution(int iSeed) {
	CRandom c_gen(iSeed);
	int i_genotype_size = pc_problem->iGetD()*pc_problem->iGetF() +
		pc_problem->iGetF()*pc_problem->iGetM() +
		pc_problem->iGetM()*pc_problem->iGetS();

	vector <double*> v_population = vector <double*>();// czemu wektor? czy musi byc operator przypisania?
//	vector <CIndividual*> v_population = vector <CIndividual>();

	for (int i = 0; i < POPULATION_SIZE; i++) {
		//		v_population[i] = RANDOM;
	}
//	while (!bCheckStopCondition()) {
		for (int i = 0; i < POPULATION_SIZE; i++) {
		//	CIndividual* pd_base_ind = &v_population[c_gen.i_random(0, POPULATION_SIZE)];	// zmien nazwy
		//	CIndividual* pd_add_ind0 = &v_population[c_gen.i_random(0, POPULATION_SIZE)];
		//	CIndividual* pd_add_ind1 = &v_population[c_gen.i_random(0, POPULATION_SIZE)];
			// pomysl, jak sprawic, by rozwiazania byly zawsze poprawne
		//	CIndividual* pd_ind_new = new CIndividual; // konstruktor napisac i madrze wypelnic      //[i_genotype_size]; // dealokacja
		//	if (1){//individualsAreDifferent(ind, baseInd, addInd0, addInd1)) {
			//	for (int i_gene_offset = 0; i_gene_offset << i_genotype_size; i_gene_offset++) {
			//		if (c_gen.d_random(0, 1) < CROSS_PROBABILITY) {
			//			pd_ind_new[i_gene_offset] = pd_base_ind[i_gene_offset] +
			//				DIFF_WEIGHT * (pd_add_ind0[i_gene_offset] - pd_add_ind1[i_gene_offset]);
			//		}
			//		else {
				//		pd_ind_new[i_gene_offset] = v_population[i][i_gene_offset];
			//		}
				}
			//	if (pc_problem->dGetQuality(pd_ind_new) >= dGetQuality(v_population[i])) {	// lub getfitnessy
				//	delete v_population[i];
				//	v_population[i] = pd_ind_new;
			//	}
		//	}
	//	}
	return nullptr;
	}