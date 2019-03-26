#include <iostream>
#include "List.hpp"

using namespace std;

int main(){
    List *L = new List();
    int N, K;
    cin>>N>>K;
    int i;
    //inserindo
    for(i = 0; i <= N; i++){
        L->insert(i);
    }
    L->print();
    cout<<L->size<<endl;
    
    //removendo os k primeiros
    for(i = 0; i < K; i++){
        if(i > N+1){
            break;
        }
        int x = L->removeFirst();
    }
    L->print();
    cout<<L->size<<endl;
    
    //removendo os pares
    for(i = ((N - K) + 1); i >= 0; i--){
        if(i%2 == 0){
            L->remove(i);
        }
    }
    L->print();
    L->clearList();    
    delete L;
	return 0;
}