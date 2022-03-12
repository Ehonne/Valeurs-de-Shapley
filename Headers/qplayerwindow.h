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
    explicit QPlayerWindow(MainWindow *dad, QWidget *parent = nullptr);
    ~QPlayerWindow();
    int nbr_player;
    vector<Joueur> vect_joueur;
public slots:
    void make();
    void save();
private:
    Ui::QPlayerWindow *ui;
};

#endif // QPLAYERWINDOW_H
