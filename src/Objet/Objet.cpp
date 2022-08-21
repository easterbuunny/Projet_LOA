#include "Objet.hpp"

Objet::Objet(string n, bool u) :  usable(u), name(n){}

const string Objet::getName(){ return name; }

bool Objet::isUsable(){ return usable; }