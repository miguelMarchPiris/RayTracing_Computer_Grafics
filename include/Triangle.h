//
// Created by marcos on 8/3/20.
//

#ifndef RAYDATA_TRIANGLE_H
#define RAYDATA_TRIANGLE_H

#include <iostream>
#include "Plane.h"
#include "Scale.h"
#include "Rotate.h"

using namespace std;

class Triangle : public Plane {
public:
    //Constructors i destructor
    Triangle(vec3 v1, vec3 v2, vec3 v3, float data);
    Triangle(vec3 cord, float r, float d);
    virtual ~Triangle();

    //intersection i aplicaTG
    virtual bool intersection(const Ray& r, float t_min, float t_max, IntersectionInfo& info) const;

    //Para mover el objeto dentro de las coords de la escena
    //De momento solo consideramos trasladar y reescalar triangulos
    virtual void aplicaTG(TG *t);

private:
    //Esta tolerancia nos va a servir para determinar si la normal del triangulo contenido en el plano
    //forma un angulo muy proximo a 90 (triangulo y rayo paralelos) con el rayo
    float const EPSILON = 0.001;

    vector<vec3> vertexs;
    vec3 v1, v2, v3; //cordenadas de los tres vertices
    vec3 normal; //vector normal del triangulo

    //Tamaño del triangulo
    float size;
};


#endif //RAYDATA_TRIANGLE_H
