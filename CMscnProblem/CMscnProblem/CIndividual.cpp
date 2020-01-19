#include "CIndividual.h"


CIndividual::CIndividual(int iGenotypeSize){
	i_genotype_size = iGenotypeSize;
	pd_genotype = new double[iGenotypeSize];
}

CIndividual::~CIndividual(){
	delete [] pd_genotype;
}
