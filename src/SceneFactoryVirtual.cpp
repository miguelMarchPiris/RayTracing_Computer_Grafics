//
// Created by anna on 18/01/2020.
//

#include <include/Cylinder.h>
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
    Sphere * sphere0 = new Sphere(vec3(0, 1, -1), 0.5, 1.0);
    sphere0->setMaterial(new Lambertian(vec3(0.5, 0.5, 0.5)));
    Sphere * sphere1 = new Sphere(vec3(0, -100.5, -1), 100, 1.0);
    sphere1->setMaterial(new Lambertian(vec3(0.8, 0.8, 0)));
    Sphere * sphere2 = new Sphere(vec3(2, 0, -1), 0.5, 1.0);
    sphere2->setMaterial(new Lambertian(vec3(0.8, 0.8, 0)));

    //Cylinder
    Cylinder *cil1 = new Cylinder(vec3(2, 0, -1), 1, 1, 1);
    cil1->setMaterial(new Lambertian(vec3(0.8, 0.8, 0)));

    Light *light = new Light(vec3(2, 8, 10));

    BoundaryObject * cube = new BoundaryObject("../resources/cube.obj", -1);
    cube->setMaterial(new Lambertian(vec3(0.8, 0.8, 0)));

    sphere0->getMaterial()->especular = vec3(1, 1, 1);
    sphere1->getMaterial()->especular = vec3(1, 1, 1);
    sphere2->getMaterial()->especular = vec3(1, 1, 1);
    cube->getMaterial()->especular = vec3(1,1,1);

    cil1->getMaterial()->especular = vec3(1, 1, 1);

    // Animation *anim = new Animation();
    // anim->transf = new Translate(vec3(0.2));
    // sphere->addAnimation(anim);

    s->objects.push_back(sphere0);
    s->objects.push_back(sphere1);
    s->objects.push_back(sphere2);
    s->objects.push_back(cube);

    s->objects.push_back(cil1);

    s->lights.push_back(light);

}

Camera *SceneFactoryVirtual::createCamera() {
    // creacio de la camera
    vec3 lookfrom(13, 2, 3);
    vec3 lookat(0,0,0);
    float dist_to_focus = length(lookfrom-lookat);
    float aperture = 0.1;
    int pixelsX = 600;
    int pixelsY = 400;
    return( new Camera(lookfrom, lookat, vec3(0,1,0), 20, pixelsX, pixelsY, aperture, dist_to_focus));
}
