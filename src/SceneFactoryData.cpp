#include "SceneFactoryData.h"

SceneFactoryData::SceneFactoryData()
{

}

Camera *SceneFactoryData::createCamera() {
    // creacio de la camera
    vec3 lookfrom(2,2,1);
    //vec3 lookfrom(13, 2, 3);
    vec3 lookat(0,0,0);

    float dist_to_focus = 2;

    float aperture = 0.5;
    int pixelsX = 600;
    int pixelsY = 400;

    return ( new Camera(lookfrom, lookat, vec3(0,1,0), 90, pixelsX, pixelsY, aperture, dist_to_focus));

}

Scene *SceneFactoryData::createScene(QString filename) {
    Scene *s = new Scene();
    DataReader *sc = new DataReader(s);
    // TODO: Fase 1: construccio de l'escena dins de dataReader
    sc->readFile(filename);
    return s;
}

Scene *SceneFactoryData::createScene(){
    Scene *s = new Scene();
    Sphere * sphere = new Sphere(vec3(0, 0, -1), 0.5, 1.0);
    sphere->setMaterial(new Lambertian(vec3(0.5, 0.2, 0.7)));
    Light *light = new Light(vec3(0, 1, 0));

    //    Animation *anim = new Animation();
    //    anim->transf = new Translate(vec3(0.2));
    //    sphere->addAnimation(anim);

    s->objects.push_back(sphere);
    s->lights.push_back(light);
    return s;
}

ColorMap *SceneFactoryData::createColorMap(ColorMapStatic::ColorMapType t) {
    ColorMap *cm = new ColorMapStatic(t);
    return cm;
}
