#pragma once
class CIndividual { //dodaj zmienna genotype_len
private:
	double * pd_genotype;
	int i_genotype_size;
	double d_fitness;

public:
	CIndividual() {};
	CIndividual(int iGenotypeSize);
	~CIndividual();

	void vSetFitness(double dFitness) {
		d_fitness = dFitness;
	}		

	void vSetGenotypeSize(int iGenotypeSize) {
		i_genotype_size = iGenotypeSize;
	}

	double dGetFitness() {
		return d_fitness;
	}

	double * pdGetGenotype() {
		return pd_genotype;
	}	

	void vSetGenotype(double* pdGenotype) {
		pd_genotype = pdGenotype;
	}

	double dGetGeneAtIndex(int iId) {
		return pd_genotype[iId];
	}

	void vSetGeneAtIndex(int iId, double dNewGene) {
		pd_genotype[iId] = dNewGene;
	};
};
