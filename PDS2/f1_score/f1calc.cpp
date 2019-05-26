#include "f1calc.hpp"
#include <iomanip>
#include "utils.hpp"
using namespace std;

tuple<int,int,int,int,int> F1CALC::processaEntradas(string sTP,string sTN,string sFP,string sFN,string sTotal){
	for (int i = 0; i < (int)sTP.length(); ++i) ASSERT((int)sTP[i] > 47 && (int)sTP[i] < 58, "Input validation failed");
	for (int i = 0; i < (int)sTN.length(); ++i) ASSERT((int)sTN[i] > 47 && (int)sTN[i] < 58, "Input validation failed");
	for (int i = 0; i < (int)sFP.length(); ++i) ASSERT((int)sFP[i] > 47 && (int)sFP[i] < 58, "Input validation failed");
	for (int i = 0; i < (int)sFN.length(); ++i) ASSERT((int)sFN[i] > 47 && (int)sFN[i] < 58, "Input validation failed");
	for (int i = 0; i < (int)sTotal.length(); ++i) ASSERT((int)sTotal[i] > 47 && (int)sTotal[i] < 58, "Input validation failed");
	tuple<int,int,int,int,int> tup = make_tuple(stoi(sTP), stoi(sTN), stoi(sFP), stoi(sFN), stoi(sTotal));
	return tup;
}

tuple<float,float> F1CALC::calculaPresRecall(int TP,int TN,int FP,int FN,int Total){
	ASSERT(Total == TP+TN+FP+FN,"Pre-condition failed");
	ASSERT(TP + FP != 0,"Pre-condition failed");
	ASSERT(TP + FN != 0,"Pre-condition failed");
	
	float precision = float(TP) / (float(TP) + float(FP));
	float recall = float(TP) / (float(FN) + float(TP));
	
	// cout << fixed << setprecision(2) << endl;

	ASSERT(precision + recall != 0,"Post-condition failed");
	
	tuple<float,float> tup = make_tuple(precision, recall);
	return tup;
}

float F1CALC::calculaF1(float p, float r){
	return (2 * (p*r)) / (p+r);
}