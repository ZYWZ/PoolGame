#include "stagethreefactory.h"
#include <qDebug>

Table* StageThreeFactory::makeTable(const QJsonObject& tableData) {

    // create a stage one table based on the fed in json data
    QString colour = tableData.value("colour").toString();

    // extract width and height from json vals
    QJsonObject tSize = tableData.value("size").toObject();
    double width = tSize.value("x").toDouble();
    double height = tSize.value("y").toDouble();

    double friction = tableData.value("friction").toDouble();

    // pockets are not added in yet.
    return new StageThreeTable(width, height, QColor(colour), friction);
}
