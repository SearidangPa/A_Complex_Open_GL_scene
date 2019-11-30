#pragma once

#include "DisplayableObject.h"

class Lamp_post:
public DisplayableObject
{
public:
    Lamp_post();
    ~Lamp_post();
    Lamp_post(const std::string& file1, const std::string& file2, const std::string& file3);
    void Display();
private:
    void Drawcone(float r1, float r2);
    void textured_cylinder(float r, float h);
    void half_textured_cylinder(float r, float h);
    void texturedCube(GLuint texID);
    GLuint texID1;GLuint texID2; GLuint texID3;
    
    float r1 = 1, h1 = 7;
    float r2 = 0.6, h2 = 25;
    float r3 = 0.2, h3 = 8;
    float white[4] = {1, 1, 1, 1};
    float yellow[4] = {1, 1, 0, 1};
};

