#ifndef DATAREADER_H
#define DATAREADER_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <vector>
#include "glm/glm.hpp"
#include "Scene.h"
#include "ObjectFactory.h"


class DataReader {
public:
    explicit DataReader();

    DataReader(Scene *s);

    void readFile (QString fileName);

    float xmin, zmin, xmax, zmax;

protected:
    virtual void fileLineRead (QString lineReaded);

    Scene *scene;

    void baseFound(QStringList list);

    void limitsFound(QStringList list);

    void propFound(QStringList list);

    void dataFound(QStringList list);

private:
    int numProp;
    vector<ObjectFactory::OBJECT_TYPES> props;
    float props_data[10];
    float proporcio;
};

#endif // DataReader_H
