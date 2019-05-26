#include "f1calc.hpp"
using namespace std;

tuple<int,int,int,int,int> F1CALC::processaEntradas(string sTP,string sTN,string sFP,string sFN,string sTotal){
	tuple<int,int,int,int,int> tup = make_tuple(8,8,8,8,8);
	// tup = make_tuple(int(sTP));
	cout << stoi(sTP) << endl;
	return tup;
}

tuple<float,float> F1CALC::calculaPresRecall(int TP,int TN,int FP,int FN,int Total){

}

float F1CALC::calculaF1(float p, float r)
{}