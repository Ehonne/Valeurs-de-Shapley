#include "../Headers/mainwindow.h"
#include "ui_mainwindow.h"
#include "../Headers/tplayerwindow.h"
#include "../Headers/qplayerwindow.h"
#include "../Headers/loadwindow.h"

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
    QPlayerWindow secwind(this);
    secwind.setModal(true);
    secwind.exec();
}


