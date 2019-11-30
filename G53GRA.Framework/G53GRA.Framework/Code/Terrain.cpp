#include "Terrain.h"


// Default Constructor
Terrain::Terrain()
: _resolution(4), _texID(NULL)
{
    // sqaure vertices (used for initial triangle faces)
    static float vertices[] =
    {
        -0.5f, 0, -0.5f,   // VERTEX 0
        -0.5f, 0, 0.5f,    //VERTEX 1
        0.5f, 0, 0.5f,    // VERTEX 2
        0.5f, 0, -0.5f,   // VERTEX 3
    };
    // Globalise vertices
    _initV = vertices;
}

// Constructor with Texture filename
Terrain::Terrain(const std::string& filename) : Terrain()
{
    SetTexture(filename);
}

void Terrain::SetTexture(const std::string& filename)
{
    // Load texture using the provided Texture loader (.bmp only)
    _texID = Scene::GetTexture(filename);
}

void Terrain::Display()
{
    // Push MODELVIEW matrix and attributes to respective stacks (save state)
    glPushMatrix();
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    
    glColor3f(0.3, 0.8, 0.2);
    
    // Project from Object Space to World Space
    glTranslatef(pos[0], pos[1], pos[2]);               // Position
    glScalef(scale[0], scale[1], scale[2]);             // Scale
    glRotatef(rotation[0], 1.f, 0.f, 0.f);              // Set orientation (X)
    glRotatef(rotation[1], 0.f, 1.f, 0.f);              // Set orientation (Y)
    glRotatef(rotation[2], 0.f, 0.f, 1.f);              // Set orientation (Z)
    
    // Enable texturing (2D image as texture)
    glEnable(GL_TEXTURE_2D);
    // Bind input texture to GL_TEXTURE_2D buffer
    glBindTexture(GL_TEXTURE_2D, _texID);
    // Handle lighting effects
    glEnable(GL_COLOR_MATERIAL);
    
    // Render sphere
    DrawTerrain();
    
    // Unbind the texture
    glBindTexture(GL_TEXTURE_2D, NULL);
    // Disable texturing
    glDisable(GL_TEXTURE_2D);
    
    // Pop matrix and attribute stack to revert transformation changes
    glPopAttrib();
    glPopMatrix();
}

void Terrain::DrawTerrain()
{
    // Subdivide each face of a sqaure (_resolution = number of divisions)
    // and then render the final subdivisions of each face
    SubDivide(_resolution, &_initV[_VERTEX0], &_initV[_VERTEX1], &_initV[_VERTEX2], &_initV[_VERTEX3]);

}

void Terrain::SubDivide(int recurse_idx, float *a, float *b, float *c, float *d)
{
    // Recursively subdivide faces
    float salt = 0;  //salt helps make the terrain have ups and downs which is more realistic to real life terrain
    if (recurse_idx > 0)
    {
        if (recurse_idx==1){
            salt = 0.006;
        }
        else if (recurse_idx==2){
            salt = -0.005;
        }
        else if (recurse_idx==3){
            salt = 0.007;
        }
        else if (recurse_idx==4){
            salt = -0.003;
        }
        // Calcuate mid point between each pair of triangle vertices (a,b,c)
        float ab[3] = { (a[0] + b[0])*0.5f, (a[1] + b[1])*0.5f, (a[2] + b[2])*0.5f};
        float bc[3] = { (b[0] + c[0])*0.5f, (b[1] + c[1])*0.5f, (b[2] + c[2])*0.5f};
        float cd[3] = { (c[0] + d[0])*0.5f, (c[1] + d[1])*0.5f, (c[2] + d[2])*0.5f};
        float da[3] = { (d[0] + a[0])*0.5f, (d[1] + a[1])*0.5f, (d[2] + a[2])*0.5f};
        float m[3]  ={ (ab[0] + cd[0])*0.5f, (ab[1] + cd[1])*0.5f + salt, (ab[2] + cd[2])*0.5f};
        
        SubDivide(recurse_idx - 1, a, ab, m, da);
        SubDivide(recurse_idx - 1, ab, b, bc, m);
        SubDivide(recurse_idx - 1, m, bc, c, cd);
        SubDivide(recurse_idx - 1, da, m, cd, d);        
    }
    // Draw final subdivision faces
    else
    {
        Drawsquare(a, b, c, d);
    }
}

/* draw squares with specified normal and texel for each vertex */
void Terrain::Drawsquare(float *a, float *b, float *c, float *d)
{
    glBegin(GL_QUADS);
    // vertex a
    glNormal3fv(a);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3fv(a);
    // vertex b
    glNormal3fv(b);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3fv(b);
    // vertex c
    glNormal3fv(c);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3fv(c);
    // vertex c
    glNormal3fv(d);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3fv(d);
    glEnd();
    

}

