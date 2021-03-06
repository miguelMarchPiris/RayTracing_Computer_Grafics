#include "Render.h"



// Metode Render

// Aquesta funcio transforma cada pixel a coordenades de mon i
// envia un raig des de la camera en aquella direccio cridant al metode CastRay
// i pel pintar la imatge final:
// 1) Neteja la pantalla per a visualitzar el nou frame
// 2) Envia un raig a l'escena per a cada pixel de la pantalla i utilitza el color retornat per a pintar el pixel
// 3) Actualitza la sortida corresponent segons la implementació del mètode setPixelColor de cada fill

//Precondicio:
// La Scene ha d'estar creada i inicialitzada

void Render::rendering() {
    // Recorregut de cada pixel de la imatge final
#pragma omp parallel for
    for (int y = cam->viewportY-1; y >= 0; y--) {
         for (int x = 0; x < cam->viewportX; x++) {
            vec3 col(0, 0, 0);
            float u = float(x) / float(cam->viewportX);
            float v = float(y) / float(cam->viewportY);

            Ray r = cam->getRay(u, v);

            //Definimos aqui el numero de samples
            this->numSamples = 16;

            // Antialiasing -> tiramos numSamples rayos por pixel
            // y nos quedamos con la media del color
            for(int i = 0; i < numSamples; i++){
                float u = float(x + drand48()) / float(cam->viewportX);//16 mostres dels subpixels mes propers
                float v = float(y + drand48()) / float(cam->viewportY);
                r = cam->getRay(u, v);
                vec3 subPixelColor = scene->ComputeColorRay(r,0);
                col += subPixelColor;
            }

            col /= vec3(numSamples);


            setPixelColor(col, x, y);
         }
    }
}

void Render::exitRender() {
    cleanup();
}

void Render::cleanup() {
    if (scene!=NULL)  delete scene;
}

// Metode de suport que fa el rendering per a tots els Renders que no usen GLUT
void Render::startRendering(int argc, char **argv) {
    renderingScene();
}

void Render::renderingScene()  {
    initRender("resultat.ppm");
    rendering();
    exitRender();
}

void Render::setCamera(Camera *c) {
    cam = c;
}
void Render::setScene(Scene *s) {
    scene = s;
}

