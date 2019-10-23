#ifndef LIGHTBULB_H
#define LIGHTBULB_H

#include "vertex.h"


class LightBulb
{
public:
    LightBulb();
    virtual ~LightBulb();

    void render();
protected:
public:


    V3      _pos;
    CLR     _color;
};

#endif // LIGHTBULB_H
