#include "sponsors.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QSqlError>
Sponsors::Sponsors()
{
  ID_SPONSOR=0;
  NUM_CONTRAT=0;
  CATEGORY="";
  DURE_CONTRAT="";
  NOM="";
}

Sponsors::Sponsors(int ID_SPONSOR,int NUM_CONTRAT,QString CATEGORY,QString DURE_CONTRAT,QString NOM)
{this->ID_SPONSOR=ID_SPONSOR;
 this->NUM_CONTRAT=NUM_CONTRAT;
 this->CATEGORY=CATEGORY;
 this->DURE_CONTRAT=DURE_CONTRAT;
 this->NOM=NOM;
}

int Sponsors::getID_SPONSOR(){return  ID_SPONSOR;}
int Sponsors::getNUM_CONTRAT(){return  NUM_CONTRAT;}
QString Sponsors::getCATEGORY(){return  CATEGORY;}
QString Sponsors::getDURE_CONTRAT(){return  DURE_CONTRAT;}
QString Sponsors::getNOM(){return  NOM;}
void Sponsors::setID_SPONSOR(int ID_SPONSOR){this->ID_SPONSOR=ID_SPONSOR;}
void Sponsors::setNUM_CONTRAT(int NUM_CONTRAT){this->NUM_CONTRAT=NUM_CONTRAT;}
void Sponsors::setCATEGORY(QString CATEGORY){this->CATEGORY=CATEGORY;}
void Sponsors::setDURE_CONTRAT(QString DURE_CONTRAT){this->DURE_CONTRAT=DURE_CONTRAT;}
void Sponsors::setNOM(QString NOM){this->NOM=NOM;}




bool Sponsors::ajouter() {
    QSqlQuery query;
    // Check if ID exists
    query.prepare("SELECT ID_SPONSOR FROM Sponsors WHERE ID_SPONSOR = :id_sponsor");
    query.bindValue(":id_sponsor", ID_SPONSOR);
    if (query.exec() && query.next()) {
        // ID already exists
        int existingID = query.value(0).toInt();
        QMessageBox::warning(nullptr, "Duplicate ID", "The ID " + QString::number(existingID) + " already exists in the table.");
        return false;
    }

    // Check if NUM_CONTRAT exists
    query.prepare("SELECT NUM_CONTRAT FROM Sponsors WHERE NUM_CONTRAT = :num_contrat");
    query.bindValue(":num_contrat", NUM_CONTRAT);
    if (query.exec() && query.next()) {
        // NUM_CONTRAT already exists
        int existingNumContrat = query.value(0).toInt();
        QMessageBox::warning(nullptr, "Duplicate NUM_CONTRAT", "The NUM_CONTRAT " + QString::number(existingNumContrat) + " already exists in the table.");
        return false;
    }

    // Neither ID nor NUM_CONTRAT exists, proceed with insertion
    query.prepare("INSERT INTO Sponsors (ID_SPONSOR, NUM_CONTRAT, CATEGORY, DURE_CONTRAT, NOM) "
                  "VALUES (:id_sponsor, :num_contrat, :category, :dure_contrat, :nom)");
    query.bindValue(":id_sponsor", ID_SPONSOR);
    query.bindValue(":num_contrat", NUM_CONTRAT);
    query.bindValue(":category", CATEGORY);
    query.bindValue(":dure_contrat", DURE_CONTRAT);
    query.bindValue(":nom", NOM);

    return query.exec();
}




QSqlQueryModel* Sponsors::afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM SPONSORS");


    model->setHeaderData(0, Qt::Horizontal, QObject::tr("IDSPONSOR"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NUMCONTRAT"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("CATEGORY"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DURECONTRAT"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("NOM"));

    return model;
}
bool Sponsors::supprimer(int ID_SPONSOR)
{
    QSqlQuery query;
    query.prepare("SELECT ID_SPONSOR FROM SPONSORS WHERE ID_SPONSOR = :ID_SPONSOR");
    query.bindValue(":ID_SPONSOR", ID_SPONSOR);
    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError().text();

        return false;
    }
    if (!query.next()) {
        qDebug() << "ID_SPONSOR not found in the table";
        return false;
    }

    query.prepare("DELETE FROM SPONSORS WHERE ID_SPONSOR = :ID_SPONSOR");
    query.bindValue(":ID_SPONSOR", ID_SPONSOR);
    if (!query.exec()) {
        qDebug() << "Error deleting entry:" << query.lastError().text();
        return false;
    }

    return true;
}

bool Sponsors::modifier(int ID_SPONSOR, int newID, int newNumContrat, const QString& newCategory, const QString& newDureContrat, const QString& newNom) {
    QSqlQuery query;
    query.prepare("SELECT ID_SPONSOR FROM Sponsors WHERE ID_SPONSOR = :id_sponsor");
    query.bindValue(":id_sponsor", ID_SPONSOR);
    if (query.exec() && query.next()) {
        // ID_SPONSOR exists, proceed with modification
        query.prepare("UPDATE Sponsors SET ID_SPONSOR = :new_id, NUM_CONTRAT = :new_num_contrat, CATEGORY = :category, DURE_CONTRAT = :dure_contrat, NOM = :nom WHERE ID_SPONSOR = :id_sponsor");
        query.bindValue(":new_id", newID);
        query.bindValue(":new_num_contrat", newNumContrat);
        query.bindValue(":category", newCategory);
        query.bindValue(":dure_contrat", newDureContrat);
        query.bindValue(":nom", newNom);
        query.bindValue(":id_sponsor", ID_SPONSOR);
        return query.exec();
    } else {
        // ID_SPONSOR doesn't exist
        return false;
    }
}

Sponsors Sponsors::getSponsorByID(int ID_SPONSOR)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM SPONSORS WHERE ID_SPONSOR = :ID_SPONSOR");
    query.bindValue(":ID_SPONSOR", ID_SPONSOR);
    query.exec();

    Sponsors sponsor;
    if (query.next()) {
        sponsor.setID_SPONSOR(query.value(0).toInt());
        sponsor.setNUM_CONTRAT(query.value(1).toInt());
        sponsor.setCATEGORY(query.value(2).toString());
        sponsor.setDURE_CONTRAT(query.value(3).toString());
        sponsor.setNOM(query.value(4).toString());
    }
    return sponsor;
}


QSqlQueryModel* Sponsors::rankingByNumContrat() {
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM Sponsors ORDER BY NUM_CONTRAT");
    return model;
}





