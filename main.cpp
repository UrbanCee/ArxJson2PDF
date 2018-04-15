#include <QCoreApplication>
#include "chardata.h"

int main(int argc, char *argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);
    QString MetaFilename="MetaData_Animals.Arx.json";

    AnimalData::createEmptyAnimalFile("Animal_Template.Animal.json");

    //out << "Usage: ArxJson2PDF filename.animal.json TexFilename.tex\n";
    return 0;
}
