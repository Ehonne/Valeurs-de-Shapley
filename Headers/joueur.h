#ifndef JOUEUR_H
#define JOUEUR_H
#include "iostream"
using namespace std;

class Joueur
{
public:
    int degat;
    string nom;

    Joueur();
    Joueur(int dmg, string name);

    ~Joueur();
};

#endif // JOUEUR_H
