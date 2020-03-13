#include "CArray.h"


CArray::CArray(int iSize){
	i_size = iSize;
	pd_array = new double [iSize];
}

CArray::~CArray() {
	delete[] pd_array;
}

bool CArray::bSetValInArray(int iIndex, double dVal) {
	if (iIndex < 0 || iIndex >= i_size) {
		return false;
	}
	pd_array[iIndex] = dVal;
	return true;
}

bool CArray::bReadValFromFile(FILE *pfFile){
	double d_num;
	char c_val[15];
	for (int i = 0; i < i_size; i++) {
		fscanf(pfFile, "%[^0-9] %lf", c_val, &d_num);
		pd_array[i] = d_num;
	}
	return true;
}

void CArray::vFillRandomly(CRandom* pc_random, int iMin, int iMax) {
	for (int i = 0; i < i_size; i++) {
		pd_array[i] = pc_random->d_random(iMin, iMax);
	}
}