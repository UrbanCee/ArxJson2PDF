#include "chardata.h"
#include <QDebug>

QVector<AnimalData> AnimalData::loadAnimalFile(QString filename)
{
    QVector<AnimalData> animals;
    QJsonObject fileObject=readJson(filename);
    if (!fileObject["Tiere"].isArray())
    {
        qDebug() << "No Arrow unter \"Tiere\" - Key ";
        return animals;
    }
    QJsonArray animalArray = fileObject["Tiere"].toArray();
    int iIndex=0;
    for (QJsonArray::const_iterator it=animalArray.begin();it!=animalArray.end();it++)
    {
        if (!((*it).isObject()))
        {
            qDebug() << "Object #" << iIndex << "is not a JsonObject!";
            return animals;
        }
        iIndex++;
        animals.append(AnimalData((*it).toObject()));
    }
    return animals;
}


AnimalData::AnimalData():QJsonObject(){}
AnimalData::AnimalData(const QJsonObject &obj):QJsonObject(obj){}
AnimalData::AnimalData(const AnimalData &anim):QJsonObject(anim){}

QString AnimalData::toTexMinipageString()
{
    QJsonObject metaData = readJson(":/res/MetaData_Animals.Arx.json");
    QString str;
    str.append(QString("\\vspace{0.2cm}{\\hspace{1cm}\\large\\textbf{%1}}\n\n\\vspace{0.2cm}\n").arg(obj()["Name"].toString()));
    str.append("\\begin{minipage}{0.48\\textwidth}\\centering\n\\renewcommand{\\arraystretch}{0.9}\n\\begin{tabular}{ll}\n");
    for (QJsonObject::iterator it=obj("Attribute").begin();it!=obj("Attribute").end();it++)
    {
        str.append(Tex::animalAttrib(it.key(),it.value().toInt()));
    }
    str.append("&\\\\[-1ex]");
    str.append(Tex::animalAttrib("Lebensblock",obj("Weitere Werte")["Lebensblock"].toInt()));
    str.append(Tex::animalAttrib("Ausdauerblock",obj("Weitere Werte")["Ausdauerblock"].toInt()));
    str.append(Tex::animalAttrib("Manablock",obj("Weitere Werte")["Manablock"].toInt()));
    str.append("&\\\\[-1ex]");
    str.append(Tex::animalAttrib("Vorkommen",obj("Weitere Werte")["Vorkommen"].toInt()));
    str.append("\\end{tabular}\\end{minipage}\n");

    str.append("\\begin{minipage}{0.48\\textwidth}\\flushleft\n\\begin{tabular}{|l|}\\hline\n"
               "\\\\[-2.2ex]\n"
               "\\multicolumn{1}{|c|}{\\textbf{Besondere Fähigkeiten}}\\\\\\hline\n");
    QJsonArray specials = obj()["Besondere Fähigkeiten"].toArray();
    for (int i=0;i<11;i++)
    {
        if (i<specials.size())
            str.append(QString("%1\\\\\n").arg(specials[i].toString()));
        else
            str.append("\\\\\n");
    }
    str.append("\\hline\\end{tabular}\\end{minipage}\n\n\\vspace{0.3cm}");

    str.append("\\begin{minipage}{0.4\\textwidth}\\begin{tabular}{|l|r@{\\em}c@{\\em}l|}\\hline\n");
    str.append("\\multicolumn{4}{|c|}{ }\\\\[-2.2ex]\n");
    str.append("\\multicolumn{4}{|c|}{\\textbf{Weitere Werte}}\\\\\\hline\n");
    str.append("&&&\\\\[-2.5ex]\n");
    str.append(Tex::animalSpecial("LL",obj("Weitere Werte")["Laufleistung einfach"].toInt(),obj("Weitere Werte")["Laufleistung voll"].toInt()));
    str.append(Tex::animalSpecial(QString("SL"),obj("Weitere Werte")["Schwimmleistung einfach"].toInt(),obj("Weitere Werte")["Schwimmleistung voll"].toInt()));
    str.append(Tex::animalSpecial(QString("FL"),obj("Weitere Werte")["Flugleistung einfach"].toInt(),obj("Weitere Werte")["Flugleistung voll"].toInt()));
    str.append(Tex::animalSpecial(QString("TK"),obj("Weitere Werte")["Tragkraft einfach"].toInt(),obj("Weitere Werte")["Tragkraft voll"].toInt()));
    str.append(Tex::animalSpecial(QString("SK/ZG"),obj("Weitere Werte")["Stemmkraft"].toInt(),obj("Weitere Werte")["Zugkraft"].toInt()));
    str.append(QString("GF:&\\multicolumn{3}{c|}{%1}\\\\\\hline\n").arg(obj("Weitere Werte")["Geistige Festigkeit"].toInt()));
    str.append(QString("Mres:&\\multicolumn{3}{c|}{%1}\\\\\\hline\n").arg(obj("Weitere Werte")["Magieresistenz"].toInt()));
    str.append(QString("Mren:&\\multicolumn{3}{c|}{%1}\\\\\\hline\n").arg(obj("Weitere Werte")["Magierenitenz"].toInt()));
    str.append("&&&\\\\[-2.5ex]\\hline\n&&&\\\\[-2.5ex]\n");
    str.append(Tex::animalSpecial(QString("RsN/RsM"),obj("Weitere Werte")["Rüstungsschutz natürlich"].toInt(),obj("Weitere Werte")["Rüstungsschutz magisch"].toInt()));
    str.append("&&&\\\\[-2.5ex]\n");
    str.append(Tex::animalSpecial(QString("AvR/BM"),obj("Weitere Werte")["Ausdauerverbrauch Rüstung"].toInt(),obj("Weitere Werte")["Bewegungsmalus"].toInt()));
    str.append("\\end{tabular}\\end{minipage}\n");

    str.append("\\begin{minipage}{0.4\\textwidth}\\begin{tabular}{|l@{\\hskip 0.5em}r@{\\em}c@{\\em}l|}\\hline\n");
    str.append("&&&\\\\[-2.2ex]\n");
    str.append("\\multicolumn{4}{|c|}{\\textbf{Fertigkeiten}}\\\\\\hline\n&&&\\\\[-2.5ex]");

    QJsonObject skills = obj("Fertigkeiten");
    int iFillerLines=0;
    for (QJsonObject::iterator it=skills.begin();it!=skills.end();it++)
    {
        QJsonObject skillObj=it.value().toObject();
        if (skillObj["Stock"].toInt()>0){
            str.append("\n");
            str.append(Tex::animalSkills(it.key(),skillObj["Stock"].toInt(),skillObj["FP"].toInt()));
        }
        else
            iFillerLines++;
    }
    for (int i=0;i<iFillerLines;i++)
        str.append("\n&&&\\\\");


    str.append("[-2.8ex]\n\\phantom{Wahrnehmung}&\\phantom{99}&\\phantom{+}&\\phantom{\\scriptsize W12+2W6+W4}\\\\\\hline\\end{tabular}\\end{minipage}");


    return Tex::embedIntoDocument(Tex::quarterPageMiniSetup(str));
}

