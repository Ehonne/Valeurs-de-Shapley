#include "../Headers/tplayerwindow.h"
#include "ui_tplayerwindow.h"
#include "../Headers/mainwindow.h"
#include "../Headers/joueur.h"
#include "../Headers/resultat.h"
#include <fstream>
#include "QMessageBox"

using namespace std;
TPlayerWindow::TPlayerWindow(QPlayerWindow *dad, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TPlayerWindow)
{
    ui->setupUi(this);
    state = 0;
    QObject::connect(ui->pushButton_exec, SIGNAL(clicked()), this, SLOT(Execute()));
    QObject::connect(ui->pushButton_cancel, SIGNAL(clicked()), this, SLOT(Cancel()));

}

TPlayerWindow::~TPlayerWindow()
{
    delete ui;
}

void TPlayerWindow::Cancel()
{
    state = 1;
    close(); //end of the window
}


void TPlayerWindow::Execute()
{
    int nbrj = ui->spinBox_nbr->value();
    int degmax = ui->spinBox_2_deg->value();
    int hpmax = ui->spinBox_3_hpb->value();
    int xpmax = ui->spinBox_xpb->value();
    nbr_player = nbrj;

    b.nom = "nom";
    b.hp = rand()%hpmax;
    b.xp = rand()%xpmax;

    string tmp;

    ///Ouverture du fichier
    ifstream f("prenoms.txt", ios::in);

    if(f)
    {
     ///Création des n joueurs
    for(int i = 0 ; i < nbrj ; i++)
    {
        getline(f,tmp);
        Joueur J1 = Joueur(tmp,rand()%degmax+1);
        vect_player.push_back(J1);
    }
    }
      else
    {
        QMessageBox::critical(this, "Entry error", "Veuillez verifier que le fichier prenom est bien present");
    }

     f.close();
    state = 0;
    close();
}
