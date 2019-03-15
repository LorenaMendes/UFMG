#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>

using namespace std;

int main(){
    string fname;
    cin >> fname;
    
    ifstream infile; 
    infile.open(fname);
    
    string line;
    vector<int> even;
    vector<int> odd;

    int val;

    while(infile>>val){
        if(val % 2) {
            odd.push_back(val);
        }
        else {
            even.push_back(val);
        }
    }

    vector<int>::iterator ptr;
    for(ptr = even.begin(); ptr != even.end(); ptr++){
        cout << *ptr << " ";
    }
    
    cout << endl;

    vector<int>::iterator ptr2;
    for(ptr2 = odd.begin(); ptr2 != odd.end(); ptr2++){
        cout << *ptr2 << " ";
    }

    infile.close();

}

/* Lê um arquivo até o final e o imprime
    while(!infile.eof()){
        getline(infile, line);
        cout << line << endl;
    }
*/    