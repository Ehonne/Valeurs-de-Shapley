#include <iostream>
#include "../Headers/joueur.h"
#include "../Headers/loadwindow.h"
#include <vector>
#include <time.h>
#include <fstream>
#include <unistd.h>

using namespace std;


//array to string

string atos(int* a, int nbjoueurs)
{
    string rtn,tmp;

    for(int i = 0 ; i < nbjoueurs; i++)
    {
        tmp = to_string(a[i]);
        rtn += tmp;
    }
    return rtn;
}

//n!

double factoriel(int n)
{
    double rtn = 1;
    for(int i = 2; i <= n; i++) rtn *= i;
    return rtn;
}

//bit Mix Function

unsigned long mix(unsigned long a, unsigned long b, unsigned long c)
{
    a=a-b;  a=a-c;  a=a^(c >> 13);
    b=b-c;  b=b-a;  b=b^(a << 8);
    c=c-a;  c=c-b;  c=c^(b >> 13);
    a=a-b;  a=a-c;  a=a^(c >> 12);
    b=b-c;  b=b-a;  b=b^(a << 16);
    c=c-a;  c=c-b;  c=c^(b >> 5);
    a=a-b;  a=a-c;  a=a^(c >> 3);
    b=b-c;  b=b-a;  b=b^(a << 10);
    c=c-a;  c=c-b;  c=c^(b >> 15);
    return c;
}

//Fonction de permutation pour la génération des n! combinaisons

void Shapley(Joueur **J, double* S, int nbjoueurs)
{
    double degats = 0;

    for(int i = 0 ; i < nbjoueurs; i++) degats += J[i]->degats;

    for(int i =0; i < nbjoueurs; i++) S[i] = J[i]->degats / degats;

}

//Repartition des gains

void Gain(double *S, Joueur **J, Boss b, int nbjoueurs)
{
    double degats = 0;

    for(int i = 0 ; i < nbjoueurs ; i++)
    {
        degats += b.hp * S[i];
        J[i]->gain = S[i]*b.xp;
    }

}
vector<Joueur> tabtovecteur(Joueur** J,int nbjoueurs)
{
    vector<Joueur> v;

        for(int i = 0 ; i < nbjoueurs; i++)
        {
            v.push_back(Joueur(J[i]->nom,J[i]->degats));
            v[i].gain = J[i]->gain;
        }

    return v;
}

Joueur** vecteurtotab(vector<Joueur> v)
{
    Joueur** J = (Joueur**) malloc(v.size()*sizeof(Joueur));

        for(int i = 0 ; i < v.size(); i++)
        {
            J[i] = new Joueur(v[i].nom,v[i].degats);
            J[i]->gain = v[i].gain;
        }

    return J;
}


vector<Joueur> calcsimple(vector<Joueur> vect, Boss b)
{
    time_t start = time(NULL);
    cout << "-----------------------------" << endl;
    cout << "JOUEURS: " << endl;
    int nbjoueurs = vect.size();
    Joueur** J = vecteurtotab(vect);

    double S[vect.size()];

    for(int x = 0; x < nbjoueurs; x++) S[x] = 0;

    Shapley(J,S,nbjoueurs);

    cout << "-----------------------------" << endl;
    cout << "SHAPLEY VALUES: " << endl;

    cout << endl;
    for(int i = 0 ; i < nbjoueurs ; i++) cout << J[i]->nom << ": " << S[i]*b.hp << endl;
    cout << endl;

    Gain(S,J,b,nbjoueurs);

    cout << "-----------------------------" << endl;
    cout << "REPARTITION DES GAINS: " << endl;

    for(int i = 0 ; i < nbjoueurs ; i++) cout << J[i]->nom << ": " << J[i]->gain << endl;
    cout << "-----------------------------" << endl;

    printf("Durée totale : %ds\n",(int)time(NULL) - start);
    vector<Joueur> v = tabtovecteur(J, nbjoueurs);
    for(int i = 0 ; i < nbjoueurs; i++) free(J[i]);

    return v;
}
