

#include <unistd.h>
#include <stdio.h>
#include "bmpload.h"
#include "scene.h"
#include "vertex.h"



const int TIMER_MS = 25; // The number of milliseconds to which the timer is set.
                         // Usually is calculated from frame to frame
Scene*          _PS;     // global scene instance

V3 VY = V3(0,1,0);       //
V3 V0 = V3(0,0,0);

//globals for main and callbacks
float   ViewAngle = 0;
bool    Bleavetrail=true;
bool    Freeze = false;
bool    Kamera=false;
bool    Recycle =true;
float   Bounce = 8.0f;
V3      Wind=V0;
bool    Reset=false;
bool    Collision=true;
int     H=800;
int     W=600;
bool    Light=false;
char    Tout[128]="*";

Mouse       MouseState;

void displayText( float x, float y, const char *sss )
{
    glDisable(GL_TEXTURE_2D);
    glPushMatrix();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRasterPos3f(x, y, -1);

    for (const char* c=sss; *c != '\0'; c++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
    }
    glPopMatrix();
}


void handleKeypress(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        delete _PS;
        _PS=0;
        exit(0);
    case 'k':           // lower Z
        Kamera=!Kamera;
        break;
    case 't':
        Bleavetrail=!Bleavetrail; // trail mode
        sprintf(Tout,"Leave Trail is: %d", Bleavetrail);
        break;
    case 'z' :
        Freeze=!Freeze;
        sprintf(Tout, "Particle Freeze is: %d", Freeze);
        break;
    case 'x':
        Recycle=!Recycle;
        sprintf(Tout, "Particle Recycle is: %d", Recycle);
        _PS->set_recycle(Recycle);
        break;
    case 'f':
    case 'g':
        if(key=='f'||key=='F')
        {
            Bounce+=.01;
        }
        else
        {
            Bounce-=.01;
        }
        if(Bounce>1.0f)
            Bounce=1.0f;
        if(Bounce<0.1f)
            Bounce=0.1f;
        _PS->set_bounce(Bounce);
        sprintf(Tout, "Bouncing factor is is: %f",Bounce );
        break;
    case 'b':
        if(Wind.x==0&&Wind.y==0&&Wind.z==0)
        {
            Wind.x=FRAND(-6,6);
            Wind.z=FRAND(-6,6);
        }
        else
        {
            Wind.x=Wind.y=Wind.z=0;
        }
        sprintf(Tout, "Wind is %f, %f",Wind.x,Wind.y);
        _PS->set_wind(Wind);
        break;
    case 'c':
        Collision=!Collision;
        sprintf(Tout, "Collision is :%d",Collision);
        _PS->set_collision(Collision);
        break;
    case 'r':
        Reset=!Reset;
        sprintf(Tout, "Reset is :%d",Reset);
        if(Reset)
            _PS->reset();
        break;
    case 'w':
        _PS->move_cam(.2f,0,0); //along z
        break;
    case 's':   //back movement
        _PS->move_cam(-.2f,0,0); //along z
        break;
    case 'a':
        _PS->move_cam(0,-0.2f,0.0f); //along z
        break;
    case 'd':   //right
        _PS->move_cam(0,0.2f,0.0f); //along z
        break;
    case 'l':   //right
        Light=!Light;
        sprintf(Tout, "Light is :%d",Light);
        break;
    default:
        break;
    }
}

void mouseFunc(int but, int state, int x, int y)
{
    MouseState.button=but;
    MouseState.state=state;
    MouseState.x=x;
    MouseState.y=y;
    //cout << MouseState.button << " " << MouseState.state << "\n";
}

void motionFunc( int x, int y )
{
    if(MouseState.button==0 && MouseState.state==0)
    {
        int dx = x - MouseState.x;
        int dy = y - MouseState.y;

        MouseState.x=x;
        MouseState.y=y;
        // the 128 value was taken by testing and testing to smooth the rotation
        _PS->rot_cam((float)dx/128.0f,(float)dy/128.0f,0);
    }
}


void handleResize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
    H=h;
    if(H==0)H=1;
    W=w;
    if(W==0)W=1;  //no 0 dividsion in drawScene
}


