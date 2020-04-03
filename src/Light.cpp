//
// Created by franc on 25/03/2020.
//
#include "Light.h"
#include <iostream>

Light::Light(glm::vec3 punt) {
    this->punt = punt;

    ambient = glm::vec3(0.4f, 0.4f, 0.4f);
    difuse = glm::vec3(0.5f, 0.5f, 0.5f);
    especular = glm::vec3(1.f, 1.f, 1.f);
    //coeficient d'atenuacio ?
    attenuation = glm::vec3(0.01f, 0.0f, 0.1f);

}

Light::Light(glm::vec3 punt, glm::vec3 ambient, glm::vec3 difuse, glm::vec3 especular, glm::vec3 attenuation){
    this->punt = punt;
    this->ambient = ambient;
    this->difuse = difuse;
    this->especular = especular;
    this->attenuation = attenuation;
}

Light::~Light() {
    std::cout<<"Llum destruida"<<std::endl;
}

void Light::setCoefAten(float ca) {
    this->coef_aten = ca;
}