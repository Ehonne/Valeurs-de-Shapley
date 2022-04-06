#ifndef TPLAYERWINDOW_H
#define TPLAYERWINDOW_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class TPlayerWindow;
}

class TPlayerWindow : public QDialog
{
    Q_OBJECT

public:
    explicit TPlayerWindow(MainWindow *dad, QWidget *parent = nullptr);
    ~TPlayerWindow();
    int nbrplayer;
    vector<Joueur> vect_joueur;
public slots:
    void Execute();
    void Save();
private:
    Ui::TPlayerWindow *ui;
};

#endif // TPLAYERWINDOW_H
