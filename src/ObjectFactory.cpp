#include <include/Cylinder.h>
#include "ObjectFactory.h"

ObjectFactory *ObjectFactory::instance = nullptr;

ObjectFactory::ObjectFactory() {

}

//! createObject
/*!
  \sa testMe()
  \param x coordenada x on cal colocar el centre de l'objecte.
  \param y coordenada x on cal colocar el centre de l'objecte.
  \param z coordenada x on cal colocar el centre de l'objecte.
  \param aux paràmetre addicional per codificar el radi de l'esfera o la d del pla.
  \param v valor d'escala que cal aplicar a l'objecte
  \param t tipus d'objecte a construir: SPHERE, PLANE, ....
*/
Object *ObjectFactory::createObject(float x, float y, float z, float aux, float v, OBJECT_TYPES t) {
    Object *o;
    // TODO Fase 1: Incloure diferents objectes: CILINDRES, TRIANGLES, BR_OBJECTES
    switch (t) {
        case SPHERE:
            o = new Sphere(vec3(x, y, z), aux, v);
            break;
        case PLANE:
            o = new Plane(vec3(x, y, z), aux, v);
            break;
        case TRIANGLE:
            //o = new Triangle(vec3(x, y, z), aux, v);
            o = new Triangle(vec3(x,0,0),vec3(0,y,0),vec3(0,0,z), aux);
            break;
            //case CYLINDER:
            //  cout<< "Cilindro creado"<<endl;
            //break;
        case FITTED_PLANE:
            o = new FittedPlane(vec3(0,1,0), vec3(0,-1,0), vec2(x,z), vec2(y,aux), -1);
            break;
        case CYLINDER:
            o = new Cylinder(vec3(x,y,z), 1.,aux,v);
            break;
        default:
            break;
    }

    return o;
}

Object *ObjectFactory::createBrObject(float x, float y, float z, float v, string file_name) {
    Object *o;
    o = new BoundaryObject(file_name, v);
    o->aplicaTG(new Translate(vec3(-x,-y,-z)));
    return o;
}