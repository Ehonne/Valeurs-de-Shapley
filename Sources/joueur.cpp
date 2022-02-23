#include "../Headers/joueur.h"

Joueur::Joueur()
{
    nom = "Alice";
    degat = 2;
}

Joueur::Joueur(int dmg, string name)
{
    nom = name;
    degat = dmg;
}
