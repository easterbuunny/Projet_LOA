#include <fstream>
#include <sstream>
#include <random>

#include "Donjon.hpp"
#include "Piece.hpp"
#include "../Joueur/Joueur.hpp"
#include "../Joueur/Humain.hpp"
#include "../Joueur/Ia.hpp"

#include "../Objet/Arme.hpp"
#include "../Objet/Armure.hpp"
#include "../Objet/Chaussure.hpp"
#include "../Objet/CleTeleportation.hpp"
#include "../Objet/Potion.hpp"
#include "../Objet/Poison.hpp"

// == ctor & dtor ==
Donjon::Donjon(string path, int l, int c, int n, vector<vector<Piece *>> v)
    : pathDonjon(path), ligne(l), colonne(c), nbPieces(n), vectorDonjon(v){}

Donjon::~Donjon(){}

// == getter == 
Humain * & Donjon::getHumain() { return humain; }
vector<Ia *> & Donjon::getIas() { return ias; }

// == méthode lier au jeu ==

// -- 2 fonctions pour savoir quand sortir de la boucle de jeu --
bool Donjon::humainWin() { return ias.size() == 0; }

bool Donjon::humainDead() { return humain==nullptr; }

/* verifie si un des joueurs est mort et l'enlève*/
void Donjon::updateJoueurDead(){
    if(!humain->isAlive()){
        delete humain;
        humain = nullptr;
    }
    for(int i = 0; i < (int)ias.size(); i++)
        if(!ias.at(i)->isAlive()) ias.erase(ias.begin()+i);
}

string Donjon::getPathDonjon(){
    return pathDonjon;
}
int Donjon::getLigne(){
    return ligne;
}

int Donjon::getColonne(){
    return colonne;
}

int Donjon::getNbPieces(){
    return nbPieces;
}

vector<vector<Piece *>> Donjon::getVectorDonjon(){
    return vectorDonjon;
}


// initVoisins() nous permet d'ajouter les voisins des pieces
// tout en evitant de sortir du tableau. On gardant l'ordre N,E,S,W
// on aura tjrs un voisin null ou non vide.
void Donjon::initVoisins(){
    for(int i = 0; i < ligne; i++){
        for(int j = 0; j < colonne; j++){
            if(vectorDonjon.at(i).at(j) == nullptr) continue;
            // On commence à ajouter les voisins de chaque salles,
            // mais il faut vérifier si l'on ne dépase pas du vecteur :
            // si le voisin est vide, on l'ajoute quand même
            // haut
            Piece * haut = (i-1 >= 0) ? vectorDonjon.at(i-1).at(j) : nullptr;
            vectorDonjon.at(i).at(j)->addNextPiece(haut);
            // droite
            Piece * droite = (j+1 < colonne) ? vectorDonjon.at(i).at(j+1) : nullptr;
            vectorDonjon.at(i).at(j)->addNextPiece(droite);
            // bas
            Piece * bas = (i+1 < ligne) ? vectorDonjon.at(i+1).at(j) : nullptr;
            vectorDonjon.at(i).at(j)->addNextPiece(bas);
            // gauche
            Piece * gauche = (j-1 >= 0) ? vectorDonjon.at(i).at(j-1) : nullptr;
            vectorDonjon.at(i).at(j)->addNextPiece(gauche);
        }
    }
}

// Cette fonction nous donner un donjon prêt à être utilisé :
//      - lecture du fichier    - création du pointeur vers le donjon
//      - initialisation de toutes les salles (et de leurs voisins)
Donjon * Donjon::creerDonjon(string file){
    // lecture du fichier
    ifstream myFile(file);

    // on affecte le tableaux des salles
    string line= "";
    string delimiter = " ";
    vector<vector<Piece *>> tabDonjon;

    getline(myFile, line);
    istringstream iss(line);
    int ligne, colonne, nbSalles;
    iss >> ligne >> colonne >> nbSalles;

    for(int i = 0; i < ligne; i++){
        getline(myFile, line);

        size_t pos = 0;
        string token;
        vector<Piece *> myRow;
        for(int j = 0; j < colonne; j++){
            pos = line.find(delimiter);
            token = line.substr(0, pos);
            if(token.compare(".") == 0)
                myRow.push_back(nullptr);
            else
                myRow.push_back(new Piece());
            line.erase(0, pos + delimiter.length());
        }
        tabDonjon.push_back(myRow);
    }

    // on crée notre donjon et on paramètre ses salles
    Donjon * myDonjon = new Donjon(file, ligne, colonne, nbSalles, tabDonjon);
    myDonjon->initVoisins();

    myFile.close();
    return myDonjon;
}

