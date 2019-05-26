#include <iostream>
#include "Classes.hpp"

using namespace std;

int main()
{
    ClasseBase base;
    base.set_public(1); 
    base.set_private(2); 
    base.set_protected(3); 
 
    ClassePublica pub;
    pub.set_public_public_base(1); 
    pub.set_protected_public_base(3); 
    
    ClassePrivada pri;
    pri.set_public_private_base(1); 
    pri.set_protected_private_base(3); 
    
    OverloadPrivada over;
    over.set_public(1); 
    over.set_private(2); 
    over.set_protected(3);
    
    A2 a2;
    a2.set_public_base_a2(1); 
    a2.set_protected_base_a2(3);
    a2.set_public2(1);
    a2.set_private2(2);
    a2.set_protected2(3);
    
    A3 a3;
    a3.set_public_a3_a2(1);
    a3.set_protected_a3_a2(3);
    a3.set_public3(1);
    a3.set_private3(2);
    a3.set_protected3(3);
    
    cout << base.get_public() << endl; 
    cout << base.get_private() << endl; 
    cout << base.get_protected() << endl; 
 
    cout << pub.get_public_public_base() << endl; 
    cout << "Inacessivel"<< endl;
    cout << pub.get_protected_public_base() << endl;

    cout << pri.get_public_private_base() << endl; 
    cout << "Inacessivel"<< endl;
    cout << pri.get_protected_private_base() << endl; 
    
    cout << over.get_public() << endl; 
    cout << over.get_private() << endl; 
    cout << over.get_protected() << endl; 

    cout << a2.get_public_base_a2() << endl;
    cout << "Inacessivel"<< endl;
    cout << a2.get_protected_base_a2() << endl; 
    cout << a2.get_public2() << endl;
    cout << a2.get_private2() << endl;
    cout << a2.get_protected2() << endl;

    cout << "Inacessivel"<< endl;
    cout << "Inacessivel"<< endl; 
    cout << "Inacessivel"<< endl;
    cout << a3.get_public_a3_a2() << endl;
    cout << "Inacessivel"<< endl;
    cout << a3.get_protected_a3_a2() << endl;
    cout << a3.get_public3() << endl;
    cout << a3.get_private3() << endl;
    cout << a3.get_protected3() << endl;
    
}
