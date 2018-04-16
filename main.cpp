#include <QCoreApplication>
#include "chardata.h"

int main(int argc, char *argv[])
{
    QTextStream out(stdout);
    if (argc !=3)
    {
        out << "Usage: \n\nArxJson2PDF [filename.animal.json] [TexFilename.tex]\n\n\n";
    }else {
        QString inFile(argv[1]);
        QString outFile(argv[2]);
        out << "Loading file: " << inFile << "\n";
        QVector<AnimalData> animals = AnimalData::loadAnimalFile("Animal_Template.Animal.json");
        //TODO verify Data
        if (animals.size()>0)
        {
            out << "...Done!\n";
        }else{
            out << "File error or empty! ... \n";
            return 1;
        }
        out << "Writing Tex file: " << outFile << "\n";
        AnimalData::createTexFileFromAnimalDataArray(animals,outFile);
        out << "...Done!\n\n";
    }
    return 0;
}
