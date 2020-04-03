//
// Created by anna on 20/01/2020.
//

#include "Texture.h"

Texture::Texture(QString nomfitxer)
{
    if(nomfitxer.toStdString()[0] == ' ')
        nomfitxer = nomfitxer.remove(0, 1);
    //cout << nomfitxer.toStdString() << endl;
    bool success = image.load(nomfitxer);

    if (!success) std::cout << "Imatge no trobada" << endl;

}
Texture::~Texture() {

}

//Amb aixo obtenim el pixel corresponent a la coordenada (u,v) amb u i v pertanyents a l'interval [0,1]
vec3 Texture::getColorPixel(vec2 uv) {
    QColor c(image.pixel((uv.x)*image.width(), (uv.y)*image.height() ));
    return(vec3(c.redF(), c.greenF(), c.blueF()));
}