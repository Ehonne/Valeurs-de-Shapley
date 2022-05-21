#include "../Headers/qplayerwindow.h"
#include "../Headers/tplayerwindow.h"
#include "ui_qplayerwindow.h"
#include "QMessageBox"
#include "../Headers/joueur.h"
#include "../Headers/resultat.h"
#include "../Sources/simple.cpp"
#include "../Sources/shapley.cpp"
#include "../Sources/shapleyapprox.cpp"
#include <bits/stdc++.h>
#include <fstream>
using namespace std;

QPlayerWindow::QPlayerWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QPlayerWindow)
{
    ui->setupUi(this);
    nbr_player = ui->spinBox->value();
    ui->tableWidget_player->setRowCount(ui->spinBox->value());
    QObject::connect(ui->pushButton_E, SIGNAL(clicked()), this, SLOT(make()));
    QObject::connect(ui->pushButton_save, SIGNAL(clicked()), this, SLOT(save()));
    QObject::connect(ui->pushButton_load, SIGNAL(clicked()), this, SLOT(load()));
    QObject::connect(ui->pushButton_Gen, SIGNAL(clicked()), this, SLOT(GenAlea()));
    QObject::connect(ui->spinBox, SIGNAL(valueChanged(int)), this, SLOT(updatetab()));
}

QPlayerWindow::~QPlayerWindow()
{
    delete ui;
}
bool QPlayerWindow::get_vect()
{//recuperation des données saisies dans l'objet addvectwindow
    int size;
   for (int i = 0; i < nbr_player; i++)
   {
       if(!ui->tableWidget_player->item(i,0))
       {
           QMessageBox::critical(this, "Entry error", "Cellule vide");
           vect_joueur.clear();
           return false;
       }
       if(!ui->tableWidget_player->item(i,1))
       {
           QMessageBox::critical(this, "Entry error", "Cellule vide");
           vect_joueur.clear();
           return false;
       }

       std::string temp = ui->tableWidget_player->item(i,1)->text().toStdString();
       std::string nam = ui->tableWidget_player->item(i,0)->text().toStdString();
       size = temp.length();
       for (int j = 0; j < size; j++)
       {
           if (!isdigit(temp[j]))
           {
               cout << temp[j] << endl;
               QMessageBox::critical(this, "Entry error", "Dégat doit etre un entier.");
               vect_joueur.clear();
               return false;
           }
           if(ui->tableWidget_player->item(i,0)->text().isEmpty())
           {
               QMessageBox::critical(this, "Entry error", "Missing name for your player.");
               vect_joueur.clear();
               return false;
           }
       }
       Joueur J1 = Joueur(nam,std::stoi(temp));
       std::cout << J1.nom << " - " << J1.degats << endl;
       vect_joueur.push_back(J1);
       vect_joueur2.push_back(J1);
       vect_joueur3.push_back(J1);
   }
   return true;
}
void QPlayerWindow::updatetab()
{
    ui->tableWidget_player->setRowCount(ui->spinBox->value());
    nbr_player = ui->spinBox->value();
}
void QPlayerWindow::GenAlea()
{
    TPlayerWindow genwindow(this);
    genwindow.setModal(true);
    genwindow.exec();
}
void QPlayerWindow::load()
{
    loadwindow secwind(this);
    secwind.setModal(true);
    secwind.exec();
    if(secwind.state == 0)
    {
        std::cout << "nbrplayer: " << secwind.nbr_player << endl;
        for (Joueur i: secwind.vect_player)
            std::cout << i.toString() << endl;
        std::cout << secwind.b.nom << secwind.b.xp << secwind.b.hp << endl;
        ui->spinBox->setValue(secwind.nbr_player);
         nbr_player = secwind.nbr_player;

             for(int i = 0; i < nbr_player; i++)
             {
                 QTableWidgetItem *newItem = new QTableWidgetItem();
                         newItem->setData(Qt::DisplayRole,secwind.vect_player[i].degats);
                 ui->tableWidget_player->setItem(i,1,newItem);
                 QTableWidgetItem *newItemname = new QTableWidgetItem(QString::fromStdString(secwind.vect_player[i].nom));
                 ui->tableWidget_player->setItem(i,0,newItemname);
             }
             ui->lineEdit_4->setText(QString::fromStdString(secwind.b.nom));
             ui->spinBox_4->setValue(secwind.b.hp);
             ui->spinBox_5->setValue(secwind.b.xp);
    }
}
void QPlayerWindow::save()
{
    bool state = get_vect();
    if(!state)
    {
        return;
    }
    else
    {
        ofstream myfile;
        myfile.open ("save.txt");
        myfile << (int)vect_joueur.size();
        myfile << "\n";
        for (int i = 0; i< (int)vect_joueur.size() ; i++) {
            myfile << vect_joueur[i].nom;
            myfile << " ";
            myfile << vect_joueur[i].degats;
            myfile << "\n";
        }
        if(ui->lineEdit_4->text().isEmpty())
        {
            QMessageBox::critical(this, "Entry error", "Nom du boss vide");
            vect_joueur.clear();
            return;
        }
        myfile << ui->lineEdit_4->text().toStdString();
        myfile << " ";
        myfile << ui->spinBox_5->text().toStdString();
        myfile << " ";
        myfile << ui->spinBox_4->text().toStdString();
        myfile << "\n";
        myfile.close();
        QMessageBox::information(this, "Sauvegarde reussi", "Veuillez trouver votre fichier dans vos documents");
        vect_joueur.clear();
    }
}

