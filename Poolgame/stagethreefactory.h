#ifndef STAGETHREEFACTORY_H
#define STAGETHREEFACTORY_H
#include "stagetwofactory.h"

/**
 * @brief The StageThreeFactory class inherit from stageTwoFactory, changes the makeTable function to add magnets.
 */
class StageThreeFactory : public StageTwoFactory
{
public:
    StageThreeFactory(){}

    virtual Table* makeTable(const QJsonObject& tableData) override;

};

#endif // STAGETHREEFACTORY_H
