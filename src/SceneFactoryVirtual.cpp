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
    Cylinder * cil0 = new Cylinder(vec3(0, 0, 0), 0.5, 1, 1.0);
    cil0->setMaterial(new Lambertian(vec3(0.5, 0.5, 0.5)));

    Light *light = new Light(vec3(0, 1, 5));

    cil0->getMaterial()->especular = vec3(1, 1, 1);

    // Animation *anim = new Animation();
    // anim->transf = new Translate(vec3(0.2));
    // sphere->addAnimation(anim);

    s->objects.push_back(cil0);
    s->lights.push_back(light);

}

Camera *SceneFactoryVirtual::createCamera() {
    // creacio de la camera
    vec3 lookfrom(0, 1, 20);
    vec3 lookat(0,0,0);
    float dist_to_focus = length(lookfrom-lookat);
    float aperture = 0.1;
    int pixelsX = 600;
    int pixelsY = 400;
    return( new Camera(lookfrom, lookat, vec3(0,1,0), 20, pixelsX, pixelsY, aperture, dist_to_focus));
}
