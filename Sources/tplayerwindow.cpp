#include "../Headers/tplayerwindow.h"
#include "ui_tplayerwindow.h"
#include "../Headers/mainwindow.h"

TPlayerWindow::TPlayerWindow(MainWindow *dad, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TPlayerWindow)
{
    ui->setupUi(this);
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
}

TPlayerWindow::~TPlayerWindow()
{
    delete ui;
}
