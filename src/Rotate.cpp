//
// Created by Marcos Plaza Gonzalez on 29/3/20.
//
#include "Rotate.h"

Rotate::Rotate(glm::vec3 rot, float a): rotate(rot), angle(a)
{
    matTG = glm::rotate(glm::mat4(1.0f), angle, rotate);

}

Rotate::~Rotate(){

}