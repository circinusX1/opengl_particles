#include "lightbulb.h"





LightBulb::LightBulb()
{
    //ctor
}

LightBulb::~LightBulb()
{
    //dtor
}


GLfloat aspec[]={0.0, 0.0 ,1.0 ,1.0};      //sets specular highlight of balls
GLfloat aposl[]={8,0,0,1};               //position of ligth source
GLfloat aamb[]={0.01f, 0.01f, 0.01f ,1.0f};   //global ambient
GLfloat aamb2[]={0.01f, 0.01f, 0.01f ,1.0f};  //ambient of lightsource

void LightBulb::render()
{
 	float adf=100.0;

    glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0,GL_POSITION,aposl);
	glLightfv(GL_LIGHT0,GL_AMBIENT,aamb2);

	glEnable(GL_LIGHT0);

	glMaterialfv(GL_FRONT,GL_SPECULAR,aspec);
	glMaterialfv(GL_FRONT,GL_SHININESS,&adf);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,aamb);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);

}
