#include <iostream>
#include "../Headers/joueur.h"
#include "../Headers/loadwindow.h"
#include <vector>
#include <time.h>
#include <fstream>
#include <unistd.h>

using namespace std;

//Fonction de permutation pour la génération des n! combinaisons

void Shapleyy(Joueur **J, double* S, Boss b, int nbjoueurs)
{
        int a[nbjoueurs], p[nbjoueurs+1];
        int i, j, tmp;
        int hprestant;

        for(i = 0; i < nbjoueurs; i++)
        {
            a[i] = i + 1;
            p[i] = i;
        }
        p[nbjoueurs] = nbjoueurs;

        hprestant = b.hp;

        ///Calcul de Shapley sur la permutation initiale
        for(int x = 0; x < nbjoueurs; x++)
        {
            if( J[a[x]-1]->degats <= hprestant)
            {
                S[a[x]-1] +=  J[a[x]-1]->degats;
                hprestant -= J[a[x]-1]->degats;
            }
            else
            {
                S[a[x]-1] += hprestant;
                hprestant = 0;
                break;
            }
        }

        i=1;
        while(i < nbjoueurs)
        {

            p[i]--;
            j = i % 2 * p[i];
            tmp = a[j];
            a[j] = a[i];
            a[i] = tmp;

            ///Calcul de Shapley sur la permutation générée
            hprestant = b.hp;
            for(int x = 0; x < nbjoueurs; x++)
            {
                if( J[a[x]-1]->degats <= hprestant)
                {
                    S[a[x]-1] +=  J[a[x]-1]->degats;
                    hprestant -= J[a[x]-1]->degats;
                }
                else
                {
                    S[a[x]-1] += hprestant;
                    hprestant = 0;
                    break;
                }
            }

            i=1;
            while(!p[i])
            {
                p[i] = i;
                i++;
            }
        }
    }


//Repartition des gains

void Gainn(double *S, Joueur **J, Boss b, int nbjoueurs)
{
    for(int i = 0 ; i < nbjoueurs ; i++) J[i]->gain = S[i]/b.hp*b.xp;
}



int calcshap()
{

    return 0;
}