void drawScene()
{
    usleep(1000); //lower the cpu rate
    if(Bleavetrail)
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clear frame buffer
    glViewport(0, 0, W, H);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0f,(float)H/(float)W, 1.0, 200.f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    if(Light)
        glEnable(GL_LIGHTING);
    else
        glDisable(GL_LIGHTING);

    glPushMatrix();
    if(Kamera && _PS->count()) // glue POV to first particle
    {
        Particle* pf =  _PS->first();
        glTranslatef(pf->_pos.z,pf->_pos.y,pf->_pos.z);
        glRotatef(pf->_angle, pf->_rax.x,pf->_rax.y,pf->_rax.z);
    }
    else
    {
        const M4&  mt = _PS->camera_matrix(0);
        glLoadMatrixf((float*)&mt);  // load camera matrix
    }
    _PS->render();
    glPopMatrix();

    //show some help on screen
    const float Xright=0.28;
    const float Xleft=0.42;
    float Ytop=0.52;
    const float Linew = 0.03;
    glColor4f(1.0, 0.0, 0.0, 0.0);
    displayText(-Xleft,Ytop,"X stops/starts simulation.");
    Ytop-=Linew;
    displayText(-Xleft,Ytop,"A and D  left right");
    Ytop-=Linew;
    displayText(-Xleft,Ytop,"W and S  forward back");
    Ytop-=Linew;
    displayText(-Xleft,Ytop,"mouse click and move, rotates");
    Ytop-=Linew;
    displayText(-Xleft,Ytop,"F and G  decrease incerase the bouncing friction factor");
    Ytop-=Linew;
    displayText(-Xleft,Ytop,"T  toggles trail on and off");
    Ytop-=Linew;
    displayText(-Xleft,Ytop,"C  toggles floor collision");
    Ytop-=Linew;
    displayText(-Xleft,Ytop,"B  toggles random x,y blowing wind");
    Ytop-=Linew;
    displayText(-Xleft,Ytop,"R reset");
    Ytop-=Linew;
    displayText(-Xleft,Ytop,"L light on off");
    Ytop-=Linew;
    displayText(-Xleft,Ytop,"Z freeze/unfreeze");

    //curent action text
    glColor4f(1.0, 0, 1.0, 0.0);
    displayText(Xright,Ytop,Tout);

    glutSwapBuffers();
}




void update(int value)
{
    if(!Freeze)
        _PS->animate((float)TIMER_MS/1000.0);
    glutPostRedisplay();
    glutTimerFunc(TIMER_MS, update, 0);

    if(Recycle == true && Reset==false && _PS->count() < MAX_PARTICLES)
    {
        _PS->add_particle();
    }
}

GLfloat amb[]= {0.4f, 0.4f, 0.4f ,1.0f};  //global ambient

int main(int argc, char** argv)
{
    srand((unsigned int)time(0));

    cout << "X  stops simulation. \n";
    cout << "A and D  keft right\n";
    cout << "W and S  forward back\n";
    cout << "mouse click and move, rotates\n";
    cout << "F and G  decrease incerase the bouncing friction factor\n";
    cout << "T  toggles trail on and off \n";
    cout << "C  toggles floor collision \n";
    cout << "B  toggles random x,y blowing wind \n";
    cout << "R reset \n";
    cout << "L light on off \n";
    cout << "Z freeze/unfreeze \n";

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); //ou should use backface culling and double buffering.
    glutInitWindowSize(800, 600);
    glutCreateWindow("particles demo");
    _PS = new Scene(0.9999f, -9.81f, -10.0f);
    _PS->move_cam(-20.0,20,0);
    _PS->rot_cam(G2R(-45),0,0);
    // we add the particles in the update() function till they reach the count

    glutDisplayFunc(drawScene);
    glutKeyboardFunc(handleKeypress);
    glutReshapeFunc(handleResize);
    glutTimerFunc(TIMER_MS, update, 0);

    glutMouseFunc( mouseFunc );
    glutMotionFunc( motionFunc );

    _PS->init_gl();

    glutMainLoop();
    delete _PS ;
    return 0;
}









