#ifndef DONJON_HPP
#define DONJON_HPP

#include <iostream>
#include <vector>

#include "../Objet/Poison.hpp"

using namespace std;

class Joueur;
class Ia;
class Humain;
class Piece;

class Donjon {
friend 
    void Poison::curseRandJoueur();
    private:
        // attributs
        const string pathDonjon;
        const int ligne, colonne, nbPieces;
        const vector<vector<Piece *>> vectorDonjon;
        Humain * humain;
        vector<Ia *> ias;

        Donjon(string, int, int, int, vector<vector<Piece *>>);

        void initVoisins();
    public:
        // ctor par copie & dtor
        Donjon(const Donjon &) = delete;
        virtual ~Donjon();
        static Donjon * creerDonjon(string);

        // getter
        Humain * & getHumain();
        vector<Ia *> & getIas();

        //get & set
        string getPathDonjon();
        int getLigne();
        int getColonne();
        int getNbPieces();
        vector<vector<Piece *>> getVectorDonjon();

        // methode lier au jeu
        void updateJoueurDead();
        void initJoueurPieceVide(Joueur *);
        void initObjetsDonjon();
        bool humainWin();
        bool humainDead();
        void initJoueurPiece(int i , int j, int id, Joueur * p);
    friend
        ostream & operator<<(ostream &, const Donjon *);
};

#endif /*DONJON_HPP*/