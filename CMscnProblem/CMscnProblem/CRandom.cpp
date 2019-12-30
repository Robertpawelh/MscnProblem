#include "pch.h"
#include "CRandom.h"


CRandom::CRandom(){
	gen = mt19937(0);
}

CRandom::CRandom(int iInstanceSeed) {
	gen = mt19937 (iInstanceSeed);
}

CRandom::~CRandom(){
}
