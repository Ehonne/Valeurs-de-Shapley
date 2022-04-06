#ifndef RESULTAT_H
#define RESULTAT_H

#include <QDialog>
#include "../Headers/joueur.h"
#include "../Headers/qplayerwindow.h"

namespace Ui {
class resultat;
}

class resultat : public QDialog
{
    Q_OBJECT

public:
    explicit resultat(QPlayerWindow *dad, QWidget *parent = nullptr);
    ~resultat();
    vector<Joueur> vect_joueurs;
    float timeS1 = 0.0;
    float timeS2 = 0.0;
    float timeS3 = 0.0;
public slots:
    void Exit();
    void save();
private:
    Ui::resultat *ui;
};

#endif // RESULTAT_H
