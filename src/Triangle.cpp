//
// Created by marcos on 8/3/20.
//

#include "Triangle.h"

Triangle::Triangle(vec3 v1, vec3 v2, vec3 v3, float data): Plane(cross(v2 - v1, v3 - v1), v1, data){
    this->v1 = v1;
    this->v2 = v2;
    this->v3 = v3;

    this->vertexs = std::vector<vec3>();
    this->vertexs.push_back(v1);
    this->vertexs.push_back(v2);
    this->vertexs.push_back(v3);

    this->normal = normalize(cross(v2 - v1,v3 - v1));
}

Triangle::Triangle(vec3 cord, float r, float d):Plane(cross(vec3(0,1,0) - vec3(1,0,0),vec3(0,0,1) - vec3(1,0,0)), vec3(1,0,0), d){
    this->v1 = vec3(1,0,0);
    this->v2 = vec3(0,1,0);
    this->v3 = vec3(0,0,1);
    vertexs = std::vector<vec3>();
    vertexs.push_back(v1);
    vertexs.push_back(v2);
    vertexs.push_back(v3);
    normal = normalize(cross(v2 - v1, v3 - v1));
    this->aplicaTG(new Translate(cord));
}

Triangle::~Triangle() {}

bool Triangle::intersection(const Ray& r, float t_min, float t_max, IntersectionInfo& info) const {
    //Fem el producte escalar entre el vector director del raig i la normal del pla
    float prod = dot(r.dirVector(),normal);

    // Comprovem si fa un hit en el pla que conté el triangle
    if(Plane::intersection(r,t_min,t_max,info)){

        //Comprovem si triangle i raig son paralels
        if(fabs(prod)<EPSILON){
            return false;
        }

        // Calculem la d, és a dir la distància desde l'origen de coordenades fins al pla
        float d=-dot(normal,vertexs[0]);

        // Calculem la distància t amb la interseccio
        float t_dist=-((d+dot(normal,r.initialPoint()))/prod);

        //el punt d'interseccio es el seguent
        vec3 interseccio=r.pointAtParameter(t_dist);

        // A continuació fem l'inside-outside test per a veure si la interseccio esta dins del triangle

        // Creem les arestes del triangle
        float a1=dot(cross((vertexs[1]-vertexs[0]),interseccio-vertexs[0]),normal);
        float a2=dot(cross((vertexs[2]-vertexs[1]),interseccio-vertexs[1]),normal);
        float a3=dot(cross((vertexs[0]-vertexs[2]),interseccio-vertexs[2]),normal);

        // Si les arestes tenen el mateix signe, la intersecció està dintre del triangle
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
        }else return false;
    }

    return false;
}

//Per aplicar TG's
void Triangle::aplicaTG(TG *t) {
    vec4 _v1(v1, 1.0);
    vec4 _v2(v2, 1.0);
    vec4 _v3(v3, 1.0);

    _v1 = t->getTG() * _v1;
    _v2 = t->getTG() * _v2;
    _v3 = t->getTG() * _v3;

    if (dynamic_cast<Translate *>(t)) {
        v1.x = _v1.x; v1.y = _v1.y; v1.z = _v1.z;
        v2.x = _v2.x; v2.y = _v2.y; v2.z = _v2.z;
        v3.x = _v3.x; v3.y = _v3.y; v3.z = _v3.z;
    }

    if (dynamic_cast<Scale *>(t)) {
        vec3 centroid(((v1.x + v2.x + v3.x)/3), ((v1.y + v2.y + v3.y)/3), ((v1.z + v2.z + v3.z)/3));
        Translate *centre = new Translate(-centroid);

        this->aplicaTG(centre);

        v1.x = _v1.x; v1.y = _v1.y; v1.z = _v1.z;
        v2.x = _v1.x; v2.y = _v1.y; v2.z = _v1.z;
        v3.x = _v1.x; v3.y = _v1.y; v3.z = _v1.z;

        this->aplicaTG(new Translate(centroid));
    }

    if (dynamic_cast<Rotate *>(t)) {
        vec3 centroid(((v1.x + v2.x + v3.x)/3), ((v1.y + v2.y + v3.y)/3), ((v1.z + v2.z + v3.z)/3));
        Translate *centre = new Translate(-centroid);

        this->aplicaTG(centre);

        v1.x = _v1.x; v1.y = _v1.y; v1.z = _v1.z;
        v2.x = _v1.x; v2.y = _v1.y; v2.z = _v1.z;
        v3.x = _v1.x; v3.y = _v1.y; v3.z = _v1.z;

        this->aplicaTG(new Translate(centroid));
    }
}
