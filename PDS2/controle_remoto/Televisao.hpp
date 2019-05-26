#ifndef TELEVISAO_H
#define TELEVISAO_H 

class Televisao
{
    private:
        unsigned int canal;
        unsigned int volume;
    	 
    public:

    	void setCanal(int c); 
        void setVolume(int v);    
		int getCanal();
        int getVolume();
        
        Televisao() {canal = 0; volume = 0;}
    
};

#endif