//
// Created by Marcos Plaza Gonzalez on 29/3/20.
//

#ifndef ROTATE_H
#define ROTATE_H

#include "TG.h"

class Rotate : public TG
{
public:
    Rotate(glm::vec3 rot, float a);
    glm::vec3 rotate;
    float angle;
    ~Rotate();
};

#endif // ROTATE_H