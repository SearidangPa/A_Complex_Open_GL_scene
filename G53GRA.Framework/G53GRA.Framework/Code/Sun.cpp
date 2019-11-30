#include "Sun.h"
#include<cmath>


Sun::Sun() : _runtime(0.0f), night_time(false), button_pressed(false)
{
	static GLfloat ambient[] =
	{
		0.1f, 0.1f, 0.1f, 1.0f
	};

	static GLfloat diffuse[] =
	{
		0.9f, 0.8f, 0.4f, 1.0f
	};

	static GLfloat specular[] =
	{
		1.0f, 1.0f, 0.0f, 1.0f
	};

	_ambient = ambient;
	_diffuse = diffuse;
	_specular = specular;
}


Sun::~Sun()
{
}
/* press v to visualize or unvisualize the lights */
void Sun::HandleKey(unsigned char key, int state, int x, int y)
{
    //if we don't check the state, visualization will only last when you hold the key
    if (!state) return;
    switch (key){
        case 'n':
            night_time = !night_time;
            button_pressed = true;
            break;
    }
    
}
void Sun::Display()
{
    if (!night_time){
        glPushMatrix();
        glPushAttrib(GL_ALL_ATTRIB_BITS);
        {
            glDisable(GL_LIGHTING);
            glTranslatef(pos[0], pos[1], pos[2]);
            glColor4fv(_diffuse);
            glutSolidSphere(200.0, 10, 10);

            glEnable(GL_LIGHTING);
        }
        glPopAttrib();
        glPopMatrix();
        
        glEnable(GL_LIGHTING);
        
        glLightfv(GL_LIGHT0, GL_AMBIENT, _ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, _diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, _specular);
        
        GLfloat lightpos[] = { pos[0], pos[1], pos[2], 1.0f };
        
        glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
        glEnable(GL_LIGHT0);
    }else{
        if (button_pressed){
            glDisable(GL_LIGHT0);
        }
    }
}
