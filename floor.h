#ifndef FLOOR_H
#define FLOOR_H

#include "vertex.h"
#include "hole.h"
#include <vector>

class Particle;
class Floor : public Plane
{
public:
    Floor(){
        _bounce = 0.68f; // 4. Friction mode toggle – “F” key and G  (incerase decrese)
        _n=VY;
        _c=-10.f;
    };
    virtual ~Floor();

    void    AddHole(Hole& hole){_holes.push_back(hole);}
    void    Collide(Particle* p, float dt, V3& reflect);
    void    Render();
protected:
public:
    float                _bounce; //
    float                _stick;
    std::vector<Hole >  _holes;
};

#endif // FLOOR_H
