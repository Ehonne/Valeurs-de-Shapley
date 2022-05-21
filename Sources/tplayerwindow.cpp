#include "../Headers/tplayerwindow.h"
#include "ui_tplayerwindow.h"
#include "../Headers/mainwindow.h"
#include "../Headers/joueur.h"
#include "../Headers/resultat.h"

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
}
