#ifndef CONTROLE_H
#define CONTROLE_H

#include "Televisao.hpp"

class Controle
{
    private:
        Televisao *tv;    
    
    public:
        void setCanal(int c);
        void setVolume(int v); 

        void aumentaVolume();
        void diminuiVolume();
        
        void aumentaCanal();
        void diminuiCanal();

        Controle(Televisao *t);
};

#endif