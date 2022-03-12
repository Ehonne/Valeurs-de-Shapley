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
    QObject::connect(ui->pushButton_load, SIGNAL(clicked()), this, SLOT(load()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::make()
{
    if(state == 0)
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

void MainWindow::load()
{
    loadwindow secwind(this);
    secwind.setModal(true);
    secwind.exec();
    std::cout << "nbrplayer: " << secwind.nbr_player << endl;
    for (Joueur i: secwind.vect_player)
        std::cout << i.toString() << endl;
    std::cout << secwind.b.nom << secwind.b.xp << secwind.b.hp << endl;
    number_player = secwind.nbr_player;
    vect_player = secwind.vect_player;
    b = secwind.b;
    state = 1;
    make();
}
