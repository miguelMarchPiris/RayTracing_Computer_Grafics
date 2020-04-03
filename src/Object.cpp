#include "Object.h"


Object::Object()
{
    data = -1;
    material = nullptr;
}

Object::Object(float d)
  {
    data = d;
    material = nullptr;
  }

Object::~Object()
{
    // TODO Fase 2: Quan s'incloguin nous materials, cal retocar aquest destructor
    if (material!=nullptr){
        if (dynamic_cast<Lambertian *>(material))
            delete (Lambertian *)material;
        if (dynamic_cast<MaterialTextura *>(material))
            delete (MaterialTextura *)material;
        if (dynamic_cast<Metal *>(material))
            delete (Metal *)material;
        if (dynamic_cast<Transparent *>(material))
            delete (Transparent *)material;
    }
}

float Object::getData() {
    return data;
}

void Object::setMaterial(Material *m) {
    material = m;
}

Material *Object::getMaterial() {
    return material;
}
