#pragma once
#include "CRandomSolutionGenerator.h"
#include "CIndividual.h"
#include "COptimizer.h"

#include <iostream>

#define POPULATION_SIZE 70
#define CROSS_PROBABILITY 0.3
#define DIFF_WEIGHT 0.2
#define STARTING_VALUES_DIVIDER 1
#define ITERATIONS_BEFORE_POPULATION_SIZE_CHANGE 10

using namespace std;

class CDiffEvol : public COptimizer {
private:
	CIndividual * pc_current_population;
	int i_current_pop_size;
	CRandom c_rand_gen;
	double d_best_quality;
	int i_genotype_size;
//	int i_iterations_counter;

	void vInitialize();
//	bool bCheckStopCondition(); 
	bool bAreIndividualsDifferent(CIndividual* cInd1, CIndividual* cInd2, CIndividual* cInd3, CIndividual* cInd4);
	void v_find_3_different_individuals(int iIndId, CIndividual** ppcInd1, CIndividual** ppcInd2, CIndividual** ppcInd3);
	void v_crossover(CIndividual* pcNewInd, CIndividual** ppcIndBase, CIndividual** ppcInd1, CIndividual** ppcInd2, int iGeneOffset);
	void v_set_new_quality(CIndividual* pcNewInd, int iParentId);
	void v_replace_ind_if_child_is_better(CIndividual* pcNewInd, int iParentId);
	void vRunIteration();
	void v_change_population_size(int iNewSize);

public:
	CDiffEvol(CProblem * pcProblem, int iSeed);
	~CDiffEvol();

};

