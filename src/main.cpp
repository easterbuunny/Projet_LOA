#include <iostream>
#include <random>
#include <fstream>
#include <istream>
#include <sstream>
#include <vector>

#include "Donjon/Donjon.hpp"
#include "Personnage/Personnage.hpp"
#include "Objet/Objet.hpp"

#include "Joueur/Joueur.hpp"
#include "Joueur/Humain.hpp"
#include "Joueur/Ia.hpp"

#define NB_DONJON_MIN 1
#define NB_DONJON_MAX 4

void debutDuJeu(bool);

using namespace std;

// Cette fonction nous servira à avoir tjrs un choix correcte auprès du joueur
// avec min l'indice de choix le plus petit qu'aura le joueur et max le plus grand
int boucleChoix(int min, int max){
    int cJoueur;
    while(1){
        cout << "Faites votre choix : ";
        cin >> cJoueur;
        if(cin.fail() || (cJoueur < min || cJoueur > max))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout<< "Veuillez inscrire un choix correct"<<endl;
        }
        else return cJoueur;
    }
}

// === Tous les Menus existants du jeu ===
int menuDebutDeJeu(){
    cout<<"1-Nouvelle Partie"<<endl;
    cout<<"2-Reprendre partie"<<endl;
    cout<<"3-Sortir"<<endl;
    int s = boucleChoix(1,3);
    return s;
}

int menuActionJoueurParTour(){
    cout << "-- Choisir une action --"      << endl;
    cout << "1-Inventaire"                << endl;
    cout << "2-Se deplacer"               << endl;
    cout << "3-Rester surplace"           << endl;
    cout << "4-Voir mes stats"           << endl;
    cout << "5-Sortir du jeu"             << endl;
    int cJoueur = boucleChoix(1,5);
    return cJoueur;
}

int menuInventaire(){
    cout << "-- Action Inventaire --"   << endl;
    cout << "1-Prendre un objet"      << endl;
    cout << "2-Laisser un objet"      << endl;
    cout << "3-Utiliser un objet"     << endl;
    cout << "4-Retour"                << endl;
    int cJoueur = boucleChoix(1,4);
    return cJoueur;
}

int menuSauvegarde(){
    cout<<"== Voulez vous sauvegarder? =="<<endl;
    cout<<"\t1-Oui"<<endl;
    cout<<"\t2-Non"<<endl;
    int cJoueur = boucleChoix(1,2);
    return cJoueur;
}

int choixPersonnage(){
    cout << "Veuiller choisir une classe de Personnage : " << endl;
    cout << "\t1- Guerrier" << endl;
    cout << "\t2- Amazone"  << endl;
    cout << "\t3- Moine"    << endl;
    cout << "\t4- Sorcier"  << endl;
    int cPersonnage = boucleChoix(1,4);
    return cPersonnage;
}
// ==========

int main(int argc, char **argv){
    cout<<"\t=~=~= Parcours du chateau =~=~="<<endl;
    int s = menuDebutDeJeu();
    switch (s){
        case (1):
            debutDuJeu(false);
            break;
        case (2):
            debutDuJeu(true);
            break;
    }
    return 0;
}


