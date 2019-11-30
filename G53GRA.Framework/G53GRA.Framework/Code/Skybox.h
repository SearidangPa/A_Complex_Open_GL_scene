#pragma once

#include "DisplayableObject.h"
#include "Input.h"

class Skybox : 
	public DisplayableObject,
    public Input
{
public:
	Skybox(GLuint texTop, GLuint texLeft, GLuint texRight, GLuint texNear, GLuint texFar);
	~Skybox();

	void Display();
    void HandleKey(unsigned char key, int state, int x, int y);
private:
	GLuint _texTop, _texLeft, _texRight, _texNear, _texFar;
    bool night_time;
    
};
