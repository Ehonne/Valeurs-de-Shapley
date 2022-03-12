#include "../Headers/joueur.h"

Joueur::Joueur()
{
    nom = "Alice";
    degats = 2;
}

Joueur::Joueur(string nom, double degats)
{
    this->nom = nom;
    this->degats = degats;
    this->gain = 0;
}

Joueur::~Joueur()
{

}