void debutDuJeu(bool reprise){
    // attribut commun à la reprise ou non du jeu
    int persoJoueur;
    vector<Joueur *> adversaires;
    vector<Joueur *> listJoueur;
    Joueur *joueur;
    Donjon *monDonjon;
    vector<int> position;
    int nbLigne = 0;
    int nbColonne = 0;
    int nbSalle = 0;
    if(!reprise){
        cout << "\t=== Que la partie commence ===" << endl;
        cout << "Si cela n'est pas déjà fait, nous vous invitons à lire les regles"  << endl;
        cout << "du jeu dans le fichier texte \"Regle du jeu\" qui vous est fourni." << endl;
        
        // ** Choix du personnage **
        // ~ TEXTE ~
        cout << "Veuiller choisir une classe de Personnage : " << endl;
        cout << "\t1- Guerrier" << endl;
        cout << "\t2- Amazone"  << endl;
        cout << "\t3- Moine"    << endl;
        cout << "\t4- Sorciere"  << endl;
        int persoJoueur = boucleChoix(1,4);

        // ** Création aléa d'un Donjon **
        string nomDonjon = "./res/donjon";
        random_device rd; // obtain a random number from hardware
        mt19937 gen(rd()); // seed the generator
        uniform_int_distribution<> rand(NB_DONJON_MIN, NB_DONJON_MAX);
        nomDonjon += to_string(rand(gen));
        monDonjon = Donjon::creerDonjon(nomDonjon);

        // ** Création + affectation des joueurs dans le donjon **
        joueur = Humain::forgeJoueurHumain(persoJoueur);
        monDonjon->initJoueurPieceVide(joueur);
        for(int i = 1; i <= 4; i++){
            if(persoJoueur == i) continue;
            Ia * ia = Ia::forgeJoueurIa(i);
            adversaires.push_back(ia); // on l'ajoute pour la sauvegarde
            monDonjon->initJoueurPieceVide(ia);
        }

        // ** initialisation des objets dans les salles **
        monDonjon->initObjetsDonjon();
    }
    else{
        cout<<"Récupere les fichiers effectuer dans la sauvegarde"<<endl;
        string type = "";
        string classe = "";
        int pos = 0;
        ifstream i_file_personnage("./res/position");
        if(!i_file_personnage.is_open())
            cout<<"Impossible d'ouvrir le fichier"<<endl;   
        else{
            for(int i =  0; i<4; i++){
                i_file_personnage>>type>>classe>>pos;
                if(type=="Joueur"){
                    if(classe=="Guerrier"){persoJoueur=1;}
                    else if(classe=="Amazone"){persoJoueur=2;}
                    else if(classe=="Moine"){persoJoueur=3;}
                    else{persoJoueur=4;}
                }
                position.push_back(pos);
            }
        }
        //Création des personnages sauvegarder
         for(int i = 0; i < 4; i++){
            if(persoJoueur == i) {
                joueur = Humain::forgeJoueurHumain(persoJoueur);
                listJoueur.push_back(joueur);
            }
            adversaires.push_back(Ia::forgeJoueurIa(i));
            listJoueur=adversaires;
        }

        //** Récuperer un donjon sauvegarder puis continuer le jeu en placant les informations a la bonne position **
        ifstream i_file("./res/save");
        if(!i_file.is_open()){
            cout<<"Impossible d'ouvrir le fichier"<<endl;
        }
        else{
            //Lire un fichier
            string ligne = "";
            string pathDonjon = "";
            string delimiter = " ";
            //Chercher le donjon correspondant
            getline(i_file,ligne);
            pathDonjon=ligne;
            ifstream i_file_donjon(pathDonjon);
            //Créer le donjon textuelle
            Donjon *monDonjon = Donjon::creerDonjon(pathDonjon);
            //Lit la ligne
            i_file_donjon>>nbLigne>>nbColonne>>nbSalle;
            char piece;
            //Lire les fichiers qui sauvegarde la map du donjon
            for(int i = 0; i<nbLigne; i++){
                //Lit la colonne
                for(int j = 0; j<nbColonne; j++){
                    i_file>>piece;
                    //Les salles visité
                    //Salle visité et qu'il peut avoir un adversaire ou un objet
                    if(piece=='X' || piece=='O'){
                        monDonjon->getVectorDonjon().at(i).at(j)->setVisited(true);
                    }
                    //Position du joueur
                    else if(piece=='*'){
                        monDonjon->getVectorDonjon().at(i).at(j)->setJoueurHere(true);
                        monDonjon->getVectorDonjon().at(i).at(j)->setVisited(true);
                    }
                    else{
                        monDonjon->getVectorDonjon().at(i).at(j)=nullptr;
                    }

                }
            }
            //Placement des personnages dans les pieces (ne fonctionne pas)
           /*  for(int k = 0; k<(int)position.size();k++){
                for(int i = 0; i<nbLigne;i++){
                    for(int j = 0; j<nbColonne; i++){
                        monDonjon->initPersonnagePiece(i,j,position.at(k),listJoueur.at(k));
                    }
                }
            } */
        }
        return ;
    }


    /* ** Boucle d'un tour de jeu ** */
    cout << "\n\t=== *chlik chlik* Vous êtes actuellement dans un donjon ===" << endl;
    // ~ IMPLE ~
    while(true){
        // == Affichage de la carte ==
        cout << monDonjon;
        // on récupère la référence du joueur et des ias
        Humain * & humain = monDonjon->getHumain();
        vector<Ia *> & adversaires = monDonjon->getIas();
        // == COMBAT ==
        if(humain->amIAlone())
            cout << "\t... Il n'y a personne dans cette piece, continuons ...\n" << endl;
        else{
            // !! La boucle se termine quand l'humain meurs ou que tous les autres IAs meurent
            if(!humain->fightRoom()) break;
            if(monDonjon->humainWin()) break;
        }
        // == comportement des ias ==
        for(int i = 0; i < (int)adversaires.size(); i++)
            adversaires.at(i)->behave();
        // == Affichage de la salle pour les objets presents ==
        cout << humain->getActualPiece() << endl;
        // == Actions à faire à la fin d'un combat ==
        /* On reste dans la boucle tant qu'on a pas choisi une fonction
         * qui va au tour prochain */
        int ctJoueur;
        do{
            ctJoueur = menuActionJoueurParTour();
            cout << endl;
            switch(ctJoueur){
                // Inventaire
                case(1):{
                    const Personnage * phumain = humain->getPersonnage();
                    phumain->showObjets();
                    int cj = menuInventaire();
                    switch(cj){
                        case 1 :{
                            if(phumain->isSacFull()){
                                cout << "Vous ne pouvez pas prendre, votre sac est rempli ..." << endl;
                                break;
                            }
                            else if(humain->getActualPiece()->getSizeObjets() == 0){
                                cout << "\n\t... La salle n'a pas d'objet ..." << endl;
                                break;
                            }
                            int min = 1, max = humain->getActualPiece()->getSizeObjets();
                            int citem = boucleChoix(min, max)-1;
                            humain->takeObjet(citem);
                            cout << humain->getActualPiece() << endl;
                            break;
                        }
                        case 2 :{
                            if(phumain->getNbItem() == 0){
                                cout << "\nRien à enlever !\n" << endl;
                                break;
                            }
                            int min = 1, max = phumain->getNbItem();
                            int citem = boucleChoix(min, max)-1;
                            humain->dropObjet(citem);
                            cout << humain->getActualPiece() << endl;
                            break;
                        }
                        case 3 :{
                            if(!phumain->isAnyUsableObjet()){
                                cout << "\n\t... Aucun objet consommable ...\n" << endl;
                                break;
                            }
                            int citem = phumain->showUsableObjets();
                            humain->useObjet(citem);
                            break;
                        }
                    }
                    cout << endl;
                    break;
                }
                // Movement
                case(2):
                    humain->move();
                    break;
                // Rester sur play
                case(3):
                    humain->stay();
                    break;
                // Afficher les stats
                case(4):
                    humain->getPersonnage()->showStats();
                    break;
                // Sauvegarder la partie 
                case(5): //Sauvegarder la partie
                    int cJoueur = menuSauvegarde();
                    if(cJoueur==1){
                        fstream o_file("./res/save");
                        fstream o_file_personnage("./res/position");

                        if(!o_file.is_open() || !o_file_personnage.is_open()){
                            cout<<"Impossible d'ouvrir le fichier"<<endl;
                        }
                        else{
                            //Ecrire dans un fichier
                            o_file<<monDonjon->getPathDonjon()<<endl;
                            o_file<<monDonjon<<endl;
                            o_file_personnage<<"Joueur "<<joueur->getPersonnage()->getName()<<" "<<joueur->getActualPiece()->getId()<<endl;
                            for(int i = 0; i<3; i++){
                                o_file_personnage<<"IA "<<adversaires.at(i)->getPersonnage()->getName()<<" "<<adversaires.at(i)->getActualPiece()<<endl;
                            }
                        }

                        o_file.close();
                        o_file_personnage.close();
                    }
                    return;
            }
        }while(ctJoueur == 1 || ctJoueur == 4);
    /* GAME OVER */
    if(monDonjon->humainDead())
        cout << "Ah, tu es mort, dommage ... YOU DIED" << endl;
    else if(monDonjon->humainWin())
        cout << "Bravo, tu as tué tous les ennemis ! YOU WIN!" << endl;
    else
        cout << "prblm implémentation" << endl;
    }
}