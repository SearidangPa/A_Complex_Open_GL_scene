#pragma once

#include "DisplayableObject.h"
#include "Input.h"
#include "Animation.h"

class Sun :
	public DisplayableObject,
    public Input
{
public:
	Sun();
	~Sun();

	void Display();
    void HandleKey(unsigned char key, int state, int x, int y);  //for visualization of the light

private:
	GLfloat *_ambient, *_diffuse, *_specular;

	float _runtime;
    bool night_time;
    bool button_pressed;

};

