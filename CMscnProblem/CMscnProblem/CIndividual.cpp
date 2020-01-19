#include "CIndividual.h"


CIndividual::CIndividual(int iGenotypeSize){
	i_genotype_size = iGenotypeSize;
	pd_genotype = new double[iGenotypeSize];
}

/*
CIndividual::CIndividual(CIndividual& cOther) {
	pd_genotype = new double[cOther.i_genotype_size];
	for (int i = 0; i < i_genotype_size; i++) {
		pd_genotype[i] = cOther.pd_genotype[i];
	}
};
*/

CIndividual::~CIndividual(){
	delete [] pd_genotype;
}
