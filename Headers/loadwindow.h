#ifndef LOADWINDOW_H
#define LOADWINDOW_H

#include <QDialog>
#include "../Headers/joueur.h"

namespace Ui {
class loadwindow;
}
typedef struct Boss{
    string nom;
    int hp;
    int xp;
} boss;
class loadwindow : public QDialog
{
    Q_OBJECT

public:
    explicit loadwindow(QWidget *parent = nullptr);
    ~loadwindow();
    vector<Joueur> vect_player;
    int nbr_player;
    Boss b;
    int state = 0;

public slots:
    void Validate(); //Button for validation
    void Cancel();  // Button for cancel

private:
    Ui::loadwindow *ui;
};

#endif // LOADWINDOW_H
