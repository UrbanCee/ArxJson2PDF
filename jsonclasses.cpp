#include <jsonclasses.h>
#include <QtCore>
#include <QDebug>

bool writeJson(QString filename, QJsonObject object)
{
    QFile outFile( filename );
    if ( !outFile.open(QIODevice::WriteOnly) )
    {
        QTextStream out(stdout);
        out << "Error writing " << filename << "!\n";
        qDebug() << "Error writing " << filename << "!\n";
        return false;
    }

    outFile.write(QJsonDocument(object).toJson());
    return true;
}


QJsonObject readJson(QString filename)
{
    QFile inFile( filename );
    QTextStream out(stdout);
    if ( !inFile.open(QIODevice::ReadOnly) )
    {
        QTextStream out(stdout);
        //qDebug() << "Error reading " << filename << "!\n";
        out << "Error reading " << filename << "!\n";
        return QJsonObject();
    }
    QJsonParseError error;
    QJsonDocument doc=QJsonDocument::fromJson(inFile.readAll(),&error);
    if (error.error==QJsonParseError::NoError){
        return QJsonObject(doc.object());
    }
    //qDebug() << "Error parsing" << filename << "!\n";
    //qDebug() << error.errorString();
    out << "Error parsing " << filename << "!\n";
    out << error.errorString();
    return QJsonObject();


}
