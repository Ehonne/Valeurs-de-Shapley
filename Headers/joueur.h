#ifndef JOUEUR_H
#define JOUEUR_H
#include "iostream"
using namespace std;

class Joueur
{
public:
    string nom;
    double degats;
    double gain;

    Joueur();
    Joueur(string nom, double degats);
    std::string toString() const;
    ~Joueur();
};

#endif // JOUEUR_H
