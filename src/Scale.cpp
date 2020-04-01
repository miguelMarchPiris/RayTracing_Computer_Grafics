//
// Created by Marcos Plaza Gonzalez on 29/3/20.
//
#include "Scale.h"

Scale::Scale(glm::vec3 scal): scale(scal)
{
    matTG = glm::scale(glm::mat4(1.0f), scale);
}

Scale::Scale(float f)
{
    this->scale1 = f;
}
float Scale::getFloat(){
    return this->scale1;
}

Scale::~Scale()
{

}