#include "../Headers/loadwindow.h"
#include "ui_loadwindow.h"
#include "iostream"
#include "QMessageBox"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

loadwindow::loadwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loadwindow)
{
    ui->setupUi(this);
    state = 0;
    QObject::connect(ui->PushButton_valide, SIGNAL(clicked()), this, SLOT(Validate()));
    QObject::connect(ui->Button_cancel, SIGNAL(clicked()), this, SLOT(Cancel()));
}

loadwindow::~loadwindow()
{
    delete ui;
}

void loadwindow::Validate()
{
    std::string path = ui->LineEdit_location->text().toStdString();
    char chemin[path.length()+1];
    strcpy(chemin, path.c_str());
    strcat(chemin,".txt");
    string line;
      ifstream myfile (chemin);
      if (myfile.is_open())
      {
        getline(myfile,line);
        nbr_player = std::atoi(line.c_str());
        for(int i = 0; i < nbr_player; i++)
        {
          getline(myfile,line);
          Joueur J = Joueur();
          int j = 0;
          string name = "";
          while(line[j] != ' ')
          {
              name.push_back(line[j]);
              j++;
          }
          J.nom = name;
          j++;
          string degat = "";
          while(line[j] != ' ')
          {
              degat.push_back(line[j]);
              j++;
          }
          J.degats = std::atoi(degat.c_str());
          cout << line << '\n';
          vect_player.push_back(J);
        }
        //On arrive au boss
        getline(myfile,line);
        int j=0;
        string name = "";
        while(line[j] != ' ')
        {
            name.push_back(line[j]);
            j++;
        }
        b.nom = name;
        j++;
        string xp = "";
        while(line[j] != ' ')
        {
            xp.push_back(line[j]);
            j++;
        }
        b.xp = std::atoi(xp.c_str());
        j++;
        string hp = "";
        while(line[j] != ' ')
        {
            hp.push_back(line[j]);
            j++;
        }
        b.hp = std::atoi(hp.c_str());
        cout << line << '\n';
        myfile.close();
      }

      else
      {
          QMessageBox::critical(this, "Entry error", "Le fichier ne peut pas etre ouvert.");
          vect_player.clear();
          state = 1;
      }
      if(nbr_player != (int)vect_player.size())
      {
          QMessageBox::critical(this, "Entry error", "Le contenue du fichier n'est pas correcte");
          vect_player.clear();
          state = 1;
      }
      else
      close();
}

void loadwindow::Cancel()
{
    state = 1;
    close(); //end of the window
}

