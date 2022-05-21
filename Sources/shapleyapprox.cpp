#include <iostream>
#include "../Headers/joueur.h"
#include "../Headers/loadwindow.h"
#include <vector>
#include <time.h>
#include <fstream>
#include <unistd.h>

using namespace std;


//Fonction de permutation pour la génération des n! combinaisons

void ShapleyApprox(Joueur **J, double* S, boss b, int nbjoueurs, int m)
{
    int tmp, r;
    int a[nbjoueurs];

    for(int i = 0; i < nbjoueurs; i++) a[i] = i;

    for(int x = 0; x < m ; x++)
    {
        int hprestant;
        hprestant = b.hp;

        for(int j = nbjoueurs-1; j > 1; j--)
        {
            r = (double) rand()/RAND_MAX * j;

            if(j != r)
            {
                tmp = a[j];
                a[j] = a[r];
                a[r] = tmp;
            }
        }

        ///Calcul de Shapley sur la permutation initiale
        for(int x = 0; x < nbjoueurs; x++)
        {
            if( J[a[x]]->degats <= hprestant)
            {
                S[a[x]] +=  J[a[x]]->degats;
                hprestant -= J[a[x]]->degats;
            }
            else
            {
                S[a[x]] += hprestant;
                hprestant = 0;
                break;
            }
        }
    }

}

//Repartition des gains

void GainApprox(double *S, Joueur **J, boss b,int nbjoueurs)
{
    for(int i = 0 ; i < nbjoueurs ; i++) J[i]->gain = S[i]/b.hp*b.xp;
}

int cacl()
{


    return 0;
}
