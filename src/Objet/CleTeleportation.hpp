#ifndef CLETELEPORTATION_HPP
#define CLETELEPORTATION_HPP
#include <iostream>
#include "Objet.hpp"

using namespace std;

class CleTeleportation : public Objet {
    private :
        static bool exist;
        CleTeleportation();
    public :
        // création & dtor
        CleTeleportation(const CleTeleportation &) = delete;
        static CleTeleportation * forgeCleTeleportation();
        virtual ~CleTeleportation();
        void teleportToIa();
        // methodes possibles par les autres classes
        virtual int getStat();
};

#endif /*CLETELEPORTATION_HPP*/