#pragma once

#include "DisplayableObject.h"
#include "Animation.h"
#include "Input.h"
#include "VectorMath.h"
#include <cstdlib>
#include <iostream>

#include <string>
// Pointer index for vertex 0
#define _VERTEX0 0
// Pointer index for vertex 1
#define _VERTEX1 3
// Pointer index for vertex 2
#define _VERTEX2 6
// Pointer index for vertex 3
#define _VERTEX3 9
// Pointer index for vertex 4

// Cap subdivisons at 7
#define _MAX_RES 7

class Terrain :
public DisplayableObject
{
public:
    Terrain();
    Terrain(const std::string& filename);
    ~Terrain(){}
    
    void Display();

    void SetTexture(const std::string& filename);
    // Manually set resolution
    inline void SetResolution(int r) { _resolution = r >= 0 ? (r > _MAX_RES ? _MAX_RES : r) : 0; }

    
protected:
    void DrawTerrain();
    void SubDivide(int p_recurse, float *a, float *b, float *c, float *d);
    void Drawsquare(float *a, float *b, float *c, float *d);
    
    // ID to bound texture
    int _texID;
    // recursive resolution (increase for finer mesh)
    int _resolution;

    // Initial vertices
    float* _initV;
};

