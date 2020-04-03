//
// Created by franc on 25/03/2020.
//
#include "Light.h"
#include <iostream>

Light::Light(glm::vec3 punt, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 attenuation) {
    this->punt = punt;
    this->Kambient = ambient;
    this->Kdiffuse = diffuse;
    this->Kspecular = specular;
    this->attenuation = attenuation;
}

Light::~Light() {
    std::cout<<"Llum destruida"<<std::endl;
}
