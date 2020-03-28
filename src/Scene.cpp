#include "Scene.h"

Scene::Scene()
{
    pmin.x = -0.5f;  pmin.y = -0.5f; pmin.z = -0.5f;
    pmax.x = 0.5f;  pmax.y = 0.5f; pmax.z = 0.5f;
}

Scene::~Scene()
{
// TODO Fase 1: Quan s'incloguin nous objectes, cal retocar aquest destructor
    for(unsigned int i = 0; i < objects.size(); ++i){
        if(objects[i]){
            if (dynamic_cast<Sphere*>(objects[i]))
                    delete (Sphere *)(objects[i]);
        }
    }
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
    /* IntersectionInfo temporal per a cada objecte */
    IntersectionInfo info_temp;
    info.t = t_max;

    for(auto object : objects)
    {
        if (object->intersection(raig, t_min, t_max, info_temp))
        {
            if (info_temp.t < info.t)
            {
                /* Si arribem a un minim, ho copiem al intersection info del raig */
                info = info_temp;
            }
        }
    }
    return info.t < t_max;
    // TODO FASE 0 i FASE 1: Heu de codificar la vostra solucio per aquest metode substituint el 'return true'
    // Una possible solucio es cridar el mètode intersection per a tots els objectes i quedar-se amb la interseccio
    // mes propera a l'observador, en el cas que n'hi hagi més d'una.
    // Cada vegada que s'intersecta un objecte s'ha d'actualitzar el IntersectionInfo del raig,
    // pero no en aquesta funcio.
}


/*
** TODO: Funcio ComputeColorRay es la funcio recursiva del RayTracing.
 * TODO: FASE 1 per a cridar a la intersecció amb l'escena i posar el color de l'objecte
** TODO: Fase 2 de l'enunciat per incloure Blinn-Phong  i ombres
** TODO: Fase 2 per a tractar reflexions i transparències
**
*/
vec3 Scene::ComputeColorRay (Ray &ray, int depth ) {
    vec3 color;
    vec3 ray2;

    ray2 = normalize(ray.direction);
    // TODO: A canviar el càlcul del color en les diferents fases
    IntersectionInfo info;

    if (this->intersection(ray, 0, 100, info))
        color = info.normal;
    else{
        //color = vec3(-0.5 * ray2.y + 0.75, -0.3 * ray2.y + 0.85, 1);
        vec3 white = vec3(1.0,1.0,1.0);
        vec3 blue = vec3(0.5,0.7,1.0);
        float t = 0.5f*(ray2.y+1);
        color = vec3(t*blue+(1-t)*white);
    }

    return color;
}



void Scene::update(int nframe) {
    for (unsigned int i = 0; i< objects.size(); i++) {
        if (dynamic_cast<Animable*>(objects[i]) ) objects[i]->update(nframe);
    }
}

void Scene::setMaterials(ColorMap *cm) {

    Material *m;
    // TODO: Fase 0
    // Cal canviar el codi per a afegir més materials.
    srand (static_cast <unsigned> (time(0)));
    for (auto object: this->objects)
    {
        /* Per cada objecte afegim un material de manera random */
        object->setMaterial(new Lambertian(
                vec3((float) rand()/RAND_MAX, (float) rand()/RAND_MAX, (float) rand()/RAND_MAX))
                );
    }
    // TODO: Fase 2
    // Cal canviar el tipus de material Lambertian, Specular, Transparent, Tipus Textura
    if (cm == nullptr)
        m = new Lambertian(vec3(0.5, 0.2, 0.7));
    else {
        // TODO: Fase 2:
        //  Crear els materials segons la paleta de cada propietat a cada objecte de l'escena
        m = new Lambertian(cm->getColor(0));
    }
    for (auto o:objects)
        if (o->getMaterial()== nullptr) o->setMaterial(m);
}

void Scene::setDimensions(vec3 p1, vec3 p2) {
    pmin = p1;
    pmax = p2;
}