void AnimalData::createEmptyAnimalFile(QString filename)
{
    QJsonObject metaData=readJson(":/res/MetaData_Animals.Arx.json");
    if (metaData.isEmpty())
    {
        qDebug()<<"Error reading meta Data";
        return;
    }
    QJsonObject data;
    data.insert("Name",QString("NameOfAnimal"));
    QJsonObject attributes;
    QJsonArray attrNames = metaData["Attribute"].toArray();
    for (QJsonArray::const_iterator it=attrNames.begin();it!=attrNames.end();it++)
    {
        attributes.insert((*it).toString(),6);
    }
    data.insert("Attribute",attributes);

    QJsonObject additionalData;
    QJsonArray additionalDataMeta = metaData["Weitere Werte"].toArray();
    for (QJsonArray::const_iterator it=additionalDataMeta.begin();it!=additionalDataMeta.end();it++)
    {
        additionalData.insert((*it).toString(),0);
    }
    data.insert("Weitere Werte",additionalData);

    QJsonArray specials;
    specials.append("Dunkelsicht");
    specials.append("Kälteschutz IV");
    data.insert("Besondere Fähigkeiten",specials);

    QJsonObject skills;
    QJsonArray skillNames = metaData["Fertigkeiten"].toArray();
    for (QJsonArray::const_iterator it=skillNames.begin();it!=skillNames.end();it++)
    {
        QJsonObject skill;
        skill.insert("Stock",0);
        skill.insert("FP",0);
        skills.insert((*it).toString(),skill);
    }
    data.insert("Fertigkeiten",skills);

    QJsonArray weapons;
    QJsonObject weapon;

    QJsonArray weaponValues= metaData["Kampfwerte"].toArray();
    for (QJsonArray::const_iterator it=weaponValues.begin();it!=weaponValues.end();it++)
    {
        weapon.insert((*it).toString(),0);
    }
    weapon.insert("Name","Waffe 1");
    weapon.insert("Initiative Würfel","W6");
    weapon.insert("Schaden Würfel","2W4");
    weapons.append(weapon);
    weapon.insert("Name","Waffe 2");
    weapons.append(weapon);
    data.insert("Kampfwerte",weapons);

    QJsonArray animalArray;
    animalArray.append(data);
    animalArray.append(data);

    QJsonObject animals;
    animals.insert("Tiere",animalArray);

    writeJson(filename,animals);

}

