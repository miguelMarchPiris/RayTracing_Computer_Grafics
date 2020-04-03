//
// Created by Marcos Plaza Gonzalez on 29/3/20.
//
#ifndef SCALE_H
#define SCALE_H

#include "TG.h"

class Scale : public TG
{
public:
    glm::vec3 scale;
    float scale1;
    Scale(glm::vec3 scal);
    Scale(float f);
    float getFloat();
    void setFloat(float);
    ~Scale();
};

#endif // SCALE_H