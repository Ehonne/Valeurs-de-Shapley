#include "../Headers/qplayerwindow.h"
#include "ui_qplayerwindow.h"
#include "QMessageBox"

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

void QPlayerWindow::make()
{
    int size;
    std::string::size_type sz;
   for (int i = 0; i < nbr_player; i++)
   {
       std::string temp = ui->tableWidget_player->item(i,1)->text().toStdString();
       size = temp.length();
       for (int j = 0; j < size; j++)
       {
           if (isdigit(temp[j]))
           {
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
       //number = std::stod(temp,&sz);
       //vect_init.push_back(number); //recuperation des données saisies dans l'objet addvectwindow
    }
}
