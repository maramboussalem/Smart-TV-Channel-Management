#ifndef SPONSORS_H
#define SPONSORS_H
#include <QString>
#include <QMessageBox>
#include <QDate>
#include <QSqlQuery>
#include <QSqlQueryModel>
class Sponsors
{
public:
    Sponsors();
    Sponsors(int,int,QString,QString,QString);
    int getID_SPONSOR();
    int getNUM_CONTRAT();
    QString getCATEGORY();
    QString getDURE_CONTRAT();
    QString getNOM();
    void setID_SPONSOR(int);
    void setNUM_CONTRAT(int);
    void setCATEGORY(QString);
    void setDURE_CONTRAT(QString);
    void setNOM(QString);
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    bool modifier(int ID_SPONSOR, int newID, int newNumContrat, const QString& newCategory, const QString& newDureContrat, const QString& newNom);
   Sponsors getSponsorByID(int ID_SPONSOR);
   QSqlQueryModel* rankingByNumContrat();




private:
    int ID_SPONSOR, NUM_CONTRAT ;
    QString CATEGORY, DURE_CONTRAT, NOM;
};

#endif // SPONSORS_H
