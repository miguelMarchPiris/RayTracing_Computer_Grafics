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
    Material(vec3 ambient, vec3 diffuse, vec3 specular, float beta, float shininess);
    ~Material();

    virtual bool scatter(const Ray& r_in, const IntersectionInfo& rec, std::vector<vec3>& colors, std::vector<Ray>& r_out) const = 0;

    // Ka
    vec3 ambient;
    // Kd
    vec3 diffuse;
    // Ks
    vec3 specular;
    float beta;
    int shininess;

protected:
    vec3 RandomInSphere() const;
};

#endif // MATERIAL_H
