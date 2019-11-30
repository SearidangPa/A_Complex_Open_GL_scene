#include "Lamp_post.h"
#include "VectorMath.h"
#define _TRACK_RADIUS 20.0f
#define _ACCELERATION 10.0f

Lamp_post::Lamp_post() {}
Lamp_post::Lamp_post(const std::string& file1, const std::string& file2, const std::string& file3) : Lamp_post()
{
    texID1 = Scene::GetTexture(file1);
    texID2 = Scene::GetTexture(file2);
    texID3 = Scene::GetTexture(file3);
}

Lamp_post::~Lamp_post(){}

void Lamp_post::Display()
{
    glPushMatrix();
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    
    // Project from Object Space to World Space
    glTranslatef(pos[0], pos[1], pos[2]);               // Position
    glScalef(scale[0], scale[1], scale[2]);             // Scale
    glRotatef(rotation[0], 1.f, 0.f, 0.f);              // Set orientation (X)
    glRotatef(rotation[1], 0.f, 1.f, 0.f);              // Set orientation (Y)
    glRotatef(rotation[2], 0.f, 0.f, 1.f);              // Set orientation (Z)
    
    //draw the base cylinder
    glColor3f(1, 1, 1);
    textured_cylinder(r1, h1);
    glTranslatef(0, h1, 0);
    
    glColor3f(0.2, 0.3, 0.28);
    Drawcone(r1, r2);
    
    glTranslatef(0, 0.5, 0);
    glColor3f(1, 1, 1);
    //draw the second cylinder
    textured_cylinder(r2, h2);
    glTranslatef(0, h2-1, 0);
    
    //draw the cylinder part that support the head lamp
    glPushMatrix();{
        glRotated(-80, 0, 0, 1);
        textured_cylinder(r3, h3);
    }glPopMatrix();
    
    //draw the polygonal part that support the head lamp
    glPushMatrix();{
        glTranslatef(h3+1.3, 1.2, 0);
        glPushMatrix();{
            glColor3f(0.2, 0.3, 0.28);
            glScaled(3.5, 1.2, 1.5);
            glutSolidCube(1);
        }glPopMatrix();
        
        //draw the headlamp
        glDisable(GL_COLOR_MATERIAL);
        static GLfloat mat_specular[] = { 1.f, 1.f, 1.f, 1.f };
        glMaterialfv(GL_FRONT, GL_AMBIENT, white);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);

        glTranslatef(0, -0.5, 0);
        glScaled(3, 0.8, 1);
        glutSolidCube(1);
    }glPopMatrix();
    
    /*  display the traffic sign */
    glPushMatrix();{
        glTranslatef(0, -h2*0.5, r2);
        glScaled(4, 6, 0.1);
        glColor3f(1,1,1);
        texturedCube(texID2);
    }glPopMatrix();
    
    /* display the number of the lamp using textured the half cylinder method below*/
    glTranslatef(0, -h2*0.7, 0);
    glRotated(90, 0, 1, 0);
    half_textured_cylinder(r2, 3);
    
    glPopAttrib();
    glPopMatrix();
}



void Lamp_post::Drawcone(float r1, float r2)
{
    float th = 0.0f, res = 2.0f * M_PI / 30.0f;
    float x1 = 0.0, z1 = 0.0;
    float x2 = 0.0, z2 = 0.0;
    float h2 = 0.5;
    float h1 = 0;
    /* draw the outmost layer of the wheel*/
    glBegin(GL_TRIANGLE_STRIP);
    do
    {
        x1 = r1*cos(th); z1 = r1*sin(th);
        x2 = r2*cos(th); z2 = r2*sin(th);
        glVertex3f(x2, h2, z2);
        glVertex3f(x1, h1, z1);
        th += res;
        
    } while (th <= 2.0f * M_PI);
    glEnd();
    
    /* draw the outmost layer of the wheel*/
    glBegin(GL_TRIANGLE_STRIP);
    do
    {
        x1 = r1*cos(th); z1 = r1*sin(th);
        x2 = r2*cos(th); z2 = r2*sin(th);
        glVertex3f(x2, h2, z2);
        glVertex3f(x1, h1, z1);
        th -= res;
        
    } while (th >=0);
    glEnd();
}

