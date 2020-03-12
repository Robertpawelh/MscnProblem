#pragma once
#include "CRandom.h"
#include <cstdio>

class CMatrix {
private:
	int i_x;
	int i_y;
	double ** ppd_matrix;
public:
	CMatrix() {};
	CMatrix(const int iX, const int iY);
	~CMatrix();

	double operator()(const int iX, const int iY){
		return ppd_matrix[iX][iY];
	} 
	/*
	double dGetX() {
		return i_x;
	}

	double dGetY() {
		return i_y;
	}
	*/
	bool bSetValInMatrix(int iRow, int iColumn, double dVal);

	bool bReadValFromFile(FILE* pfFile);

	void vFillRandomly(CRandom *pcRandom, int iMin, int iMax);
};

