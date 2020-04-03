#ifndef MATERIAL_H
#define MATERIAL_H

#include <vector>
#include "Ray.h"
#include "Hitable.h"


// Classe abstracte Material. Totes les seves filles hauran de definir el metode abstracte sccater
class Material
{
public:

    Material();
    //Material(vec3 ambient, vec3 kdiffuse, vec3 specular, float beta, float shininess);
    Material(vec3 a, vec3 d, vec3 s, float o, int sh);
    ~Material();

    virtual bool scatter(const Ray& r_in, const IntersectionInfo& rec, std::vector<vec3>& colors, std::vector<Ray>&r_out) const = 0;
    virtual vec3 getDiffuse(vec2 point)const;
    vec3 multScalar(float f,vec3 vec)const;

    /*

     *
    this->specular=vec3(1,1,1)-this->kt;
    this->diffuse=vec3(0,0,0);
    this->ambient

     this->kdiffuse = vec3(0.5,0.5,0.5);
    this->Kspecular = vec3(1.0,1.0,1.0);
    this->Kambient = vec3(0.2,0.2,0.2);
    this->alpha = 1.0;
    this->shininess = 50.0;

     */
    vec3 Kdiffuse= vec3(0);
    vec3 Kspecular= vec3(0);
    vec3 Kambient= vec3(0);
    vec3 Kt = vec3(0);

    //Controlar la opacitat i brillantor del objecte
    float alpha;
    int shininess;
    double const EPSILON = 0.001;

protected:
    vec3 RandomInSphere() const;
};

#endif // MATERIAL_H
