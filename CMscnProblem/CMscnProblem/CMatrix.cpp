#include "CMatrix.h"
#include <iostream>

CMatrix::CMatrix(const int iX, const int iY){
	i_x = iX;
	i_y = iY;
	ppd_matrix = new double*[iX];
	for (int i = 0; i < iX; i++) {
		ppd_matrix[i] = new double[iY];
	}
}


CMatrix::~CMatrix(){
	for (int i = 0; i < i_x; i++) {
		delete[] ppd_matrix[i];
	}
	delete[] ppd_matrix;
}

bool CMatrix::bSetValInMatrix(int iRow, int iColumn, double dVal) {
	if (iRow < 0 || iRow >= i_x || iColumn < 0 || iColumn >= i_y) {
		return false;
	}
	ppd_matrix[iRow][iColumn] = dVal;
	return true;
}

bool CMatrix::bReadValFromFile(FILE* pfFile) {
	double d_num;
	char c_val[15];
	for (int i = 0; i < i_x; i++) {
		for (int j = 0; j < i_y; j++) {
			fscanf(pfFile, "%[^0-9] %lf", c_val, &d_num);
			ppd_matrix[i][j] = d_num;// .bSetValInMatrix(i, j, d_num);
		}
	}
	return true;
}

void CMatrix::vFillRandomly(CRandom *pcRandom, int iMin, int iMax) {
	for (int i = 0; i < i_x; i++) {
		for (int j = 0; j < i_y; j++) {
			ppd_matrix[i][j] = pcRandom->d_random(iMin, iMax);
		}
	}
}