
#include <unistd.h>
#include "scene.h"
#include "bmpload.h"

#define MIN_VEL 0.0128f


//                                         < Friction mode toggle – “F” key is the _attn
Scene::Scene(float attn, float grav, float fh):_attn(attn),_grav(grav),_camera(V0,0,0,0)
{
    _spread = 5;
    _collision = true;
    _recycle = true;
    _q = gluNewQuadric();
     gluQuadricOrientation(_q, GLU_OUTSIDE);
    vector<string> files;
    files.push_back("particle.bmp");
    files.push_back("floor.bmp");
    vector<int> tids = loadTextures(files);
    _tx_particle = tids[0];
    _tx_floor    = tids[1];
    _tx_objs     = 0;//loader.LoadBitmap("");
}

Scene::~Scene()
{
    reset();
    glDeleteTextures(1,&_tx_particle);
    gluDeleteQuadric(_q);
}


void Scene::move_cam(float fwd, float side, float up)
{
    _camera.Move(fwd, side, up);
}

void Scene::rot_cam(float azimuth, float elevation, float roll)
{
    _camera.Rotate(azimuth, elevation, roll);
}

// For each particle in the list:
void Scene::animate(float dt)
{
    std::list<Particle*>::iterator b = _particles.begin();
    for(; b!= _particles.end();++b)
    {
        if(false == (*b)->animate(this, dt)) //Update the particle:  see in animate
        {
            //b = _particles.erase(b);
            //recycle;
            if(_recycle)
            {
                _recycle_particle(*b);
            }
            else //Start/Stop Simulation – Space bar
            {

                std::list<Particle*>::iterator bn = _particles.erase(b);
                delete *b;
                b=bn;
                if(b==_particles.end())
                    break;
            }
        }
    }
}

// Animation of Particles
void Scene::render()
{
    glColor4f(1.0, 1.0, 1.0, 0.0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _tx_particle);
    std::list<Particle*>::iterator b = _particles.begin();
    //glColor3f(255,255,255);
    for(; b!= _particles.end();++b)
    {
        (*b)->render(_tx_particle, _q);
    }
    //glEnable(GL_TEXTURE_2D);
     glBindTexture(GL_TEXTURE_2D, _tx_floor);
    _floor.Render();

    render_axis();
    glDisable(GL_TEXTURE_2D);

    this->light_up();
}

void Scene::light_up()
{
    _light.render();
}


void Scene::_recycle_particle(Particle* p)
{
    V3 op = V3(0.0,(_floor._c+PART_SIZE),0); // displayed in the xz plane at y=0   WE DIDI -10 to see it properly
    V3 vy = VY * FRAND(70,100);
    vy.z = FRAND(-_spread,_spread);
    vy.x = FRAND(-_spread,_spread);
    vy.norm();
    p->recycle(op, vy, CLR(FRAND(200,55),FRAND(200,255),FRAND(200,255)),
               FRAND(10,20), PART_SIZE,  FRAND(8,10));
    //usleep(10000+rand()%10000);
}

void Scene::add_particle()
{
    //const V3& pos, const V3& dir, const CLR& rgb, float vel, float rad, float ttl)
    Particle* p = new Particle();
    if(p)
    {
        _recycle_particle(p);
       _particles.push_back(p);
    }
}

void Scene::reset()
{
    std::list<Particle*>::iterator b = _particles.begin();
    for(; b!= _particles.end();++b)
        delete *b;
    _particles.clear();
}

void Scene::render_axis()
{
    glDisable(GL_TEXTURE_2D);

    glBegin(GL_LINES);

        glColor3f(1,0,1);
        glVertex3f(-30, _floor._c+.2, 0.0);
        glVertex3f(+30, _floor._c+.2, 0.0);

        glColor3f(1,1,0);
        glVertex3f(0.0, 30, 0.0);
        glVertex3f(0.0, -30, 0.0);

        glColor3f(0,1,1);
        glVertex3f(0.0, _floor._c+.2, -30);
        glVertex3f(0.0, _floor._c+.2, 30);

    glEnd();
}

void Scene::init_gl()
{
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glDepthMask(GL_TRUE);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
    glEnable(GL_COLOR_MATERIAL);
    glClearDepth( 1 );
    glDisable(GL_FOG);
    glDisable(GL_DITHER);
    glEnable(GL_ALPHA_TEST);
    glEnable(GL_MULTISAMPLE);
    glClearColor(0.0f,0.0f,0.0f,0.f);

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glCullFace(GL_FRONT);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial( GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}
