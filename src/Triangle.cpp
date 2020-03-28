//
// Created by marcos on 8/3/20.
//

#include "Triangle.h"

Triangle::Triangle(vec3 v1, vec3 v2, vec3 v3, float data): Plane(cross(v2 - v1, v3 - v1), v1, data){
    this->v1 = v1;
    this->v2 = v2;
    this->v3 = v3;

    this->vertex = std::vector<vec3>();
    this->vertex.push_back(v1);
    this->vertex.push_back(v2);
    this->vertex.push_back(v3);

    this->normal = normalize(cross(v2 - v1,v3 - v1));
}

Triangle::Triangle(vec3 cord, float r, float d):Plane(cross(vec3(0,1,0) - vec3(1,0,0),vec3(0,0,1) - vec3(1,0,0)), vec3(1,0,0), d){
    this->v1 = vec3(1,0,0);
    this->v2 = vec3(0,1,0);
    this->v3 = vec3(0,0,1);
    vertex = std::vector<vec3>();
    vertex.push_back(v1);
    vertex.push_back(v2);
    vertex.push_back(v3);
    normal = normalize(cross(v2 - v1, v3 - v1));
    this->aplicaTG(new Translate(cord));
}

Triangle::~Triangle() {}

bool Triangle::intersection(const Ray& r, float t_min, float t_max, IntersectionInfo& info) const {
    //Fem el producte escalar entre el vector director del raig i la normal del pla
    float prod=dot(r.dirVector(),normal);

    // Comprovem si fa un hit en el pla que conté el triangle
    if(Plane::intersection(r,t_min,t_max,info)){
        //Dunno what is goin on here
        //if(fabs(prod)<EPSILON){
            //return false;
        //}

        // Calculem la d, és a dir la distància desde l'origen de coordenades fins al pla
        float d=-dot(normal,vertex[0]);

        // Calculem la distància t amb la fòrmula que tenim a
        // https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/ray-triangle-intersection-geometric-solution
        float t_dist=-((d+dot(normal,r.initialPoint()))/prod);
        vec3 interseccio=r.pointAtParameter(t_dist);

        // Creem les arestes del triangle
        float a1=dot(cross((vertex[1]-vertex[0]),interseccio-vertex[0]),normal);
        float a2=dot(cross((vertex[2]-vertex[1]),interseccio-vertex[1]),normal);
        float a3=dot(cross((vertex[0]-vertex[2]),interseccio-vertex[2]),normal);

        // Mirem si les arestes tenen el mateix signe,
        // per a saber si la intersecció està dintre del triangle
        if((a1<0 && a2<0 && a3<0) || (a1>0 && a2>0 && a3>0)){
            // Si la distància t calculada està dins del rang del raig,
            // actualitzem la info
            if(t_min<t_dist && t_dist<t_max){
                info.t = t_dist;
                info.p = interseccio;
                if(prod<0)
                    info.normal = normal;
                else
                    info.normal = -normal;
                info.mat_ptr = material;
                return true;
            }
            return false;
        }else{
            return false;
        }
    }
    return false;
}
