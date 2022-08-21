#include "Humain.hpp"
#include "../Personnage/Personnage.hpp"
#include "../Objet/Objet.hpp"
#include "Ia.hpp"

Humain::Humain(Personnage * p) : Joueur(p) {}

Humain * Humain::forgeJoueurHumain(int choix){
    return new Humain(Personnage::forgePersonnage(choix));
}

void Humain::takeObjet(int i){
    Objet * o = &(actualPiece->getObjetAt(i));
    personnage->putObjet(o);
}

void Humain::dropObjet(int i){
    Objet * o = &(personnage->dropObjet(i));
    actualPiece->addObjet(o);
}

void Humain::useObjet(int i){
    // il a 2 cas possible : la option ou le poison
    int healBefore = personnage->getHealthPoint();
    personnage->useObjet(i);
    if(healBefore != personnage->getHealthPoint()){
        cout << "PV " << healBefore << " -> " << personnage->getHealthPoint();
    }
}

void Humain::stay() { 
    cout << "\t~~ Restons sur place un moment ~~" << endl;
}

void Humain::move(){
    // on récupère d'abord les prochaines salles disponibles
    vector<Piece *> piecesVoisines = actualPiece->getPiecesVoisines();
    // !!! TEXT MIS A PART : car l'ajout du text se fait en fonction
    // des salles que connait le joueur humain !!!
    cout << "== Selectionner la prochaine porte ==" << endl;
    for(int i = 0; i < 4; i++){
        if(piecesVoisines.at(i) == nullptr){ // on vérifie que la prochaine salle n'est pas un mur
            cout << "\t" << i+1 << "- MUR" << endl;
            continue;
        }
        cout << "\t" << i+1 << "- ";
        switch(i){
            case 0: cout << "HAUT" << endl; break;
            case 1: cout << "DROITE" << endl; break;
            case 2: cout << "BAS" << endl; break;
            case 3: cout << "GAUCHE" << endl; break;
        }
    }
    // ~ IMPLE ~
    int cJoueur;
    while(1){
        cout << "choix : ";
        cin >> cJoueur;
        cJoueur--; // On a commencé à 0
        if(cin.fail() || (cJoueur < 0 || cJoueur > 3) || (piecesVoisines.at(cJoueur)==nullptr))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout<< "Veuillez inscrire un choix correct"<<endl;
        }
        else break;
    }
    actualPiece = actualPiece->updateMoveJoueur(cJoueur, this); // maj de la position du joueur
}

bool Humain::amIAlone(){ return actualPiece->getJoueurs().size() == 1; }

/** true si humain a gagné & false si humain mort*/
bool Humain::fightRoom(){
    // on récupère les jours présents dans la salle
    vector<Joueur *> joueurs = actualPiece->getJoueurs();
    // == Affichage des adversaires == 
    cout << "\t### Voici vos adversaires, combatez les ! ";
    for(int i = 0; i < (int)joueurs.size(); i++){
        if(dynamic_cast<Humain *>(joueurs.at(i))) continue;
        cout << joueurs.at(i)->getPersonnage()->getName() << " ";
    }
    cout << " ####" << endl;
    // == Combat chaque adversaire ==
    for(int i = 0; i < (int)joueurs.size(); i++){
        if(dynamic_cast<Humain *>(joueurs.at(i))) continue;
        Ia * adv = dynamic_cast<Ia *>(joueurs.at(i));
        // -- TEXT --
        cout << "--" << personnage->getName() << " (vous) contre "
        << adv->getPersonnage()->getName() << "--" << endl;
        // savoir si l'humain attaque en premier ou nn
        bool humainTurn = this->isFasterThan(adv);
        bool humainKilled = false, iaKilled = false;
        // -- boucle d'attaque --
        while(!humainKilled && !iaKilled){
            if(humainTurn) iaKilled = this->fight(adv);
            else humainKilled = adv->fight(this);
            humainTurn = !humainTurn; // permet d'échanger le tour d'attaque
        }
        cout << endl;
        if(humainKilled) return false;
    }
    return true;
}