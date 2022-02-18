#include "../Headers/mainwindow.h"
#include "ui_mainwindow.h"
#include "../Headers/tplayerwindow.h"
#include "../Headers/qplayerwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(make()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::make()
{
    number_player = ui->NbrJoueur->value();
    if(number_player <= 3)
    {
        TPlayerWindow secwind(this);
        secwind.setModal(true);
        secwind.exec();
    }
    else
    {
        QPlayerWindow secwind(this);
        secwind.setModal(true);
        secwind.exec();
    }
}
