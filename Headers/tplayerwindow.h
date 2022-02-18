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

private:
    Ui::TPlayerWindow *ui;
};

#endif // TPLAYERWINDOW_H
