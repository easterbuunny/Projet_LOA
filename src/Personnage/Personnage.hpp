#ifndef PERSONNAGE_HPP
#define PERSONNAGE_HPP

#include <string>
#include <vector>
#include <random>
#include <iostream>

#include "../Donjon/Piece.hpp"

using namespace std;

class Objet;

class Personnage{
    protected :
        // status du joueur
        const string name;
        int healthPoint;
        int habilityPoint;
        int defencePoint;
        int attackPoint;

        // données relatives au jeu
        vector<Objet *> sac;

        // ctor
        Personnage(string, int, int, int, int);

    public :
        // ctor par copie & dtor
        Personnage(const Personnage &) = delete;
        virtual ~Personnage(){}

        // création de personnage
        static Personnage * forgePersonnage(int i);

        // getter sur les caractéristique du personnage
        const void showStats() const;
        const string getName() const;
        const int getHealthPoint() const;
        const int getHabiltyPoint() const;
        const int getDefencePoint() const;
        const int getAttackPoint() const;

        // méthodes appelées pour faciliter l'implementation du combat
        bool tryDodge() const;
        void attack(Personnage * &) const;

        // méthodes concernant les Objets
        const Objet * getObjetAt(int);
        void useObjet(int);
        void showObjets() const;
        int showUsableObjets() const;
        void putObjet(Objet * &);
        Objet & dropObjet(int);
        bool isSacFull() const;
        bool isAnyUsableObjet() const;
        int getNbItem() const;
friend
    ostream & operator<<(ostream &out, Personnage *p);
};


#endif /*PERSONNAGE_HPP*/