#pragma once
class CIndividual{
private:
	double * pd_genotype;
public:
	CIndividual();
	~CIndividual();

	double dGetFitness() {
		return -111;
	}			// zaimplementowac
};

