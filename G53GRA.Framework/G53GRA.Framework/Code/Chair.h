#pragma once

#include "DisplayableObject.h"

#include <string>

class Chair:
public DisplayableObject
{
public:
    Chair();
    Chair(const std::string& filename);
    ~Chair(){}
    
    void Display();
    
private:
    void Textured_Cube();
    void Draw_back();
    void Draw_Connector();
    void Draw_horizontal_seat();
    void Draw_left_leg();
    void Draw_right_leg();
    
    GLint texID;
    
    float leg_height = 6;
    float dist_back_leg_to_front_leg = 6;
    float dist_left_leg_to_right_leg = 20;
    float wood_slice_thickness = dist_back_leg_to_front_leg/6;
    float gap_horizontal_seat = dist_back_leg_to_front_leg/7.5;
    float gap_back = 2;
};

