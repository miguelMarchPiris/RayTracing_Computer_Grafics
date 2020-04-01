#include "Controller.h"
#include "MaterialTextura.h"

Controller::Controller(QString fileName, SceneFactory::SCENE_FACTORIES s, RenderFactory::RENDER_TYPES rt)
{
    // ETAPA 1: Coonstrucció de l'escena
    // Pot ser una escena virtual (no provinent de dades)
    // O pot ser una escena que prové de dades geolocalitzades (Visualization Mapping)
    // S'usa un Abstract Factory per a construir l'escena, la camera
    // TODO Fase 2: crear les llums i pasar-les a l'escena
    SceneFactory *scFac = createFactory(s);
    Scene *scene;
    scene = scFac->createScene(fileName);

    Camera *camera;
    camera = scFac->createCamera();

    //Creacio de les tres llums
    //Light * l1 = new Light(glm::vec3(-5, 20, 10), glm::vec3(0.1, 0.1, 0.1), glm::vec3(0.7, 0.7, 0.7), glm::vec3(0.7, 0.7,0.7), glm::vec3(0.01f, 0.0f, 0.5f));
    //Light * l2 = new Light(glm::vec3(2, 8, -1), glm::vec3(0.1, 0.1, 0.1), glm::vec3(0.7, 0.7, 0.7), glm::vec3(0.7, 0.7,0.7), glm::vec3(0.01f, 0.0f, 0.5f));
    //Light * l3 = new Light(glm::vec3(2, 8, 10), glm::vec3(0.1, 0.1, 0.1), glm::vec3(0.7, 0.7, 0.7), glm::vec3(0.7, 0.7,0.7), glm::vec3(0.01f, 0.0f, 0.5f));
    Light *light = new Light(vec3(2, 8, -10));
    scene->lights.push_back(light);
    //creacio de la llum d'ambient global ?

    //Afegim les llums a lescena
    //scene->lights.push_back(l1);
    //scene->lights.push_back(l2);
    //scene->lights.push_back(l3);

    // Es crea aqui només un ColorMap
    // TODO Fase 2: Cal tenir en compte tants ColorMaps com numero de propietats, en el cas que el fitxer de dades en
    //  tingui més d'una. On es pot fer això millor?
    ColorMap *colorMap = scFac->createColorMap(ColorMapStatic::ColorMapType::COLOR_MAP_TYPE_INFERNO);
    scene->setMaterials(colorMap); //Aqui me dice valgrind que hay fuga de memoria

    //TODO el ground de la escena debe ser de la dimension de la escena?
    //scene->ground = new FittedPlane(vec3(0,1,0), vec3(0,-1,0), vec2(-10,-10), vec2(10,10), -1);
    //scene->ground->setMaterial(new MaterialTextura());
    //scene->objects.push_back(scene->ground);

    // TODO Fase 1: Cal posar les dimensions de l'escena virtual usant setDimensions de la classe Scene
    //Dimensiones de la escena
    vec3 _pmin (-10,-10,-10);
    vec3 _pmax (10,10,10);

    scene->setDimensions(_pmin, _pmax);

    // ETAPA 2: Inicialitzacio del Rendering
    // usa un Factory Template per a construir el tipus de render
    render = RenderFactory::getInstance()->getRender(rt);
    render->setScene(scene);
    render->setCamera(camera);
    render->numSamples = 10;
}

void Controller::start(int argc, char **argv) {
    // ETAPA 2: Activació del Rendering
    render->startRendering(argc, argv);
}

SceneFactory* Controller::createFactory(SceneFactory::SCENE_FACTORIES factory)
{
    if(factory == SceneFactory::SCENE_FACTORIES::VIRTUAL)
    {
        return new SceneFactoryVirtual();
    }
    else if(factory == SceneFactory::SCENE_FACTORIES::DATA)
    {
        return new SceneFactoryData();
    }
    return nullptr;
}
