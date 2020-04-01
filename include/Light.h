//
// Created by franc on 25/03/2020.
//

#ifndef RAYDATA_LIGHT_H
#define RAYDATA_LIGHT_H
#include "glm/glm.hpp"

class Light{
public:
    Light(glm::vec3 punt);

    //Constructor amb parametres
    Light(glm::vec3 punt, glm::vec3 ambient, glm::vec3 difuse, glm::vec3 especular, glm::vec3 attenuation);

    ~Light();

    glm::vec3 punt;
    glm::vec3 ambient; //Ka
    glm::vec3 difuse; //kd
    glm::vec3 especular; //Ks
    glm::vec3 attenuation; //beta?
};

#endif //RAYDATA_LIGHT_H
