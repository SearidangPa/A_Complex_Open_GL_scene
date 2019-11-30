#include "DisplayableObject.h"
#include "Input.h"

#define _LIGHT0_ 0
#define _LIGHT1_ 4

class Light :
public DisplayableObject,
public Input
{
public:
    Light(int index, GLfloat* position, GLenum lightnum1, GLenum lightnum2);
    ~Light();
    
    void Display();
    void HandleKey(unsigned char key, int state, int x, int y);  //for visualization of the light
    
private:
    GLenum _lightnum1;  GLenum _lightnum2;                //the light numbers
    GLfloat *_ambient, *_diffuse, *_specular, *_position; //the properties of the light
    bool isVisualized;                                    //whether the light ball is visualized
    bool turn_on;
    bool button_pressed;
};