void Lamp_post::half_textured_cylinder(float r, float h)
{
    glPushAttrib(GL_ALL_ATTRIB_BITS);       // save current style attributes
    
    float res = 0.1f * M_PI ;               // resolution (in radians: equivalent to degrees)
    float x = 0, z = 0.f;                   // initialise x and z on right of cylinder centre
    float t = 0.f;                          // initialise angle as 0
    
    float a1, a2, b1, b2; a1=a2=b1=b2=0;
    glRotated(180, 0, 0, 1);
    glEnable(GL_TEXTURE_2D);                // enable texturing
    glBindTexture(GL_TEXTURE_2D, texID3);   // bind 2D texture to shape
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    do
    {                                    // create branch with multiple QUADS
        glBegin(GL_QUADS);
        // Create first points (with normals)
        glNormal3f(x, 0.f, z);          // define a normal facing out from the centre (0,0,0)
        
        glTexCoord2f(a1, 1.0);
        glVertex3f(x, 0.f, z);          // bottom (with normal (x,0,z))
        
        glTexCoord2f(b1, 0.f);          // assign texture coordinates to next vertex (u,v) = (0,1)
        glVertex3f(x, h, z);            // top (with normal (x,0,z))
        // Iterate around circle
        t += res;                       // add increment to angle
        x = r*cos(t);                   // move x and z around circle
        z = r*sin(t);
        a2 += res/3;
        b2 += res/3;
        // Close quad (with new vertex normals)
        glNormal3f(x, 0.f, z);          // define a new normal now that x,z have moved around
        glTexCoord2f(b2, 0);            // assign texture coordinates to next vertex (u,v) = (1,1)
        glVertex3f(x, h, z);            // top
        glTexCoord2f(a2, 1.f);          // assign texture coordinates to next vertex (u,v) = (1,0)
        glVertex3f(x, 0.f, z);          // bottom
        a1 = a2;
        b1 = b2;
        glEnd();

    } while (t <= M_PI);                // full rotation around circle
    glDisable(GL_TEXTURE_2D);    // disable texturing following this point
    
    glPopAttrib();
}

