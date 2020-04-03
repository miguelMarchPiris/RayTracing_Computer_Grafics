#include <include/Transparent.h>
#include "Scene.h"
#include "glm/gtx/string_cast.hpp"
#include "MaterialTextura.h"
#include "Metal.h"

Scene::Scene()
{
    pmin.x = -5;  pmin.y = -5; pmin.z = -5;
    pmax.x = 5;  pmax.y = 5; pmax.z = 5;
    // llum d'ambient global
    globalAmbientLighting = vec3(0.1f, 0.1f, 0.1f);
}

// TODO cal modificar aquest metode en el moment que afegim mes materials (a part del Lambertian)
//  o be quan afegim mes figures en el cas de que calgues
Scene::~Scene()
{
// TODO Fase 1: Quan s'incloguin nous objectes, cal retocar aquest destructor

    //Cal alliberar memoria reservada pels objectes. Aquests eliminaran la instancia de material que tinguin
    for(unsigned int i = 0; i < objects.size(); ++i)
        if (objects[i]) {
            if (dynamic_cast<Sphere *>(objects[i]))
                delete (Sphere *) (objects[i]);

            if (dynamic_cast<Plane *>(objects[i]))
                delete (Plane *) (objects[i]);

            if (dynamic_cast<Triangle *>(objects[i]))
                delete (Triangle *) (objects[i]);

            if (dynamic_cast<BoundaryObject *>(objects[i]))
                delete (BoundaryObject *) (objects[i]);

            if (dynamic_cast<FittedPlane *>(objects[i]))
                delete (FittedPlane *) (objects[i]);

            if (dynamic_cast<Cylinder *>(objects[i]))
                delete (Cylinder *) (objects[i]);
        }

    //per les llums
    for(unsigned int i = 0; i < lights.size(); i++) delete lights[i];
}

/*
** TODO: FASE 1: Metode que testeja la interseccio contra tots els objectes de l'escena
**
** Si un objecte es intersecat pel raig, el parametre  de tipus IntersectInfo conte
** la informació sobre la interesccio.
** El metode retorna true si algun objecte es intersecat o false en cas contrari.
**
*/
bool Scene::intersection(const Ray& raig, float t_min, float t_max, IntersectionInfo& info) const
{
    // Cada vegada que s'intersecta un objecte s'ha d'actualitzar el HitInfo del raig,
    // pero no en aquesta funcio.
    // Considerem que no hem trobat col*lisionat amb ningun objecte
    // Hem de crear un nou Hitinfo per poder actualitzar si hem trobat un objecte més próxim.
    IntersectionInfo info_temp;
    info.t = t_max;

    for(auto object : objects)
        if (object->intersection(raig, t_min, t_max, info_temp))
            if (info_temp.t < info.t)
                /* Si arribem a un minim, ho copiem al intersection info del raig */
                info = info_temp;

    return info.t < t_max;
}

