#include "DataReader.h"
#include <QFile>
#include <QTextStream>
#include <iostream>
#include <sstream>
#include <include/ObjectFactory.h>
#include <include/MaterialTextura.h>

DataReader::DataReader(Scene *s)
{
    scene = s;
    numProp = 0;
    proporcio = 10.0f;
}

void DataReader::readFile(QString fileName) {
    QFile file(fileName);

    if(!file.open(QIODevice::ReadOnly)) {
        std::cerr << "Error opening the file" << std::endl;
        return;
    }

    QTextStream in(&file);
    while(!in.atEnd()) {
        QString line = in.readLine();
        fileLineRead(line);
    }

    file.close();
}

// TODO: Fase 1: Cal afegir més tipus d'objectes
void DataReader::fileLineRead (QString lineReaded) {

    QStringList fields = lineReaded.split(",");
    if (QString::compare("limits", fields[0], Qt::CaseInsensitive) == 0)
        limitsFound(fields);
    else if (QString::compare("base", fields[0], Qt::CaseInsensitive) == 0)
        baseFound(fields);
    else if (QString::compare("prop", fields[0], Qt::CaseInsensitive) == 0)
        propFound(fields);
    else if (QString::compare("data", fields[0], Qt::CaseInsensitive) == 0)
        dataFound(fields);
    else
        std::cerr << "Element unknown" << std::endl;
}

void DataReader::baseFound(QStringList fields) {
    //base plane nx ny nz d textura
    if (fields.size() != 7) {
        std::cerr << "Wrong base format" << std::endl;
        return;
    }
    if(fields[1].toStdString()[0] == ' ')
        fields[1] = fields[1].remove(0, 1);
    std::cout << fields[1].toStdString() << std::endl;
    if (QString::compare("plane", fields[1], Qt::CaseInsensitive) == 0) {
        // TODO Fase 1: Cal fer un pla acotat i no un pla infinit. Les dimensions del pla acotat seran les dimensions de l'escena en x i z
        Object *o;
        o = ObjectFactory::getInstance()->createObject(-1 * proporcio, proporcio, -1 * proporcio,
                                                       proporcio, fields[5].toFloat(),ObjectFactory::FITTED_PLANE);
        //auto *translate1 = new Translate(vec3((-1) * scene->pmin[0], 0.0f, (-1) * scene->pmin[2]));
        //o->aplicaTG(translate1);
        //auto *scale1 = new Scale(10);
        //o->aplicaTG(scale1);

        // TODO Fase 4: llegir textura i afegir-la a l'objecte. Veure la classe Texture
        scene->floor = dynamic_cast<FittedPlane *>(o);
        scene->floor->setMaterial(new MaterialTextura(fields[6]));
        //scene->setMaterials(scene->ground->getMaterial());
        //scene->objects.push_back(scene->ground);
    }
    // TODO: Fase 3: Si cal instanciar una esfera com objecte base i no un pla, cal afegir aqui un else
}




void DataReader::limitsFound(QStringList fields) {
    // limits xmin xmax zmin zmax
    if (fields.size() != 5) {
        std::cerr << "Wrong limits format" << std::endl;
        return;
    }
    // TODO Fase 1: Cal guardar el limits del mapa per saber on mapejar les posicions dels objectes
    //limites del plano o de la escena? O las dos cosas?
    double x_min = fields[1].toDouble();
    double x_max = fields[2].toDouble();
    double z_min = fields[3].toDouble();
    double z_max = fields[4].toDouble();

    scene->setDimensions(vec3(x_min,0,z_min), vec3(x_max,0,z_max));

}
//vec3 normal, vec3 pass_point, vec2 pass_min, vec2 pass_max, float d

void DataReader::propFound(QStringList fields) {
    //prop numProp vmin vmax tipusGizmo
    if (fields.size() != 5)
    {
        std::cerr << "Wrong propietat format" << std::endl;
        return;
    }
    // TODO Fase 1: Cal guardar els valors per a poder escalar els objectes i el tipus de
    //  gizmo de totes les propietats (SPHERE, BR_OBJ, CILINDRE...)

    cout<<fields[4].toStdString()<<endl;
    if (QString::compare("sphere", fields[4], Qt::CaseInsensitive) == 0) {
        props.push_back(ObjectFactory::OBJECT_TYPES::SPHERE);
        this->props_data[2*numProp] = (float) fields[2].toInt();
        this->props_data[2*numProp + 1] = (float) fields[3].toInt();
    }
    else if (QString::compare("cylinder", fields[4], Qt::CaseInsensitive) == 0) {
        std::cout << "Cilindre" << std::endl;
        props.push_back(ObjectFactory::OBJECT_TYPES::CYLINDER);
        this->props_data[2*numProp] = (float) fields[2].toInt();
        this->props_data[2*numProp + 1] = (float) fields[3].toInt();
    }

    numProp++;

    // TODO Fase 2: Aquesta valors minim i maxim tambe serviran per mapejar el material des de la paleta
}


void DataReader::dataFound(QStringList fields) {
    //data x z valor1 valor2...
    if (fields.size() != (numProp+3)) {
        std::cerr << "Wrong data format" << std::endl;
        return;
    }
    for (int i=0; i<numProp; i++) {
        // TODO Fase 1: Cal colocar els objectes al seu lloc del mon virtual, escalats segons el valor i
        //  amb el seu color corresponent segons el seu ColorMap
        Object *o;
        vec3 point (fields[1].toFloat(), 0.0f, fields[2].toFloat());
        vec2 uvpoint = scene->get_uvCoords(point);
        cout << uvpoint[0] << " " << uvpoint[1] << endl;
        float r = (fields[3 + i].toFloat()/(2 * (props_data[2*i+1] - props_data[2*i])));
        cout << fields[3 + i].toFloat() << " " << r << endl;
        o = ObjectFactory::getInstance()->createObject(2 * proporcio * uvpoint[0] - proporcio + i, 0.0, 2 * proporcio * uvpoint[1] - proporcio,
                                                       r, 0.0f,
                                                       props[i]);
        scene->objects.push_back(o);
    }
}
