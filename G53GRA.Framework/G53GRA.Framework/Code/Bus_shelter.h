
#pragma once
    
#include "DisplayableObject.h"
#include "Animation.h"
    
#include <string>
    
class Bus_shelter:
public DisplayableObject,
public Animation
{
public:
    Bus_shelter();
    Bus_shelter(const std::string& f1, const std::string& f2, const std::string& f3);
    ~Bus_shelter(){};
    
    void Display();
    void Update(const double& deltaTime);
    
private:
    GLint texID1;
    GLint texID2;
    GLint texID3;
    void DrawLeftside();
    void DrawRightside();
    void DrawBackside();
    void DrawBackbars();
    void DrawTop();
    void Drawseat();
    void TexturedCube(GLint texID);
    void SpriteFrame_Display(float width, float height, GLuint texID);
    
    float top_width = 50, top_height = 1,  top_thick = 13;
    float pole_width = 1, pole_height = 20, pole_thick = 0.5;
    float black[3] = {0.1, 0.1, 0.1};
    float red[3] = {0.5, 0.0, 0.0};
    float white[3] = {1, 1, 1};
    
    float texCoords[8];
    int spriteWidth;
    int spriteFrame;
    double time;
    float sCoord;
};
    

    
    


    
    
    
