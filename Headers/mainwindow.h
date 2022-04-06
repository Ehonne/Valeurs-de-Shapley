#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include "../Headers/joueur.h"
#include "../Headers/loadwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QDialog
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int number_player;
    int state = 0;
    vector<Joueur> vect_player;
    Boss b;
public slots:
    void make();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
