#ifndef CHARDATA_H
#define CHARDATA_H

#include <QtCore>
#include <QJsonObject>

#include "jsonclasses.h"

class AnimalData : public QJsonObject
{
public:
    static void createEmptyAnimalFile(QString filename);
};


#endif // CHARDATA_H
