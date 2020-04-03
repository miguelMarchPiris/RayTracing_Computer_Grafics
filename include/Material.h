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
    //Material(vec3 a, vec3 d, vec3 s, vec3 k, float beta);
    Material(vec3 a, vec3 d, vec3 s, float o, int sh);
    ~Material();

    virtual bool scatter(const Ray& r_in, const IntersectionInfo& rec, vec3& color, std::vector<Ray>&r_out) const = 0;
    virtual vec3 getDiffuse(vec2 point)const;
    vec3 multScalar(float f,vec3 vec)const;

    vec3 Kdiffuse;
    vec3 Kspecular;
    vec3 Kambient;
    vec3 Kt = vec3(0);

    //Controlar la opacitat i brillantor del objecte
    float alpha;
    int shininess;
    double const EPSILON = 0.001;

protected:
    vec3 RandomInSphere() const;
};

#endif // MATERIAL_H
