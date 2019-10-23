

#include "floor.h"
#include "scene.h"
#include "particle.h"


Floor::~Floor()
{

}

// Particle floor collision
void    Floor::Collide(Particle* p, float dt, V3& vect)
{
    if(p->_fwd.vdp(_n)<0) // are we going toward the plane. Fast reject when moving away
    {
        float dist =  FastDistTo(p->_pos);   // yes we do. see how far we are
        if(dist < p->_rad)                  // if we less then radius
        {

            float into = p->_rad - dist;     // how much we went into .. ignored, we use brute force collision point
            //get IP
            V3 inv = vect;
            V3 ip ;
            if(RayIntersect(p->_pos, p->_fwd, ip)) // find intersectin point
            {
                ReflectVector(inv, _n, _bounce, vect);  // reflect vector
            }
            p->_pos = ip + VY * PART_SIZE;
        }
    }
}

void     Floor::Render()
{
    // Render environment (walls, floor, etc.) Just floor
    glColor3ub(100,100,100);

    glBegin(GL_QUADS);
        glTexCoord2f(0, 0);
        glVertex3f(10, _c, -10);

        glTexCoord2f(0, 1);
        glVertex3f(-10, _c, -10);

        glTexCoord2f(1, 1);
        glVertex3f(-10, _c, 10);

        glTexCoord2f(1, 0);
        glVertex3f(10, _c, 10);

    glEnd();
}
