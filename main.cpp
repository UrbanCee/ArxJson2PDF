#include <QCoreApplication>
#include "chardata.h"

int main(int argc, char *argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);
    QString MetaFilename="MetaData_Animals.Arx.json";

    //AnimalData::createEmptyAnimalFile("Animal_Template.Animal.json");

    QVector<AnimalData> animals = AnimalData::loadAnimalFile("Animal_Template.Animal.json");

    QFile outFile( "test.tex" );
    if ( !outFile.open(QIODevice::WriteOnly) )
    {
        qDebug() << "Error writing!\n";
        return false;
    }

    outFile.write(animals[0].toTexMinipageString().toUtf8());

    //out << "Usage: ArxJson2PDF filename.animal.json TexFilename.tex\n";
    return 0;
}
