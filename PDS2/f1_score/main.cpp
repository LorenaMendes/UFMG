#include "utils.hpp"
#include "f1calc.hpp"

#include <string>
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
	string sTP, sTN, sFP, sFN, sTotal;
	int TP, TN, FP, FN, Total;
	float precision, recall, f1;
	
	cin >> sTP >> sTN >> sFP >> sFN >> sTotal;
	
	tie(TP, TN, FP, FN, Total) = F1CALC::processaEntradas(sTP, sTN, sFP, sFN, sTotal);

	tie(precision,recall) = F1CALC::calculaPresRecall(TP, TN, FP, FN, Total);
	
	f1 = F1CALC::calculaF1(precision, recall);
	
	cout << "F1: " << f1 << endl;
}