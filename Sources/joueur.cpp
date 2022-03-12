#include "../Headers/joueur.h"
#include <string>
#include <sstream>
Joueur::Joueur()
{
    nom = "Alice";
    degats = 2;
    gain = 0;
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

ostream& operator << (ostream &os, const Joueur &s) {
    return (os << "Nom: " << s.nom << ", Degat: " << s.degats << ", Gain: " << s.gain);
}

std::string Joueur::toString() const {
    stringstream ss;
    ss << (*this);
    return ss.str();
}
