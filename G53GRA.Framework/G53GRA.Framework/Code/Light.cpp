#include "Light.h"
#include <cmath>

Light::Light(int index, GLfloat* position, GLenum lightnum1, GLenum lightnum2) :
isVisualized(false), turn_on(false), button_pressed(false)
{
    //default properties of the light if nothing is specified
    static GLfloat ambient[] ={ 0.1f, 0.1f, 0.1f, 1.0f};
    static GLfloat diffuse[] = {0.9f, 0.8f, 0.4f, 1.0f};
    static GLfloat specular[] = {1.0f, 1.0f, 0.0f, 1.0f};
    
    _position = position;
    _ambient = ambient;
    _diffuse = diffuse;
    _specular = specular;
    _lightnum1 = lightnum1;
    _lightnum2 = lightnum2;

}

Light::~Light(){}


/* draw the lights if choose to visualize them */
void Light::Display()
{
    if (isVisualized) {         //to visualize where the light is placed
        glPushAttrib(GL_ALL_ATTRIB_BITS);
        glPushMatrix();
        
        glColor4fv(_ambient);  //set the color of the sphere the same as the ambient light
        glTranslatef(_position[0], _position[1], _position[2]);
        glutSolidSphere(30.0f, 10, 10);
        
        glPopMatrix();
        glPopAttrib();
    }
    if (turn_on){
        //enable lighting
        glEnable(GL_LIGHTING);
        
        /* the first light is a spot light facing down */
        float Spot_dir[] = {0.f, -1.f, 0.f};
        
        /*set the property of the light object*/
        glLightfv(_lightnum1, GL_POSITION, _position);
        glLightfv(_lightnum1, GL_AMBIENT, _ambient);
        glLightfv(_lightnum1, GL_DIFFUSE, _diffuse);
        glLightfv(_lightnum1, GL_SPECULAR, _specular);
        
        glLightfv(_lightnum1, GL_SPOT_DIRECTION, Spot_dir);
        glLightf(_lightnum1, GL_SPOT_EXPONENT, 0.7f);
        glLightf(_lightnum1, GL_SPOT_CUTOFF, 90.f);
        
        glEnable(_lightnum1);
        
        /* the second light is a spot light facing up to light up
           the head of the street lamp */
        float Spot_dir1[] = {0.f, 1.f, 0.f};
        static GLfloat ambient1[] ={ 0.5f, 0.5f, 0.f, 1.0f};
        static GLfloat diffuse1[] = {0.5f, 0.5f, 0.f, 1.0f};
        
        glLightfv(_lightnum2, GL_POSITION, _position);
        glLightfv(_lightnum2, GL_AMBIENT, ambient1);
        glLightfv(_lightnum2, GL_DIFFUSE, diffuse1);
        glLightfv(_lightnum2, GL_SPECULAR, _specular);
        
        glLightfv(_lightnum2, GL_SPOT_DIRECTION, Spot_dir1);
        glLightf(_lightnum2, GL_SPOT_EXPONENT, 5.f);
        glLightf(_lightnum2, GL_SPOT_CUTOFF, 60.f);
        glEnable(_lightnum2); 
    }
    
    else{
        if (button_pressed){
            glDisable(_lightnum1);
            glDisable(_lightnum2);
        }
    }
    
    
}

/* press v to visualize or unvisualize the lights */
void Light::HandleKey(unsigned char key, int state, int x, int y)
{
    //if we don't check the state, visualization will only last when you hold the key
    if (!state) return;
    switch (key){
        case 'v':
            isVisualized = !isVisualized;
            break;
        case 'n':
            turn_on = !turn_on;
            button_pressed = true;
            break;
    }
}

