#pragma once
#include "CRandom.h"
#include <cstdio>
#include <iostream>

class CArray{
	int i_size;
	double * pd_array;
public:
	CArray() {};
	CArray(int iSize);
	~CArray();
	double operator[](int iRow) {
		return pd_array[iRow];
	}
	bool bSetValInArray(int iIndex, double dVal);
	bool bReadValFromFile(FILE* pfFile);
	void vFillRandomly(CRandom* pc_random, int iMin, int iMax);
	//void vPrintArray();
};

