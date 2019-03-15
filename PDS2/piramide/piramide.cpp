#include <iostream>

using namespace std;

void imprime(int x){
    for (int i = 0; i < x; ++i) cout << "*";
	cout << endl;
}

int main(){
    int x;
    cin >> x;
    for (int i = 1; i <= x; ++i) imprime(i);
	for (int i = x-1; i > 0; --i) imprime(i);
	return 0;
}