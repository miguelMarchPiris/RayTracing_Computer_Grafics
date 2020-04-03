//
// Created by anna on 18/01/2020.
//

#include <include/Cylinder.h>
#include <include/Metal.h>
#include <include/Transparent.h>
#include "SceneFactoryVirtual.h"


SceneFactoryVirtual::SceneFactoryVirtual()
{

}

Scene *SceneFactoryVirtual::createScene(QString filename) {
    Scene *s = new Scene();
    SceneReader *sc = new SceneReader(s);
    sc->readFile(filename);
    return s;
}

Scene *SceneFactoryVirtual::createScene() {
    Scene *s = new Scene();
    //   TODO Fase 0: Test amb una esfera.
    //  TODO Fase 1: Aquest codi es pot modificar per a provar la visualització de diferents primitives bàsiques
    this->OneSphere(s);
    return s;
}

void SceneFactoryVirtual::OneSphere(Scene *s) {


    //Base
    Sphere * sphere_base = new Sphere(vec3(0, -100.5, -1), 100, 1.0);
    sphere_base->setMaterial(new Lambertian(vec3(0.2, 0.2, 0.2), vec3(0.8, 0.8, 0.0), vec3(1, 1, 1), 1, 10));

    Sphere * esfera_metalica = new Sphere(vec3(-0.6, 1.4, -5.2), 1.2, 1.0);
    Cylinder*cilindro_transparente               = new Cylinder(vec3(1., 0.5, -2.0), 1.5, 2.5, 1.0);
    Sphere * esfera_transparente  = new Sphere(vec3(0.0, 1.6, -2.0), 1.5, 1.0);
    Sphere * esfera_blanca            = new Sphere(vec3(1.75, 1.5, -5.0), 0.6, 1.0);
    Sphere * esfera_fucsia             = new Sphere(vec3(2.5, 1.5, -5.5), 0.8, 1.0);
    Sphere * esfera_verde            = new Sphere(vec3(-2.0, 3.5, -3.0), 1.3, 1.0);

    esfera_metalica->setMaterial(new Metal(vec3(0.2, 0.2, 0.2), vec3(0.7, 0.7, 0.7), vec3(0.7, 0.7, 0.7), 1, 10));
    cilindro_transparente              ->setMaterial(new Transparent(vec3(1, 1, 1) * 0.9f, 1.35));
    esfera_transparente->setMaterial(new Transparent(vec3(1, 1, 1) * 0.9f, 1.05));
    esfera_blanca->setMaterial(new Lambertian(vec3(0.2, 0.2, 0.2), vec3(1, 1, 1), vec3(1, 1, 1), 1, 10));
    esfera_fucsia->setMaterial(new Lambertian(vec3(0.2, 0.2, 0.2), vec3(0.8, 0.0, 0.6), vec3(1, 1, 1), 1, 10));
    esfera_verde->setMaterial(new Lambertian(vec3(0.2, 0.2, 0.2), vec3(0, 1, 0), vec3(1, 0, 1), 1, 10));


    BoundaryObject *bro0 = new BoundaryObject("../resources/cube.obj", 1.0);
    bro0->setMaterial(new Lambertian(vec3(0.2, 0.2, 0.2), vec3(0.5, 0.5, 0.5), vec3(1, 1, 1), 1, 10));


    Light *light0 = new Light(vec3(10, 8, 10), vec3(0.3, 0.3, 0.3), vec3(0.7, 0.7, 0.7), vec3(1, 1, 1), vec3(0.01, 0, 0.5));
    //Light *light1 = new Light(vec3(-5, 4, -5));

    // Animation *anim = new Animation();
    // anim->transf = new Translate(vec3(0.2));
    // sphere->addAnimation(anim);

    s->objects.push_back(esfera_blanca);
    s->objects.push_back(sphere_base);
    s->objects.push_back(esfera_metalica);
    //s->objects.push_back(esfera_transparente);
    s->objects.push_back(esfera_verde);
    s->objects.push_back(esfera_fucsia);
    s->objects.push_back(cilindro_transparente);

    s->lights.push_back(light0);
    //s->lights.push_back(light1);

}

Camera *SceneFactoryVirtual::createCamera() {
    // creacio de la camera
    vec3 lookfrom(0, 5.5, 13);
    //vec3 lookfrom(-10, 2, 13);
    vec3 lookat(0,2.1,0);
    float dist_to_focus = length(lookfrom-lookat);
    float aperture = 0.1;
    int pixelsX = 600;
    int pixelsY = 400;
    return( new Camera(lookfrom, lookat, vec3(0,1,0), 20, pixelsX, pixelsY, aperture, dist_to_focus));
}
