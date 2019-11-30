#pragma once
#include "DisplayableObject.h"

class Floor :
	public DisplayableObject
{
public:
	Floor(){};
	~Floor(){};
    Floor(const std::string& filename, int index, int range);
	void Display();
private:
    GLint texid;
    int index;
    int _range;
    float* _Diffuse;
};
