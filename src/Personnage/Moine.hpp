#ifndef MOINE_HPP
#define MOINE_HPP
#include "Personnage.hpp"

using namespace std;

class Moine : public Personnage {
    friend class Personnage;
    private :
        Moine();
    public :
        Moine(const Moine &) = delete;
        virtual ~Moine(){}
};


#endif /*MOINE_HPP*/