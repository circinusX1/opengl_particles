#ifndef SCENE_H
#define SCENE_H


#include <vector>
#include <list>
#include "vertex.h"
#include "floor.h"
#include "particle.h"
#include "camera.h"
#include "lightbulb.h"


using namespace std;


#define MAX_PARTICLES 80
#define PART_SIZE     0.3f



class Particle;
class Scene
{
public:
    friend class Particle;
    Scene(float attn, float grav, float fh);
    virtual ~Scene();

    void set_friction(float f){_attn=f;}
    void add_particle();
    void reset();
    void set_bounce(float bounce){_floor._bounce=bounce;};
    void set_wind(const V3& wind){_wind=wind;};
    void set_collision(bool collision){_collision=collision;};
    void set_recycle(bool recycle){_recycle=recycle;};
    void move_cam(float fwd, float side, float up);
    const M4 camera_matrix(int){return _camera.GetViewMtx(0);}
    void rot_cam(float side, float up, float fwd);
    void light_up();
    void animate(float dt);
    void render();
    int count(){return _particles.size();}
    Particle* first()const{return *(_particles.begin());}
    void init_gl();
protected:
    void _recycle_particle(Particle* p);
    void render_axis();
private:

    float       _attn;
    float       _grav;
    V3          _wind;
    Floor       _floor;
    GLuint      _tx_particle;
    GLuint      _tx_floor;
    GLuint      _tx_objs;
    GLUquadric* _q;
    int         _spread;
    bool        _collision;
    bool        _recycle;
    Camera      _camera;
    std::list<Particle*> _particles; //Particle List
    LightBulb _light;
};


// we use a struct, all members are public.
struct Mouse
{
    Mouse():button(0),state(1),x(0),y(0)
    {

    }
    int button;
    int state;
    int x;
    int y;
};

#endif // SCENE_H
