#ifndef TPLAYERWINDOW_H
#define TPLAYERWINDOW_H

#include <QDialog>
#include "mainwindow.h"
#include "../Headers/joueur.h"
#include "../Headers/qplayerwindow.h"

namespace Ui {
class TPlayerWindow;
}

class TPlayerWindow : public QDialog
{
    Q_OBJECT

public:
    explicit TPlayerWindow(QPlayerWindow *dad, QWidget *parent = nullptr);
    ~TPlayerWindow();
    vector<Joueur> vect_player;
    int nbr_player;
    Boss b;
    int state = 0;
public slots:
    void Execute();
    void Cancel();
private:
    Ui::TPlayerWindow *ui;
};

#endif // TPLAYERWINDOW_H
