#ifndef AMAZONE_HPP
#define AMAZONE_HPP
#include "Personnage.hpp"

using namespace std;

class Amazone : public Personnage {
    friend class Personnage;
    private :
        Amazone();
    public :
        Amazone(const Amazone&) = delete;
        virtual ~Amazone(){}
};



#endif /*AMAZONE_HPP*/