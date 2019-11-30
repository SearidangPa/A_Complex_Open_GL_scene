#pragma once

#include "DisplayableObject.h"
#include "Animation.h"
// Pointer index for vertex 0
#define _VERTEX0 0
// Pointer index for vertex 1
#define _VERTEX1 3
// Pointer index for vertex 2
#define _VERTEX2 6
// Pointer index for vertex 3
#define _VERTEX3 9
// Pointer index for vertex 4
#define _VERTEX4 12
// Pointer index for vertex 5

class Bus_Stand_Pole:
public DisplayableObject,
public Animation
{
public:
    Bus_Stand_Pole();
    ~Bus_Stand_Pole();
    Bus_Stand_Pole(const std::string& f1, const std::string& f2, const std::string& f3,
                   const std::string& f4, const std::string& f5, const std::string& f6,
                   const std::string& f7, const std::string& f8);
    void Display();
    void Update(const double& deltaTime);
    
private:
    void Drawcone(float r1, float r2);
    void cylinder(float r, float h, int ind);
    void unit_cylinder(float r, float unit, int ind);
    void texturedCube(GLint texID, bool two_sided);
    void DrawlittleHouse_with_schedule();
    void DrawTriangle(float *a, float *b, float *c);
    void cubeframe(float h, float w);
    void DrawHouseRoof();
    void SpriteFrame_Display(float width, float height, GLuint texID);
    void DrawBanner(float r2);
    void DrawDisplay(float r2, float h2);
    
    GLuint texID1; GLuint texID2; GLuint texID3; GLuint texID4;
    GLuint texID5; GLuint texID6; GLuint texID7; GLuint texID8;

    float r1 = 1, h1 = 7;
    float r2 = 0.65, h2 = 25;
    float box_w = 10, box_h = 2;
    
    float black[3] = {0.0, 0.0, 0.0};
    float grey[3] = {0.25, 0.25, 0.25};
    float white[3] = {1, 1, 1};
    float* _initV = NULL;
    
    float texCoords[8];
    int spriteWidth;
    int spriteFrame;
    double time;
};

