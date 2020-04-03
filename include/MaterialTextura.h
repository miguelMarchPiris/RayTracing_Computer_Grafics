//
// Created by marcos on 31/3/20.
//

#ifndef RAYDATA_MATERIALTEXTURA_H
#define RAYDATA_MATERIALTEXTURA_H

#include "Material.h"
#include "Texture.h"

class MaterialTextura : public Material{
public:
    //Constructors i destructor
    MaterialTextura();
    MaterialTextura(QString);
    MaterialTextura(vec3 a, vec3 d, vec3 s, float o, int sh);
    virtual ~MaterialTextura();

    //metode scatter
    virtual bool scatter(const Ray& r_in, const IntersectionInfo& rec, vec3& color, std::vector<Ray> &r_out) const;
    vec3 getDiffuse(vec2 point)const override;

    //Carreguem la textura/imatge que volem
    Texture *image;//= new Texture("://resources/mondrian.png");
    double const EPSILON = 0.001;
};


#endif //RAYDATA_MATERIALTEXTURA_H