void Lamp_post::textured_cylinder(float r, float h)
{
    glPushAttrib(GL_ALL_ATTRIB_BITS);       // save current style attributes

    float res = (float)0.2f*M_PI;           // resolution (in radians: equivalent to 18 degrees)
    float x = 0, z = 0.f;                   // initialise x and z on right of cylinder centre
    float t = 0.f;                          // initialise angle as 0
    
    glDisable(GL_COLOR_MATERIAL);
    // Define the specular material colour property K_s
    static GLfloat mat_specular[] = { 1.f, 1.f, 1.f, 1.f };
    // Define the shininess/specular exponent factor n ( capped between 0.0 and 128.0 )
    static GLfloat mat_shininess[] = { 100.0 };
    
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    
    glEnable(GL_TEXTURE_2D);                // enable texturing
    glBindTexture(GL_TEXTURE_2D, texID1);   // bind 2D texture to shape
    
    do
    {                                   // create branch with multiple QUADS
        glBegin(GL_QUADS);
        // Create first points (with normals)
        glNormal3f(x, 0.f, z);          // define a normal facing out from the centre (0,0,0)
        glTexCoord2f(0.f, 0.f);         // assign texture coordinates to next vertex (u,v) = (0,0)
        glVertex3f(x, 0.f, z);          // bottom (with normal (x,0,z))
        
        glTexCoord2f(0.f, 1.f);         // assign texture coordinates to next vertex (u,v) = (0,1)
        glVertex3f(x, h, z);            // top (with normal (x,0,z))
        // Iterate around circle
        t += res;                       // add increment to angle
        x = r*cos(t);                   // move x and z around circle
        z = r*sin(t);
        // Close quad (with new vertex normals)
        glNormal3f(x, 0.f, z);          // define a new normal now that x,z have moved around
        glTexCoord2f(1.f, 1.f);         // assign texture coordinates to next vertex (u,v) = (1,1)
        glVertex3f(x, h, z);            // top
        
        glTexCoord2f(1.f, 0.f);         // assign texture coordinates to next vertex (u,v) = (1,0)
        glVertex3f(x, 0.f, z);          // bottom
        glEnd();
    } while (t <= 2.1 * M_PI);          // full rotation around circle
    
    do
    {                                    // create branch with multiple QUADS
        glBegin(GL_QUADS);
        // Create first points (with normals)
        glNormal3f(x, 0.f, z);          // define a normal facing out from the centre (0,0,0)
        glTexCoord2f(0.f, 0.f);         // assign texture coordinates to next vertex (u,v) = (0,0)
        glVertex3f(x, 0.f, z);          // bottom (with normal (x,0,z))
        
        glTexCoord2f(0.f, 1.f);         // assign texture coordinates to next vertex (u,v) = (0,1)
        glVertex3f(x, h, z);            // top (with normal (x,0,z))
        // Iterate around circle
        t -= res;                       // add increment to angle
        x = r*cos(t);                   // move x and z around circle
        z = r*sin(t);
        // Close quad (with new vertex normals)
        glNormal3f(x, 0.f, z);          // define a new normal now that x,z have moved around
        glTexCoord2f(1.f, 1.f);         // assign texture coordinates to next vertex (u,v) = (1,1)
        glVertex3f(x, h, z);            // top
        
        glTexCoord2f(1.f, 0.f);         // assign texture coordinates to next vertex (u,v) = (1,0)
        glVertex3f(x, 0.f, z);          // bottom
        glEnd();
    } while (t >=0);                    // full rotation around circle
    
    glDisable(GL_TEXTURE_2D);         // disable texturing following this point
    
    glPopAttrib();
}

void Lamp_post::texturedCube(GLuint texID)
{
    // Enable Texturing
    glEnable(GL_TEXTURE_2D);
    
    // Enable setting the colour of the material the cube is made from
    // as well as the material for blending.
    glEnable(GL_COLOR_MATERIAL);
    
    // Tell openGL which texture buffer to use
    glBindTexture(GL_TEXTURE_2D, texID);
    
    glBegin(GL_QUADS);
    
    // draw the front face
    // set the normal of the front face
    glNormal3f(0.0f, 0.0f, 1.0f);
    
    // define texture coordinates for the 4 vertices
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    
    // draw the back face
    
    // set the normal of the front face
    glNormal3f(0.0f, 0.0f, -1.0f);
    
    // define texture coordinates for the 4 vertices
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    
    // draw the left face
    
    // set the normal of the left face
    glNormal3f(-1.0f, 0.0f, 0.0f);
    
    // define texture coordinates for the 4 vertices
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    
    // draw the right face
    
    // set the normal of the right face
    glNormal3f(1.0f, 0.0f, 0.0f);
    
    // define texture coordinates for the 4 vertices
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    
    // draw the top face
    
    // set the normal of the top face
    glNormal3f(0.0f, 1.0f, 0.0f);
    
    // define texture coordinates for the 4 vertices
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    
    // draw the bottom face
    
    // set the normal of the bottom face
    glNormal3f(0.0f, -1.0f, 0.0f);
    
    // define texture coordinates for the 4 vertices
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    
    glEnd();
    
    // Stop blending textures and colours
    glDisable(GL_COLOR_MATERIAL);
    
    // Bind to the blank buffer to stop ourselves accidentaly
    // using the wrong texture in the next draw call
    glBindTexture(GL_TEXTURE_2D, NULL);
    // Stop performing texturing
    glDisable(GL_TEXTURE_2D);

}
