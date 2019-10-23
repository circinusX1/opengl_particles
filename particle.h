#ifndef PARTICLE_H
#define PARTICLE_H

#include "vertex.h"

void drawScene();

//  Particle Structure

class Scene;
class Particle
{
public:
    friend class Scene;
    friend class Floor;
    friend void drawScene();

    Particle(){}
    virtual ~Particle();
    Particle(const Particle& p);
    Particle& operator=(const Particle& p);

    bool animate(Scene* ps, float dt);
    void render(GLuint t,GLUquadric* q);
    void recycle(const V3& pos, const V3& dir, const CLR& rgb, float vel, float rad, float ttl);
protected:
public:
    //
    float      _rot;
    V3		_fwd;
    V3		_pos;
    CLR    _rgba;  // colour (could be constant across the particle, or a different colour at each vertex)
    V3     _vel;   // particle movement speed (higher is faster, 0 is stationary)
    V3     _rax;   // otation angle (rx, ry, rz) (for rotating/spinning particles)
    float   _rad;   // size  radius
    float   _ttl;   // age (particles have a finite lifespan)
    float   _age;   // age (particles have a finite lifespan)
    float   _angle; // rotation step
};

#endif // PARTICLE_H
