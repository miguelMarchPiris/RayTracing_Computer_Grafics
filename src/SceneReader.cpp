#include "SceneReader.h"
#include <QFile>
#include <QTextStream>
#include <iostream>
#include <include/ObjectFactory.h>
#include "MaterialTextura.h"

SceneReader::SceneReader(Scene *s) {
    scene = s;

}

void SceneReader::readFile(QString fileName) {

    std::cout << fileName.toStdString() << std::endl;

    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly)) {
        std::cerr << "Error opening the file" << std::endl;
        return;
    }

    QTextStream in(&file);

    while (!in.atEnd()) {
        QString line = in.readLine();
        fileLineRead(line);
    }

    file.close();
}

// TODO: Fase 1: Cal afegir més tipus d'objectes
void SceneReader::fileLineRead(QString lineReaded) {
    QStringList fields = lineReaded.split(",");

    if (QString::compare("Sphere", fields[0], Qt::CaseInsensitive) == 0) //Sphere
        sphereFound(fields);
    else if (QString::compare("Base", fields[0], Qt::CaseInsensitive) == 0) //Plane, Triangle, FittedPlane
        baseFound(fields);
    else if (QString::compare("BrObject", fields[0], Qt::CaseInsensitive) == 0) //BoundaryObject
        brObjectFound(fields);
    else if (QString::compare("Cylinder", fields[0], Qt::CaseInsensitive) == 0) //Cylinder
        cylinderFound(fields);
    else
        std::cerr << "Element unknown" << std::endl;
}

// Exemple d'esfera
// sphere, 0.5, 0.5, 0.0, 0.25
void SceneReader::sphereFound(QStringList fields) {
    if (fields.size() != 5) {
        std::cerr << "Wrong sphere format" << std::endl;
        return;
    }
    Object *o;
    o = ObjectFactory::getInstance()->
            createObject(fields[1].toDouble(), fields[2].toDouble(), fields[3].toDouble(),
                    fields[4].toDouble(),1.0f, ObjectFactory::OBJECT_TYPES::SPHERE);

    scene->objects.push_back(o);
}


// Exemple de base:
// Base,  plane,  0.0,  1.0,  0.0,  -0.5, ://resources/map.png
// Base, triangle, 1.0, 1.0, 1.0, -1, -1
// Base, fitted, x_min, z_min, x_max, z_max
void SceneReader::baseFound(QStringList fields) {
    if (fields.size() != 7) {
        std::cerr << "Wrong base format" << std::endl;
        return;
    }

    if (QString::compare("plane", fields[1], Qt::CaseInsensitive) == 0 ||
        QString::compare(" plane", fields[1], Qt::CaseInsensitive) == 0) {
        Object *o;
        // TODO Fase 1: Cal fer un pla acotat i no un pla infinit. Les dimensions del pla acotat seran les dimensions de l'escena en x i z
        o = ObjectFactory::getInstance()->createObject(fields[2].toDouble(), fields[3].toDouble(), fields[4].toDouble(),
                                                       fields[5].toDouble(), 1.0f, ObjectFactory::OBJECT_TYPES::PLANE);


        scene->objects.push_back(o);
        // TODO Fase 4: llegir textura i afegir-la a l'objecte. Veure la classe Texture
    } else if (QString::compare("triangle", fields[1], Qt::CaseInsensitive) == 0 ||
               QString::compare(" triangle", fields[1], Qt::CaseInsensitive) == 0) {
        Object *o = ObjectFactory::getInstance()->createObject(fields[2].toDouble(), fields[3].toDouble(),
                                                                 fields[4].toDouble(), fields[5].toDouble(),
                                                                 fields[6].toDouble(),
                                                                 ObjectFactory::OBJECT_TYPES::TRIANGLE);

        scene->objects.push_back(o);
    } else if (QString::compare("fitted", fields[1], Qt::CaseInsensitive) == 0 ||
               QString::compare(" fitted", fields[1], Qt::CaseInsensitive) == 0){

        // Primer llegim els minims i despres els maxims
        double x_min = fields[2].toDouble();
        double x_max = fields[4].toDouble();
        double z_min = fields[3].toDouble();
        double z_max = fields[5].toDouble();
        double aux = fields[6].toDouble();

        //Si volem cambiar la posicio del pla hem d'anar al constructor del mateix
        //per defecte la normal es un vector que segueix l'eix vertical
        Object *o = ObjectFactory::getInstance()->createObject(x_min, x_max, z_min, z_max, aux, ObjectFactory::OBJECT_TYPES::FITTED_PLANE);
        scene->objects.push_back(o);

    }
    // TODO: Fase 3: Si cal instanciar una esfera com objecte base i no un pla, cal afegir aqui un switch
}

//brObject, cube.obj, 0, 0, 0, 10
void SceneReader::brObjectFound(QStringList fields) {

    // TODO Fase 1: Per incloure BrObjecte
    //  Es suposa que serà una linia del fitxer de l'estil
    //  brobject nomDelFitxer posició del seu centre, i la seva escala

    if (fields.size() != 6) {
        std::cerr << "Wrong brObject format" << std::endl;
        return;
    }

    Object *o;

    string file_name = fields[1].toStdString();
    float coord_x = fields[2].toFloat();
    float coord_y = fields[3].toFloat();
    float coord_z = fields[4].toFloat();
    float scale = fields[5].toFloat();

    o = ObjectFactory::getInstance()->createBrObject(coord_x, coord_y, coord_z, scale, file_name);
    scene->objects.push_back(o);
}

void SceneReader::cylinderFound(QStringList fields) {
    if (fields.size() != 6) {
        std::cerr << "Wrong cylinder format" << std::endl;
        return;
    }

    double x = fields[1].toDouble();
    double y = fields[2].toDouble();
    double z = fields[3].toDouble();
    double r = fields[4].toDouble();
    double h = fields[5].toDouble();

    Object *o = ObjectFactory::getInstance()->createObject(x,y,z,r,h,ObjectFactory::CYLINDER);
    scene->objects.push_back(o);
}