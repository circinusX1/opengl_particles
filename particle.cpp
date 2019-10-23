#include "particle.h"
#include "scene.h"

#define MINIMUM_VEL  0.1


Particle::Particle(const Particle& p)
{
    _rgba = p._rgba;
    _vel = p._vel;
    _rad = p._rad;
    _ttl = p._ttl;
    _age = p._age;
}

Particle& Particle::operator=(const Particle& p)
{
    _rgba = p._rgba;
    _vel = p._vel;
    _rad = p._rad;
    _ttl = p._ttl;
    _age = p._age;
    return *this;
}

Particle::~Particle()
{
    //dtor

}

void Particle::recycle(const V3& pos,
                   const V3& fdir,
                   const CLR& rgb,
                   float vel,
                   float rad,
                   float ttl)

{
    _vel = (vel*fdir); // velocity is speed * forward vector
    _rgba = (rgb); // color
    _rad = (rad);  // radius
    _ttl = (ttl); // 1. Particle lifespan
    _age = (0);   // start at age 0
    _pos = pos;   // curent position
    _fwd = fdir;  // foward direction
    _rot = FRAND(1,5); // Particle spin step
    _rax = V3(rand(), rand(), rand());
    _rax.norm();         // Particle spin axes
}

bool Particle::animate(Scene* ps, float dt)
{
   _age += dt;
    if(_age > _ttl)       //compute other state variables for particle (kill/delete if too old, etc.)
        return false;     //object dies, or recycled
    _vel *= ps->_attn;
    float sp = _vel.len();  // compute other state variables for particle (kill/delete if too old, etc.)
    if(sp < MINIMUM_VEL)
        return false;     // object dies, or recycled

    //also check screen boudaries values taken from debug
    if(_pos.y<-12) return false;
    if(_pos.x<-15) return false;
    if(_pos.z<-15) return false;
    if(_pos.z>15) return false;
    if(_pos.x>15) return false;

    V3 np = _vel * dt;
    _vel += (ps->_wind * dt);     // modify direction based on environment variables (gravity, wind, etc.)
    _vel.y += (ps->_grav * dt);  // compute new position (using current position, direction and speed): P’ = P+d*S
    _fwd = _vel;
    _fwd.norm();
    if(ps->_collision)
        ps->_floor.Collide(this, dt, _vel); //Particle floor collision
    np = _vel * dt;
    _pos += np;
    _angle+=_rot;

    //make it reansparent as it ages
    //float leftage = ;
     _rgba.a = 255;// ((_ttl - _age)/_ttl) * 255;
    return true;
}

// Render the particle in its new position/orientation (if it still exists)
void Particle::render(GLuint t,GLUquadric* q)
{
    glPushMatrix();
        glTranslatef(_pos.x,_pos.y,_pos.z);         //Render the particle in its new position/orientation (if it still exists)
       //glColor3ub(_rgba.r, _rgba.g ,_rgba.b);//, 255);//_rgba.a);
        glRotatef(_angle,_rax.x,_rax.y,_rax.z);
        gluQuadricTexture(q, t);
         gluQuadricNormals(q, GLU_SMOOTH);
        gluSphere(q,  GLdouble(_rad),  12,  12);
    glPopMatrix();
}