void Donjon::initJoueurPieceVide(Joueur * joueur){
    random_device rd; // obtain a random number from hardware
    mt19937 gen(rd()); // seed the generator
    uniform_int_distribution<> randI(0, ligne-1); // range de I
    uniform_int_distribution<> randJ(0, colonne-1); // range de J

    while(true){
        int i = randI(gen), j = randJ(gen);
        if(vectorDonjon.at(i).at(j) != nullptr && vectorDonjon.at(i).at(j)->isEmpty()){
            // on ajout le joueur dans le donjon
            Humain * h = dynamic_cast<Humain*>(joueur);
            if(h) humain = h;
            else ias.push_back(dynamic_cast<Ia*>(joueur));
            // on l'ajout dans une piece
            vectorDonjon.at(i).at(j)->putJoueur(joueur);
            // on indique le donjon et la piece où il se situe;
            joueur->actualDonjon = this;
            joueur->actualPiece = vectorDonjon.at(i).at(j); 
            return;
        }
    }
}

/** Cette fonction va nous créer tous les objets disponible en 1 exemplaire*/
void Donjon::initObjetsDonjon(){
    random_device rd; // obtain a random number from hardware
    mt19937 gen(rd()); // seed the generator
    uniform_int_distribution<> randI(0, ligne-1); // range de I
    uniform_int_distribution<> randJ(0, colonne-1); // range de J
    // on crée les objets
    for(int tour = 0; tour < 6; tour++){
        int i, j;
        do{
            i = randI(gen);
            j = randJ(gen);
        } while(vectorDonjon.at(i).at(j) == nullptr);
        switch(tour){
            case 0:
                vectorDonjon.at(i).at(j)->addObjet(Arme::forgeArme());
                break;
            case 1:
                vectorDonjon.at(i).at(j)->addObjet(Armure::forgeArmure());
                break;
            case 2:
                vectorDonjon.at(i).at(j)->addObjet(Chaussure::forgeChaussure());
                break;
            case 3:
                vectorDonjon.at(i).at(j)->addObjet(CleTeleportation::forgeCleTeleportation());
                break;
            case 4:
                vectorDonjon.at(i).at(j)->addObjet(Potion::forgePotion());
                break;
            case 5:
                vectorDonjon.at(i).at(j)->addObjet(Poison::forgePoison());
                break;
        }
    }
}

// permet d'afficher le Donjon du point de vu du joueur humain
void Donjon::initJoueurPiece(int i , int j ,int id, Joueur * p){
    //ERROR : condition ne rentre pas
    if(vectorDonjon.at(i).at(j)!=nullptr && vectorDonjon.at(i).at(j)->getId()==id){  
        vectorDonjon.at(i).at(j)->putJoueur(p);
        p->actualPiece = vectorDonjon.at(i).at(j);
    }
}


ostream & operator<<(ostream & out, const Donjon *d){
    // on affiche la carte avec les personnages dedans
    out << endl;
    for(int i = 0; i < (int)d->vectorDonjon.size(); i++){
        out << "\t";
        for(int j = 0; j < (int)d->vectorDonjon.at(i).size(); j++){
            const Piece * p = d->vectorDonjon.at(i).at(j);
            if(p == nullptr || !p->isVisited())
                out << ". ";    // mur ou salle non découvert
            else if(p->isHumainHere())
                out << "* ";    // salle joueur courant
            else if(!p->isEmpty())
                out << "O ";    // salle avec un adversaire minimum
            else
                out << "X ";    // salle vide
        }
        out << endl;
    }
    out << endl;
    return out;
}