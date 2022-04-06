#include "../Headers/tplayerwindow.h"
#include "ui_tplayerwindow.h"
#include "../Headers/mainwindow.h"
#include "../Headers/joueur.h"
#include "../Headers/resultat.h"

using namespace std;
TPlayerWindow::TPlayerWindow(MainWindow *dad, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TPlayerWindow)
{
    ui->setupUi(this);
    nbrplayer = dad->number_player;
    if(dad->number_player == 2)
    {
        ui->lineEdit_B->setVisible(false);
        ui->spinBox_B->setVisible(false);
    }
    if(dad->number_player == 1)
    {
        ui->lineEdit_A->setVisible(false);
        ui->spinBox_A->setVisible(false);
        ui->lineEdit_C->setVisible(false);
        ui->spinBox_C->setVisible(false);
    }
    if(dad->state == 1 && dad->number_player == 3) //On vient de load
    {
        ui->lineEdit_A->setText(QString::fromStdString(dad->vect_player[0].nom));
        ui->lineEdit_B->setText(QString::fromStdString(dad->vect_player[1].nom));
        ui->lineEdit_C->setText(QString::fromStdString(dad->vect_player[2].nom));
        ui->spinBox_A->setValue(dad->vect_player[0].degats);
        ui->spinBox_B->setValue(dad->vect_player[1].degats);
        ui->spinBox_C->setValue(dad->vect_player[2].degats);
        ui->lineEdit_4->setText(QString::fromStdString(dad->b.nom));
        ui->spinBox_Boss_Hp->setValue(dad->b.hp);
        ui->spinBox_Boss_Xp->setValue(dad->b.xp);

    }

    QObject::connect(ui->pushButton_E, SIGNAL(clicked()), this, SLOT(Execute()));
}

TPlayerWindow::~TPlayerWindow()
{
    delete ui;
}

void TPlayerWindow::Save()
{
}
void calculshapley(vector<string> list, boss b, double* S, Joueur **J, int nbrplayer)
{
    string tmp;
    int dp;

    for(int i = 0; i < (int)list.size(); i++)
    {
        dp = b.hp;
        tmp = list[i];
        for( int j = 0 ; j < (int)tmp.size(); j++)
        {
            //cout << J[tmp[j] - '1']->degats << " " << dp << endl;
            if(J[tmp[j] - '1']->degats <= dp)
            {
                S[tmp[j] - '1'] += J[tmp[j] - '1']->degats;
                dp -= J[tmp[j] - '1']->degats;
            }
            else
            {
                S[tmp[j] - '1'] += dp;
                dp = 0;
            }

        }
    }

    for(int i = 0 ; i < nbrplayer; i++) S[i] /= list.size();
}

void Gain(double *S, Joueur **J, boss b, int nbrplayer)
{
    for(int i = 0 ; i < nbrplayer ; i++) J[i]->gain = S[i]/b.hp*b.xp;
}
void permute(string a, int l, int r, vector<string> *list)
{
    char tmp;
    if( l == r )
    {
        list->push_back(a);
    }
    else {
        for( int i = l; i <= r; i++)
        {
            tmp = a[l];
            a[l] = a[i];
            a[i] = tmp;

            permute(a, l+1, r, list);

            tmp = a[l];
            a[l] = a[i];
            a[i] = tmp;
        }
    }
}

void TPlayerWindow::Execute()
{
    Boss b;
    b.hp = ui->spinBox_Boss_Hp->value();
    b.xp = ui->spinBox_Boss_Xp->value();
    b.nom = ui->lineEdit_4->text().toStdString();
    std::cout << "nom: " << b.nom;
    std::cout << endl << "hp: " << b.hp;
    std::cout << endl << "xp: " << b.xp << endl;
    if(nbrplayer == 3 && ui->checkBox_Constant->isChecked())
    {
        string res = "";
        Joueur Alice = Joueur(ui->lineEdit_A->text().toStdString(),ui->spinBox_A->value());
        Joueur Bob = Joueur(ui->lineEdit_B->text().toStdString(),ui->spinBox_B->value());
        Joueur Charlie = Joueur(ui->lineEdit_C->text().toStdString(),ui->spinBox_C->value());
        //TABLEAU DE JOUEURS **************

        Joueur* J[nbrplayer];
        J[0] = &Alice;
        J[1] = &Bob;
        J[2] = &Charlie;

        //CREATION DU STRING POUR PERMU ***

        string a = "123";

        // CREATION DE LA LISTE QUI ACCEUILLERA LES PERMUS

        vector<string> list;
       // REMPLISSAGE DE LA LISTE **********************

        permute(a, 0, a.size()-1, &list);

        //AFFICHAGE DE LA LISTE **************************
        cout << "-----------------------------" << endl;
        cout << "PERMUTATIONS: " << endl;

        cout << endl << list.size() << " permutations générées:" << endl;
        for(int i = 0; i < (int)list.size(); i++) cout << list[i] << endl;
        //CREATION DU TABLEAU QUI ACCEUILLERA LES SHAPLEY VALUES
        double S[nbrplayer];
        ///init du tableau
       for(int i = 0 ; i < nbrplayer ; i++) S[i] = 0;

        //REMPLISSAGE DU TABLEAU
        calculshapley(list, b, S, J, nbrplayer);

            //AFFICHAGE
            cout << "-----------------------------" << endl;
            cout << "SHAPLEY VALUES: " << endl;
            res+= "SHAPLEY VALUES: \n";
            cout << endl;
        for(int i = 0 ; i < nbrplayer ; i++)
        {
            res += J[i]->nom;
            res+= ": ";
            res+=S[i];
            res+="\n";
            cout << J[i]->nom << ": " << S[i] << endl;
        }
            cout << endl;
            res+="\n";
            //REPARTITION DES GAINS
        Gain(S,J,b,nbrplayer);

            //AFFICHAGE
            cout << "-----------------------------" << endl;
            cout << "REPARTITION DES GAINS: " << endl;
            res+="REPARTITION DES GAINS: \n";
            std::cout << endl << "nom: " << Alice.nom;
            std::cout << endl << "gain: " << Alice.gain << endl;
            std::cout << endl << "nom: " << Bob.nom;
            std::cout << endl << "gain: " << Bob.gain << endl;
            std::cout << endl << "nom: " << Charlie.nom;
            std::cout << endl << "gain: " << Charlie.gain << endl;
            cout << "-----------------------------" << endl;

            cout << Alice.toString() << endl;;
    }
    /*resultat reswindow(this);
    reswindow.setModal(true);
    reswindow.exec();*/
}
