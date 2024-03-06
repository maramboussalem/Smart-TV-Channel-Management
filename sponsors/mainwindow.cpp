#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sponsors.h"
#include <QtDebug>
#include <QMessageBox>
#include <QIntValidator>
#include <QSqlRecord>
#include <QModelIndex>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    S() // Initialize Sponsors object
{
    ui->setupUi(this);
    ui->lineEdit->setValidator(new QIntValidator(0, 9999999, this));

    // Fetch and populate ID_SPONSOR values into the combo box
    QSqlQueryModel* model = S.afficher();
    for (int i = 0; i < model->rowCount(); ++i) {
        int id = model->record(i).value("ID_SPONSOR").toInt();
        ui->comboBox_ID_SPONSOR->addItem(QString::number(id));
    }
    delete model; // Clean up model
    ui->tableView->setModel(S.afficher());
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_button_ajouter_clicked()
{
    QString id_sponsor_str = ui->lineEdit->text();
    QString num_contrat_str = ui->lineEdit_5->text();

    // Validate ID_SPONSOR
    QIntValidator idValidator(1, 9999999, this);
    int pos = 0;
    if (idValidator.validate(id_sponsor_str, pos) != QValidator::Acceptable) {
        QMessageBox::warning(this, "Invalid Input", "ID_SPONSOR must be a positive integer between 1 and 9999999.");
        return;
    }

    // Validate NUM_CONTRAT
    if (idValidator.validate(num_contrat_str, pos) != QValidator::Acceptable) {
        QMessageBox::warning(this, "Invalid Input", "NUM_CONTRAT must be a positive integer between 1 and 9999999.");
        return;
    }

    int ID_SPONSOR = id_sponsor_str.toInt();
    int NUM_CONTRAT = num_contrat_str.toInt();
    QString CATEGORY = ui->lineEdit_9->text();
    QString DURE_CONTRAT = ui->lineEdit_2->text();
    QString NOM = ui->lineEdit_4->text();

    Sponsors S(ID_SPONSOR, NUM_CONTRAT, CATEGORY, DURE_CONTRAT, NOM);
    if(S.ajouter())
    {
        qDebug() << "Insertion successful";
        QMessageBox::information(this, "Insertion Successful", "New sponsor has been added successfully.");
         ui->tableView->setModel(S.afficher());
         ui->lineEdit->clear();
         ui->lineEdit_5->clear();
         ui->lineEdit_9->clear();
         ui->lineEdit_2->clear();
         ui->lineEdit_4->clear();

        // Optionally, you can add code here to update UI or show a success message.

         // Update the combo box after insertion
                ui->comboBox_ID_SPONSOR->clear();
                QSqlQueryModel* model = S.afficher();
                for (int i = 0; i < model->rowCount(); ++i) {
                    QSqlRecord record = model->record(i);
                    int id = record.value("ID_SPONSOR").toInt();
                    ui->comboBox_ID_SPONSOR->addItem(QString::number(id));
                }
                delete model; // Clean up model




    }
    else
    {
        qDebug() << "Failed to insert data";
        // Optionally, you can add code here to show an error message.
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    close();
}

void MainWindow::on_deleteBut_clicked()
{
    int ID_SPONSOR = ui->id_del->text().toInt();
    bool deleted = S.supprimer(ID_SPONSOR);
    if (deleted) {
        qDebug() << "Suppression successful";
       QMessageBox::information(this, "Delete Successful", "Entry with ID_SPONSOR " + QString::number(ID_SPONSOR) + " has been deleted successfully.");
        ui->tableView->setModel(S.afficher());
        // Update the combo box after insertion
               ui->comboBox_ID_SPONSOR->clear();
               QSqlQueryModel* model = S.afficher();
               for (int i = 0; i < model->rowCount(); ++i) {
                   QSqlRecord record = model->record(i);
                   int id = record.value("ID_SPONSOR").toInt();
                   ui->comboBox_ID_SPONSOR->addItem(QString::number(id));
               }
               delete model; // Clean up model

    } else {
        qDebug() << "Failed to delete entry";
        QMessageBox::warning(this, "Delete Entry", "ID_SPONSOR not found in the table");
    }
}

void MainWindow::on_modifyButton_clicked()
{
    int ID_SPONSOR = ui->id_modify_2->text().toInt();
    int newID = ui->newID->text().toInt();
    int newNumContrat = ui->newNumContrat->text().toInt();
    QString newCategory = ui->newCategory->text();
    QString newDureContrat = ui->newDureContrat->text();
    QString newNom = ui->newNom->text();

    bool modified = S.modifier(ID_SPONSOR, newID, newNumContrat, newCategory, newDureContrat, newNom);
    if (modified) {
        qDebug() << "Modification successful";
        QMessageBox::information(this, "Modification Successful", "Entry with ID_SPONSOR " + QString::number(ID_SPONSOR) + " has been modified successfully.");

        // Update the combobox contents
        ui->comboBox_ID_SPONSOR->clear();
        QSqlQueryModel* model = S.afficher();
        for (int i = 0; i < model->rowCount(); ++i) {
            int id = model->record(i).value("ID_SPONSOR").toInt();
            ui->comboBox_ID_SPONSOR->addItem(QString::number(id));
        }
        delete model; // Clean up model

        // Update the table view
        ui->tableView->setModel(S.afficher());
    } else {
        qDebug() << "Failed to modify entry";
        QMessageBox::warning(this, "Modification Failed", "Failed to modify entry with ID_SPONSOR " + QString::number(ID_SPONSOR));
    }
}


void MainWindow::on_showButton_clicked()
{
    int ID_SPONSOR = ui->id_modify_2->text().toInt();
    Sponsors sponsor = S.getSponsorByID(ID_SPONSOR);
    if (sponsor.getID_SPONSOR() == 0) {
            // ID does not exist
            QMessageBox::warning(this, "ID Not Found", "Sponsor with the entered ID does not exist.");
        } else {
    // Display each attribute in its respective line edit widget
    ui->newID->setText(QString::number(sponsor.getID_SPONSOR()));
    ui->newNumContrat->setText(QString::number(sponsor.getNUM_CONTRAT()));
    ui->newCategory->setText(sponsor.getCATEGORY());
    ui->newDureContrat->setText(sponsor.getDURE_CONTRAT());
    ui->newNom->setText(sponsor.getNOM());}
}

void MainWindow::on_Reset_clicked()
{
    ui->newID->clear();
    ui->newNumContrat->clear();
    ui->newCategory->clear();
    ui->newDureContrat->clear();
    ui->newNom->clear();
}

void MainWindow::on_Reset_2_clicked()
{
    ui->newID->clear();
    ui->lineEdit->clear();
    ui->lineEdit_5->clear();
    ui->lineEdit_9->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_4->clear();
}

void MainWindow::on_ranking_clicked()
{
    ui->tableView->setModel(S.rankingByNumContrat());
}
