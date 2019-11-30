#pragma once

#include "../Framework/Engine/Scene.h"

class MyScene :
	public Scene
{
public:
	MyScene(int argc, char** argv, const char *title, const int& windowWidth, const int& windowHeight);
	~MyScene() {};

private:
    void Draw_yellow_strip();
    void Draw_road_divide();
    void Draw_Trees();
    void Draw_Street_Lamp();
    void Draw_sidewalk();
    
	void Initialise();
	void Projection();
    float* wDiffuse;

};