/*
** TODO: Funcio ComputeColorRay es la funcio recursiva del RayTracing.
 * TODO: FASE 1 per a cridar a la intersecció amb l'escena i posar el color de l'objecte
** TODO: Fase 2 de l'enunciat per incloure Blinn-Phong  i ombres
** TODO: Fase 2 per a tractar reflexions i transparències
**
*/
vec3 Scene::ComputeColorRay (Ray &ray, int depth) {
    vec3 color = vec3(0, 0, 0), k, ray2;
    Ray rL;
    vector<vec3> colors;
    vector<Ray> reflections;

    // Vectors pel model de Phong:
    // Del punt a la superficie de la llum - L
    vec3 l;
    // Del punt a l'observador - V
    vec3 v;
    // Normal al punt - N
    vec3 n;
    // Vector H
    vec3 h;

    float dist, factorOmbra, epsilon = 0.001f;

    // Per algun motiu no normalitza be (dona valors negatius), per aixo s'afegeix el segon vector
    ray2 = normalize(ray.initialPoint());
    // TODO: A canviar el càlcul del color en les diferents fases
    IntersectionInfo info, infoTemp;

    // Blinn-Phong
    if (this->intersection(ray, 0, 100, info)) {

        v = ray.initialPoint() - info.p;
        n = glm::normalize(info.normal);

        // Component ambient global
        color += globalAmbientLighting * info.mat_ptr->Kambient;
        for (auto light:lights) {

            l = glm::normalize(light->punt - info.p);
            h = (l + v) / (length(l + v));

            /////////// FASE 3 /////////////
            // Component difusa
            info.uv = get_uvCoords(info.p); //debemos obtener el punto (u,v) a traves del punto con el que se intersecta
            //en el caso de que el material sea MaterialTextura obtendremos los textels a traves de las coordenadas uv
            color += info.mat_ptr->getDiffuse(info.uv) * light->Kdiffuse * glm::max(dot(l, n), 0.0f);
            ////////////////////////////////

            // Component especular
            color += info.mat_ptr->Kspecular * light->Kspecular *
                     pow(glm::max(dot(h, n), 0.0f), (float) info.mat_ptr->shininess);//info.mat_ptr->beta * );

            // Dividim per la distància
            dist = glm::length(light->punt - info.p);
            color /= (dist * dist * light->attenuation[0] + dist * light->attenuation[1] + light->attenuation[2]);

            // Càlcul de l'ombra
            rL = Ray(ray.pointAtParameter(info.t) +
                     epsilon * glm::normalize(light->punt - info.p),
                     glm::normalize(light->punt - info.p));
            if (this->intersection(rL, 0, 100, infoTemp)) {
                factorOmbra = 0.0f;
            } else {
                factorOmbra = 1.0f;
            }

            color *= factorOmbra;

            // Component ambient
            color += light->Kambient * info.mat_ptr->Kambient;

            if (depth < MAX_REFLECT) {
                // si el material es transparente
                if (dynamic_cast<const Transparent *>(info.mat_ptr)) {
                    //Transparent* trans = (Transparent*) info.mat_ptr;
                    vec3 coloraux = vec3(0, 0, 0);
                    info.mat_ptr->scatter(ray, info, colors, reflections);
                    for (int i = 0; i < reflections.size(); i++) {
                        coloraux += colors[i] * ComputeColorRay(reflections[i], depth + 1);
                    }
                    color = coloraux;
                    //color+=colors[i] * ComputeColorRay(reflections[i],depth + 1);
                } else {
                    info.mat_ptr->scatter(ray, info, colors, reflections);
                    for (int i = 0; i < reflections.size(); i++) {
                        color += colors[i] * ComputeColorRay(reflections[i], depth + 1);
                    }


                }
            }
        }
    }else {

        if(depth <= 5) {
            color = (1 - ray2.y) * vec3(1, 1, 1) + ray2.y * vec3(0, 0, 1);
        }else{
            color = globalAmbientLighting;
        }
    }

    //return color;
//}

    return color;
}

void Scene::update(int nframe) {
    for (unsigned int i = 0; i< objects.size(); i++) {
        if (dynamic_cast<Animable*>(objects[i]) ) objects[i]->update(nframe);
    }
}

// TODO no s'entén gaire
void Scene::setMaterials(ColorMap *cm) {
    Material *m;
    // TODO: Fase 0
    // Cal canviar el codi per a afegir més materials.
    srand (static_cast <unsigned> (time(0)));
    for (auto object: this->objects)
    {
        if (object->getMaterial() == NULL) {
            vec3 ambient = vec3(((float) rand()/RAND_MAX, (float) rand()/RAND_MAX, (float) rand()/RAND_MAX));
            vec3 diffuse = vec3(((float) rand()/RAND_MAX, (float) rand()/RAND_MAX, (float) rand()/RAND_MAX));
            vec3 specular = vec3(((float) rand()/RAND_MAX, (float) rand()/RAND_MAX, (float) rand()/RAND_MAX));
            float alpha = 1.f;
            float shininess= 30;

            // Per cada objecte afegim un material de manera random
            object->setMaterial(new Metal(vec3(0.2, 0.2, 0.2), vec3(0.7, 0.7, 0.7), vec3(0.7, 0.7, 0.7), 1, 10));
        }
    }
    // TODO: Fase 2
    // Cal canviar el tipus de material Lambertian, Specular, Transparent, Tipus Textura
    if (cm == nullptr)
        m = new Lambertian(vec3(0.1,0.1,0.1),vec3(0.5, 0.2, 0.7),vec3(1.,1.,1.),1,400);
    else {
        // TODO: Fase 2:
        //  Crear els materials segons la paleta de cada propietat a cada objecte de l'escena
        m = new Lambertian(vec3(0.1,0.1,0.1),cm->getColor(0),vec3(1.,1.,1.),1,400);
    }
    for (auto o:objects)
        if (o->getMaterial() == nullptr) o->setMaterial(m);
}

void Scene::setDimensions(vec3 p1, vec3 p2) {
    pmin = p1;
    pmax = p2;
}


vec2 Scene::get_uvCoords(vec3 point){
    //Aplicar Operació (extreta de Parcial Transpas)
    //xUV = xDades * ( xmaxUV - xminUV) /(xmax - xmin) - xmin * ( xmaxUV - xminUV) /(xmax - xmin) + xminUV
    float u = (point.x - pmin.x) / (pmax.x - pmin.x);
    float v = (point.z - pmin.z) / (pmax.z - pmin.z);
    return vec2(u,v);
}
