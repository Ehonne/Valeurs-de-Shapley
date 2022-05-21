#ifndef QPLAYERWINDOW_H
#define QPLAYERWINDOW_H

#include <QDialog>
#include "mainwindow.h"
#include "../Headers/joueur.h"
namespace Ui {
class QPlayerWindow;
}

class QPlayerWindow : public QDialog
{
    Q_OBJECT

public:
    explicit QPlayerWindow(QWidget *parent = nullptr);
    ~QPlayerWindow();
    int nbr_player;
    bool get_vect();
    Boss b;
    vector<Joueur> vect_joueur;
    vector<Joueur> vect_joueur2;
    vector<Joueur> vect_joueur3;
    float timeS1 = 0.0;
    float timeS2 = 0.0;
    float timeS3 = 0.0;
public slots:
    void make();
    void save();
    void load();
    void updatetab();
    void GenAlea();
private:
    Ui::QPlayerWindow *ui;
};

#endif // QPLAYERWINDOW_H
