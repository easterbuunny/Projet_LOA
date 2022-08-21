#include "Personnage.hpp"

#include "Guerrier.hpp"
#include "Amazone.hpp"
#include "Moine.hpp"
#include "Sorciere.hpp"

#include "../Objet/Objet.hpp"
#include "../Objet/Arme.hpp"
#include "../Objet/Armure.hpp"
#include "../Objet/Chaussure.hpp"
#include "../Objet/Poison.hpp"
#include "../Objet/Potion.hpp"
#include "../Objet/CleTeleportation.hpp"

// == ctor & création de personnage ==
Personnage::Personnage(string n, int hp, int hap, int dp, int at) : 
    name(n), healthPoint(hp), habilityPoint(hap), defencePoint(dp), attackPoint(at){}

Personnage * Personnage::forgePersonnage(int i){
    // pas besoin de break vu que l'on return directement
    switch(i){
        case (1) : return new Guerrier();
        case (2) : return new Amazone();
        case (3) : return new Moine();
        case (4) : return new Sorciere();
    }
    return nullptr;
}

// == getter & setter ==
const void Personnage::showStats() const{
    cout << "\t~~ Caractéristique du Joueur ~~" << endl;
    cout << "\tVous êtes un : " << name << endl;
    cout << "\tHP  - " << healthPoint << endl;
    cout << "\tATK - " << attackPoint << endl;
    cout << "\tDEF - " << defencePoint << endl;
    cout << "\tAGI - " << habilityPoint << "%" << endl;
    cout << endl;
}
const string Personnage::getName() const {return name;}
const int Personnage::getHealthPoint() const {return healthPoint;}
const int Personnage::getHabiltyPoint() const {return habilityPoint;}
const int Personnage::getDefencePoint() const {return defencePoint;}
const int Personnage::getAttackPoint() const {return attackPoint;}

// == méthodes appelées pour faciliter l'implementation du combat ==
void Personnage::attack(Personnage * & adv) const{
    int myAtk = attackPoint, advDef = adv->defencePoint;
    adv->healthPoint = adv->healthPoint-(myAtk-advDef);
}

bool Personnage::tryDodge() const{
    random_device rd; // obtain a random number from hardware
    mt19937 gen(rd()); // seed the generator
    uniform_int_distribution<> rand(1, 100);
    return rand(gen) < habilityPoint;
}

// =================================================================

// == méthodes pour les Objets ==
bool Personnage::isAnyUsableObjet() const {
    for(int i = 0; i < (int)sac.size(); i++){
        if(sac.at(i)->isUsable()) return true;
    }
    return false;
}
bool Personnage::isSacFull() const { return sac.size()==4; }
int Personnage::getNbItem() const { return sac.size(); }
const Objet * Personnage::getObjetAt(int i){ return sac.at(i); }

// =================================================================

void Personnage::useObjet(int i){
    Objet & obj = *(sac.at(i));
    if(!obj.isUsable()) return;
    if(dynamic_cast<Potion*>(&obj)){
        Potion * o = dynamic_cast<Potion *>(&obj);
        healthPoint+=o->getStat();
    }
    else if(dynamic_cast<Poison*>(&obj)){
        Poison * o = dynamic_cast<Poison *>(&obj);
        o->curseRandJoueur();
    }
    else if(dynamic_cast<CleTeleportation*>(&obj)){
        CleTeleportation * o = dynamic_cast<CleTeleportation *>(&obj);
        o->teleportToIa();
    }
    sac.erase(sac.begin()+i);   
}

void Personnage::putObjet(Objet * & obj){ 
    if(dynamic_cast<Arme*>(obj)){
        Arme * o = dynamic_cast<Arme*>(obj);
        attackPoint+=o->getStat();
    }
    else if(dynamic_cast<Armure*>(obj)){
        Armure * o = dynamic_cast<Armure*>(obj);
        defencePoint+=o->getStat();
    }
    else if(dynamic_cast<Chaussure*>(obj)){
        Chaussure * o = dynamic_cast<Chaussure *>(obj);
        habilityPoint+=o->getStat();
    }
    sac.push_back(obj);
}

Objet & Personnage::dropObjet(int i){
    Objet * obj = sac.at(i);
    if(dynamic_cast<Arme*>(obj)){
        Arme * o = dynamic_cast<Arme *>(obj);
        this->attackPoint-=o->getStat();
    }
    else if(dynamic_cast<Armure*>(obj)){
        Armure * o = dynamic_cast<Armure *>(obj);
        this->defencePoint-=o->getStat();
    }
    else if(dynamic_cast<Chaussure*>(obj)){
        Chaussure * o = dynamic_cast<Chaussure *>(obj);
        this->habilityPoint-=o->getStat();
    }
    Objet & o = *sac.at(i);
    sac.erase(sac.begin()+i);
    return o;

}

// =================================================================

void Personnage::showObjets() const {
    cout << "\t--- Voici vos objets ---" << endl;
    for(int i = 0; i < (int) sac.size(); i++){
        cout << "\t" << i+1 << "- " << sac.at(i)->getName() << endl;
    }
    cout << endl;
}

int Personnage::showUsableObjets() const {
    cout << "\t--- Objets Consommable ---" << endl;
    int count = 0;
    for(int i = 0; i < (int) sac.size(); i++){
        if(!sac.at(i)->isUsable()) continue;
        count++;
        cout << "\t" << count << "- " << sac.at(i)->getName() << endl;
    }
    // ~ IMPLE ~
    int cJoueur;
    while(1){
        cout << "choix : ";
        cin >> cJoueur;
        cJoueur--; // On a commencé à 0
        if(cin.fail() || (cJoueur < 0 || cJoueur > (int)sac.size()-1) || !sac.at(cJoueur)->isUsable())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout<< "Veuillez inscrire un choix correct"<<endl;
        }
        else break;
    }
    return cJoueur;
}
