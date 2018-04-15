#ifndef CHARDATA_H
#define CHARDATA_H

#include <QtCore>
#include <QJsonObject>
#include <QVector>

#include "jsonclasses.h"
#include "texwriter.h"



class AnimalData : public QJsonObject
{

public:
    AnimalData();
    AnimalData(const QJsonObject &);
    AnimalData(const AnimalData &);
    QString toTexMinipageString();

    static void createEmptyAnimalFile(QString filename);
    static QVector<AnimalData> loadAnimalFile(QString filename);

    QJsonObject & obj(){return (*this);}
    QJsonObject obj(const QString &str){return obj()[str].toObject();}
};


#endif // CHARDATA_H