void QPlayerWindow::make()
{
    bool state = get_vect();
    b.hp = ui->spinBox_4->value();
    b.xp = ui->spinBox_5->value();
    b.nom = ui->lineEdit_4->text().toStdString();
    if(!state)
    {
        return;
    }
    else
    {
        if(ui->checkBox_class->isChecked())
        {
            time_t start = time(NULL);
            cout << "-----------------------------" << endl;
            cout << "JOUEURS: " << endl;
            int nbjoueurs = vect_joueur.size();
            Joueur** J = vecteurtotab(vect_joueur);

            double S[vect_joueur.size()];

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
            timeS1 = (int)time(NULL) - start;
            vect_joueur = tabtovecteur(J, nbjoueurs);
            for(int i = 0 ; i < nbjoueurs; i++) free(J[i]);
        }
        if(ui->checkBox_Const->isChecked())
        {
            time_t start = time(NULL);

            int nbjoueurs = vect_joueur2.size();
            Joueur** J = vecteurtotab(vect_joueur2);

            double S[nbjoueurs];

            for(int x = 0; x < nbjoueurs; x++) S[x] = 0;
            Shapleyy(J,S,b,nbjoueurs);
            for(int x = 0; x < nbjoueurs; x++) S[x] /= factoriel(nbjoueurs);

            cout << "-----------------------------" << endl;
            cout << "SHAPLEY VALUES: " << endl;

            cout << endl;
            for(int i = 0 ; i < nbjoueurs ; i++) cout << J[i]->nom << ": " << S[i] << endl;
            cout << endl;

            Gainn(S,J,b,nbjoueurs);

            cout << "-----------------------------" << endl;
            cout << "REPARTITION DES GAINS: " << endl;

            for(int i = 0 ; i < nbjoueurs ; i++) cout << J[i]->nom << ": " << J[i]->gain << endl;
            cout << "-----------------------------" << endl;
            printf("Durée totale : %ds\n",(int)time(NULL) - start);
            timeS2 = (int)time(NULL) - start;
            vect_joueur2 = tabtovecteur(J, nbjoueurs);
            for(int i = 0 ; i < nbjoueurs; i++) free(J[i]);
        }
        if(ui->checkBox_Pol->isChecked())
        {
            time_t start = time(NULL);
            int nbjoueurs = vect_joueur3.size();
            int m = pow(10,ui->spinBox_2->value());
            Joueur** J = vecteurtotab(vect_joueur3);
            double S[nbjoueurs];

            for(int x = 0; x < nbjoueurs; x++) S[x] = 0;
            ShapleyApprox(J,S,b,nbjoueurs,m);
            for(int x = 0; x < nbjoueurs; x++) S[x] /= m;

            cout << "-----------------------------" << endl;
            cout << "SHAPLEY VALUES: " << endl;

            cout << endl;
            for(int i = 0 ; i < nbjoueurs ; i++) cout << J[i]->nom << ": " << S[i] << endl;
            cout << endl;

            GainApprox(S,J,b,nbjoueurs);

            cout << "-----------------------------" << endl;
            cout << "REPARTITION DES GAINS: " << endl;

            for(int i = 0 ; i < nbjoueurs ; i++) cout << J[i]->nom << ": " << J[i]->gain << endl;
            cout << "-----------------------------" << endl;

            printf("Durée totale : %ds\n",(int)time(NULL) - start);
            timeS3 = (int)time(NULL) - start;
            vect_joueur3 = tabtovecteur(J, nbjoueurs);
            for(int i = 0 ; i < nbjoueurs; i++) free(J[i]);
        }

        resultat reswindow(this);
        reswindow.setModal(true);
        reswindow.exec();
    }
    vect_joueur.clear();
}
