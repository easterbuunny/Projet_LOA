#ifndef OBJET_HPP
#define OBJET_HPP
#include <iostream>
#include <string>

using namespace std;

class Objet{
    protected:
        const bool usable;
        const string name;
        Objet(string, bool);
    public:
        virtual ~Objet(){}
        const string getName();
        bool isUsable();
        virtual int getStat() = 0;
};

#endif /*OBJET_HPP*/