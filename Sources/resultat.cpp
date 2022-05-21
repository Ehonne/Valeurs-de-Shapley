#include "../Headers/resultat.h"
#include "ui_resultat.h"
#include "../Headers/qplayerwindow.h"
#include "QTextDocument"
#include "QTextTable"
#include <QPrinter>
#include "QMessageBox"
#include <math.h>

resultat::resultat(QPlayerWindow *dad, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::resultat)
{
    ui->setupUi(this);
    ui->tableWidget->setRowCount(dad->vect_joueur.size()+1);
    for (int i=0; i<dad->vect_joueur.size(); i++)
           cout << dad->vect_joueur[i].nom << " ";
       cout<< endl;


   // cout << vect_joueurs[2].nom << endl;

    if(!dad->vect_joueur.empty())
    {
        //Temps de calcul
        QTableWidgetItem *newItemcont = new QTableWidgetItem();
                newItemcont->setData(Qt::DisplayRole,dad->timeS1);
        ui->tableWidget->setItem(0,1,newItemcont);
        for (int i = 0; i < (int)dad->vect_joueur.size(); i++) {
           int j = i+1;
            //nom du joueur
            QTableWidgetItem *newItem = new QTableWidgetItem();
                    newItem->setData(Qt::DisplayRole,QString::fromStdString(dad->vect_joueur[i].nom));
            ui->tableWidget->setItem(j,0,newItem);
            QTableWidgetItem *newItemcont = new QTableWidgetItem();
                    newItemcont->setData(Qt::DisplayRole,floor(dad->vect_joueur[i].gain * 10000.0) / 10000.0);
            ui->tableWidget->setItem(j,1,newItemcont);
        }
    }
    if(!dad->vect_joueur2.empty())
    {
        //Temps de calcul
        QTableWidgetItem *newItemcont = new QTableWidgetItem();
                newItemcont->setData(Qt::DisplayRole,dad->timeS2);
        ui->tableWidget->setItem(0,2,newItemcont);
        for (int i = 0; i < (int)dad->vect_joueur2.size(); i++) {
           int j = i+1;
            //nom du joueur
            QTableWidgetItem *newItem = new QTableWidgetItem();
                    newItem->setData(Qt::DisplayRole,QString::fromStdString(dad->vect_joueur2[i].nom));
            ui->tableWidget->setItem(j,0,newItem);
            QTableWidgetItem *newItemcont = new QTableWidgetItem();
                    newItemcont->setData(Qt::DisplayRole,floor(dad->vect_joueur2[i].gain * 10000.0) / 10000.0);
            ui->tableWidget->setItem(j,2,newItemcont);
        }
    }
    if(!dad->vect_joueur3.empty())
    {
        //Temps de calcul
        QTableWidgetItem *newItemcont = new QTableWidgetItem();
                newItemcont->setData(Qt::DisplayRole,dad->timeS3);
        ui->tableWidget->setItem(0,3,newItemcont);
        for (int i = 0; i < (int)dad->vect_joueur3.size(); i++) {
           int j = i+1;
            //nom du joueur
            QTableWidgetItem *newItem = new QTableWidgetItem();
                    newItem->setData(Qt::DisplayRole,QString::fromStdString(dad->vect_joueur3[i].nom));
            ui->tableWidget->setItem(j,0,newItem);
            QTableWidgetItem *newItemcont = new QTableWidgetItem();
                    newItemcont->setData(Qt::DisplayRole,floor(dad->vect_joueur3[i].gain * 10000.0) / 10000.0);
            ui->tableWidget->setItem(j,3,newItemcont);
        }
    }


    QObject::connect(ui->pushButton_Quite, SIGNAL(clicked()), this, SLOT(Exit()));
    QObject::connect(ui->pushButton_Save, SIGNAL(clicked()), this, SLOT(save()));
}

resultat::~resultat()
{
    delete ui;
}

void resultat::save()
{
    /*const int columns = ui->tableWidget->columnCount();
                const int rows = ui->tableWidget->rowCount();
                QTextDocument doc;
                QTextCursor cursor(&doc);
                QTextTableFormat tableFormat;
                tableFormat.setHeaderRowCount(1);
                tableFormat.setAlignment(Qt::AlignHCenter);
                tableFormat.setCellPadding(0);
                tableFormat.setCellSpacing(0);
                tableFormat.setBorder(1);
                tableFormat.setBorderBrush(QBrush(Qt::SolidPattern));
                tableFormat.clearColumnWidthConstraints();
                QTextTable *textTable = cursor.insertTable(rows + 1, columns+1, tableFormat);
                QTextCharFormat tableHeaderFormat;
                tableHeaderFormat.setBackground(QColor("#DADADA"));
                for (int i = 0; i < columns; i++) {
                    QTextTableCell cell = textTable->cellAt(0, i);
                    cell.setFormat(tableHeaderFormat);
                    QTextCursor cellCursor = cell.firstCursorPosition();
                    cellCursor.insertText(ui->tableWidget->horizontalHeaderItem(i)->data(Qt::DisplayRole).toString());
                }
                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < columns; j++) {
                        QTableWidgetItem *item = ui->tableWidget->item(i, j);
                        if (!item || item->text().isEmpty()) {
                            //ui->tableWidget->setItem(i, j, new QTableWidgetItem("0"));
                        }

                        QTextTableCell cell = textTable->cellAt(i + 1, j+1);
                        QTextCursor cellCursor = cell.firstCursorPosition();
                        cellCursor.insertText(ui->tableWidget->item(i, j)->text());
                    }
                }
                cursor.movePosition(QTextCursor::End);
                QPrinter printer(QPrinter::PrinterResolution);
                printer.setOutputFormat(QPrinter::PdfFormat);
                printer.setPaperSize(QPrinter::A4);
                printer.setOrientation(QPrinter::Landscape);
                printer.setOutputFileName("Resulat.pdf");
                doc.setDocumentMargin(0);
                doc.setTextWidth(5);
                doc.print(&printer);*/
    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOrientation(QPrinter::Landscape);
    printer.setOutputFileName("Resultat.pdf");

    QTextDocument doc;

    QString text("<table><thead>");
    text.append("<tr>");
    for (int i = 0; i < ui->tableWidget->columnCount(); i++) {
        text.append("<th>").append(ui->tableWidget->horizontalHeaderItem(i)->data(Qt::DisplayRole).toString()).append("</th>");

    }
    text.append("</tr></thead>");
    text.append("<tbody>");
    for (int i = 0; i < ui->tableWidget->rowCount(); i++) {
        text.append("<tr>");
        for (int j = 0; j < ui->tableWidget->columnCount(); j++) {
            QTableWidgetItem *item = ui->tableWidget->item(i, j);
            if (!item || item->text().isEmpty()) {
               ui->tableWidget->setItem(i, j, new QTableWidgetItem(" "));
            }
            text.append("<td>").append(ui->tableWidget->item(i, j)->text()).append("</td>");
        }
        text.append("</tr>");
    }
    text.append("</tbody></table>");
    doc.setHtml(text);
    doc.setPageSize(printer.pageRect().size());
    doc.print(&printer);
    QMessageBox::information(this, "Sauvegarde reussi", "Veuillez trouver votre fichier dans vos documents");
    return;
}

void resultat::Exit()
{
    close();
}
