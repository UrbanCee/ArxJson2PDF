#include "chardata.h"
#include <QDebug>

void AnimalData::createEmptyAnimalFile(QString filename)
{
    QJsonObject metaData=readJson("MetaData_Animals.Arx.json");
    if (metaData.isEmpty())
    {
        qDebug()<<"Error reading meta Data";
        return;
    }
    QJsonObject data;
    data.insert("Name","InsertNameHere");
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

    qDebug() << data.contains("Weitere Werte");

    writeJson(filename,data);

}
