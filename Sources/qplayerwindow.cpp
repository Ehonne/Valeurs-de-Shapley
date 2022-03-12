#include "../Headers/qplayerwindow.h"
#include "ui_qplayerwindow.h"
#include "QMessageBox"
#include "../Headers/joueur.h"

QPlayerWindow::QPlayerWindow(MainWindow *dad, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QPlayerWindow)
{
    ui->setupUi(this);
    ui->tableWidget_player->setRowCount(dad->number_player);
    nbr_player = dad->number_player;

    QObject::connect(ui->pushButton_E, SIGNAL(clicked()), this, SLOT(make()));



}

QPlayerWindow::~QPlayerWindow()
{
    delete ui;
}
void QPlayerWindow::save()
{
}

void QPlayerWindow::make()
{
    int size;
    std::string::size_type sz;
   for (int i = 0; i < nbr_player; i++)
   {
       std::string temp = ui->tableWidget_player->item(i,1)->text().toStdString();
       std::string nam = ui->tableWidget_player->item(i,0)->text().toStdString();
       size = temp.length();
       for (int j = 0; j < size; j++)
       {
           if (!isdigit(temp[j]))
           {
               cout << temp[j] << endl;
               QMessageBox::critical(this, "Entry error", "Dégat doit etre un entier.");
               //vect_init.clear();
               return;
           }
           if(ui->tableWidget_player->item(i,0)->text().isEmpty())
           {
               QMessageBox::critical(this, "Entry error", "Missing name for your player.");
               //vect_init.clear();
               return;
           }
       }
       Joueur J1 = Joueur(nam,std::stoi(temp));
       std::cout << J1.nom << " - " << J1.degats << endl;
       vect_joueur.push_back(J1); //recuperation des données saisies dans l'objet addvectwindow
    }
}
