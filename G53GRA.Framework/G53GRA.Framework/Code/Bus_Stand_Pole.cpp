#include "Bus_Stand_Pole.h"
#include "VectorMath.h"
#define _TRACK_RADIUS 20.0f
#define _ACCELERATION 10.0f

Bus_Stand_Pole::Bus_Stand_Pole() {}
Bus_Stand_Pole::Bus_Stand_Pole(const std::string& f1, const std::string& f2, const std::string& f3,
                               const std::string& f4, const std::string& f5,const std::string& f6,
                               const std::string& f7, const std::string& f8) : Bus_Stand_Pole()
{
    texID1 = Scene::GetTexture(f1);
    texID2 = Scene::GetTexture(f2);
    texID3 = Scene::GetTexture(f3);
    texID4 = Scene::GetTexture(f4);
    texID5 = Scene::GetTexture(f5);
    texID6 = Scene::GetTexture(f6);
    texID7 = Scene::GetTexture(f7);
    texID8 = Scene::GetTexture(f8);
    spriteFrame = 0;
    spriteWidth = 40;
}

Bus_Stand_Pole::~Bus_Stand_Pole(){}

void Bus_Stand_Pole::Display()
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
    glColor3fv(grey);
    cylinder(r1, h1, 1);
    glTranslatef(0, h1, 0);

    //draw the cone connecting the big cylinder and the smaller cylinder
    Drawcone(r1, r2);

    //draw the second cylinder
    glTranslatef(0, 0.5, 0);
    cylinder(r2, h2, 1);
    glTranslatef(0, h2-1, 0);

    
    /* draw the house with 4 ads on each side*/
    glPushMatrix();{
        glColor3fv(black);
        glTranslatef(0, -h2*0.65, 0);
        cylinder(r2+0.1, 1, 2);
        glTranslatef(0, -1, 0);
        DrawlittleHouse_with_schedule();
    }glPopMatrix();
    
    /* draw the "next bus" display*/
    glPushMatrix();{
        //draw the cylinder cover
        glColor3fv(black);
        glTranslatef(0, -h2*0.45, 0);
        cylinder(r2+0.1, box_h+1, 2);
        
        //draw the box
        glTranslated(0, box_h/2, -box_w/2-0.5);
        glPushMatrix();
        glScaled(3, box_h, box_w);
        glutSolidCube(1);
        glPopMatrix();
        
        //draw the cover on top
        glPushMatrix();
        glTranslated(0, box_h/2+0.5, -0.25);
        glScaled(6, 0.2, box_w+0.5);
        glutSolidCube(1);
        glPopMatrix();
        
        //draw the front display of time of the next buses arriving
        DrawDisplay(r2, h2);
        glColor3fv(white);
        
        //draw the back display of time of the next buses arriving
        glTranslated(0, 0, 0);
        glRotated(180, 0, 1, 0);
        DrawDisplay(r2, h2);
    }glPopMatrix();
    
    /* draw the banner */
    DrawBanner(r2);
    
    glPopAttrib();
    glPopMatrix();
    
}

void Bus_Stand_Pole::DrawDisplay(float r2, float h2){
    glPushMatrix();{
        glPushAttrib(GL_ALL_ATTRIB_BITS);
        float mat_emissive[] = { 1.f, 1.f, 0.0f, 1.f };   // yellow
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_emissive);
        
        //draw the first schedule display
        glColor3fv(white);
        glTranslated(1.7, box_h/2-box_h/8, 0);
        glScaled(0.1, box_h/4, box_w);
        glRotated(90, 0, 1, 0);
        texturedCube(texID6, false);
        
        //draw the second  schedule
        glTranslated(0, -1.2, 0);
        texturedCube(texID7, false);
        
        //draw the third (final) schedule
        glTranslated(0, -1.7, 0.5);
        SpriteFrame_Display(1, 1, texID8);
        glPopAttrib();
    }glPopMatrix();
}

void Bus_Stand_Pole::DrawBanner(float r2){
    glPushMatrix();{
        //draw the circle at the top of the pole
        glColor3fv(black);
        cylinder(r2+0.1, 0.8, 2);
        
        //draw the circle around the pole below the frame
        glPushMatrix();{
            glTranslatef(0, -7.75, 0);
            cylinder(r2+0.1, 0.8, 2);
        }glPopMatrix();
        
        //draw the frame
        glTranslatef(0, -3.5, -4);
        glRotated(90, 0, 1, 0);
        cubeframe(8.1 , 6.1);
        
        //draw the banner
        glScaled(6, 8, 0.1);
        glColor3fv(white);
        texturedCube(texID2, true);
    }glPopMatrix();
}

void Bus_Stand_Pole::Update(const double& deltaTime)
{
    float sCoord;
    time += deltaTime;
    if (spriteFrame == 20 || spriteFrame == spriteWidth){
        time -= deltaTime*0.98;
    }
    if (time > 0.1)
    {
        spriteFrame = spriteFrame > spriteWidth-1? 0 : spriteFrame + 1; // shift frame up by 1 (wrap at 7)
        time = 0.0; // reset frame counter
    }
    
    sCoord = (float)spriteFrame / (float)spriteWidth;
    
    texCoords[0] = sCoord; // (s,t) texture coord at [0, 1]
    texCoords[1] = 1.0f;
    
    texCoords[2] = sCoord; // (s,t) texture coord at [0, 0]
    texCoords[3] = 0.0f;
    
    sCoord = (float)(spriteFrame + spriteWidth/2) / (float)spriteWidth;
    
    texCoords[4] = sCoord; // (s,t) texture coord at [1, 0]
    texCoords[5] = 0.0f;
    
    texCoords[6] = sCoord; // (s,t) texture coord at [1, 1]
    texCoords[7] = 1.0f;

}

void Bus_Stand_Pole::SpriteFrame_Display(float width, float height, GLuint texID){
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texID);
    
    glPushMatrix();

    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f);
    glNormal3f(0, 0, 1);
    
    glTexCoord2d(texCoords[0], texCoords[1]); // Texture coordinate index into the top left sprite coord
    glVertex3f(-width / 2.0f, height, 0.0f);    // Vertex coordinate of the top left of the quad
    
    glTexCoord2d(texCoords[2], texCoords[3]); // Texture coordinate index into the bottom left sprite coord
    glVertex3f(-width / 2.0f, 0.0f, 0.0f);       // Vertex coordinate of the bottom left of the quad
    
    glTexCoord2d(texCoords[4], texCoords[5]); // Texture coordinate index into the bottom right sprite coord
    glVertex3f(width / 2.0f, 0.0f, 0.0f);        // Vertex coordinate of the bottom right of the quad
    
    glTexCoord2d(texCoords[6], texCoords[7]); // Texture coordinate index into the top right sprite coord
    glVertex3f(width / 2.0f, height, 0.0f);     // Vertex coordinate of the top right of the quad
    glEnd();
    glPopMatrix();
    
    glBindTexture(GL_TEXTURE_2D, NULL); // Bind to the blank (null) buffer to stop ourselves accidentaly using the wrong texture in the next draw call
    
    glDisable(GL_TEXTURE_2D);
    
}


void Bus_Stand_Pole::DrawlittleHouse_with_schedule(){
    DrawHouseRoof();
    float box_w = 5, box_h = 5;
    
    //front face
    glPushMatrix();{
        //draw the frame
        glTranslatef(box_w/2, -box_h/2-0.15, 0);
        glRotated(90, 0, 1, 0);
        cubeframe(box_w , box_h);
        
        //draw the schedule picture inside the frame
        glScaled(box_w-0.2, box_h-0.2, 0.1);
        glColor3fv(white);
        texturedCube(texID4, false);
        glColor3fv(black);
    }glPopMatrix();
    
    //back face
    glPushMatrix();{
        glTranslatef(-box_w/2, -box_h/2-0.15, 0);
        glRotated(-90, 0, 1, 0);
        cubeframe(box_w , box_h);
        
        //draw the schedule picture inside the frame
        glScaled(box_w-0.2, box_h-0.2, 0.1);
        glColor3fv(white);
        texturedCube(texID3, false);
        glColor3fv(black);
    }glPopMatrix();
    
    //left face
    glPushMatrix();{
        glTranslatef(0, -box_w/2-0.15, box_h/2);
        cubeframe(box_w , box_h);
        //draw the schedule picture inside the frame
        glScaled(box_w-0.2, box_h-0.2, 0.1);
        glColor3fv(white);
        texturedCube(texID5, false);
        glColor3fv(black);
    }glPopMatrix();
    
    //right face
    glPushMatrix();{
        glTranslatef(0, -box_w/2-0.15, -box_h/2);
        cubeframe(box_w , box_h);
        //draw the schedule picture inside the frame
        glScaled(box_w-0.2, box_h-0.2, 0.1);
        glColor3fv(white);
        glRotated(180, 0, 1, 0);
        texturedCube(texID5, false);
        glColor3fv(black);
    }glPopMatrix();
    
    //draw bottom
    glPushMatrix();{
        glTranslatef(0, -box_h-0.15, 0);
        glRotated(90, 1, 0, 0);
        glScaled(box_w, box_h, 0.1);
        glutSolidCube(1);
    }glPopMatrix();
}
void Bus_Stand_Pole::DrawHouseRoof(){
    glPushMatrix();
    glScaled(4, 2, 4);
    glRotated(45, 0, 1, 0);
    static float vertices[] =
    {
        1.0f, 0.0f, 0.0f,   // VERTEX 0
        0.0f, 0.0f, -1.0f,  // VERTEX 1
        -1.0f, 0.0f, 0.0f,  // VERTEX 2
        0.0f, 0.0f, 1.0f,   // VERTEX 3
        0.0f, 1.0f, 0.0f,   // VERTEX 4
    };
    _initV = vertices;
    // half octahedron
    DrawTriangle(&_initV[_VERTEX3], &_initV[_VERTEX0], &_initV[_VERTEX4]);
    DrawTriangle(&_initV[_VERTEX0], &_initV[_VERTEX1], &_initV[_VERTEX4]);
    DrawTriangle( &_initV[_VERTEX1], &_initV[_VERTEX2], &_initV[_VERTEX4]);
    DrawTriangle(&_initV[_VERTEX2], &_initV[_VERTEX3], &_initV[_VERTEX4]);
    glPopMatrix();
}

/* A frame around which the textured bus schedule, bus map, or banner will be drawn in.  */
void Bus_Stand_Pole::cubeframe(float h, float w){
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glPushMatrix();
    float frame_width = 0.4;
    glTranslatef(-w/2, 0, 0);
    //draw the left pole
    glPushMatrix();{
        glScaled(frame_width, h,frame_width );
        glutSolidCube(1);
    }glPopMatrix();
    
    //draw the right pole
    glPushMatrix();{
        glTranslatef(w, 0, 0);
        glScaled(frame_width, h, frame_width );
        glutSolidCube(1);
    }glPopMatrix();
    
    //draw the bottom pole
    glPushMatrix();{
        glTranslatef(w/2, -h/2, 0);
        glScaled(w+frame_width , frame_width, frame_width);
        glutSolidCube(1);
    }glPopMatrix();
    
    //draw the upper pole
    glPushMatrix();{
        glTranslatef(w/2, h/2, 0);
        glScaled(w+frame_width, frame_width, frame_width);
        glutSolidCube(1);
    }glPopMatrix();
    glPopAttrib();
    glPopMatrix();
    
}

void Bus_Stand_Pole::DrawTriangle(float *a, float *b, float *c){
    // Create face with texture bound texture
    glBegin(GL_TRIANGLES);{
        // vertex a
        glNormal3fv(a); glVertex3fv(a);
        // vertex b
        glNormal3fv(b); glVertex3fv(b);
        // vertex c
        glNormal3fv(c); glVertex3fv(c);
    }glEnd();
}


void Bus_Stand_Pole::Drawcone(float r1, float r2)
{
    float th = 0.0f, res = 2.0f * M_PI / 30.0f;
    float x1 = 0.0, z1 = 0.0;
    float x2 = 0.0, z2 = 0.0;
    float h2 = 0.5; float h1 = 0;
    
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
    
    //we have to draw a reverse revolution otherwise we would see only half of the cylinder
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

void Bus_Stand_Pole::cylinder(float r, float h, int ind){
    /* long cylinder is drawn using short cylinders so that lighting looks better */
    float unit = 0.1f;
    glPushMatrix();
    for (float i = 0; i < h-unit; i+=unit){
        unit_cylinder(r, unit, ind);
        glTranslated(0, unit, 0);
    }
    glPopMatrix();
}

void Bus_Stand_Pole::unit_cylinder(float r, float unit, int ind)
{
    glPushAttrib(GL_ALL_ATTRIB_BITS);       // save current style attributes
    
    float res = (float)0.05f*M_PI;
    float x = 0, z = 0.f;                   // initialise x and z on right of cylinder centre
    float t = 0.f;                          // initialise angle as 0


    // Define the specular material colour property K_s
    static GLfloat mat_specular[] = { 0.2f, 0.2f, 0.2f, 1.f };
    // Define the shininess/specular exponent factor n ( capped between 0.0 and 128.0 )
    static GLfloat mat_shininess[] = { 50.0 };
    
    /*ind ==1 means the main pole, which we want to specify material properties.
     Otherwise, just use glcolor */
    if (ind ==1){
        glDisable(GL_COLOR_MATERIAL);
        glMaterialfv(GL_FRONT, GL_AMBIENT, grey);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, grey);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    }

    do
    {                                    // create branch with multiple QUADS
        glBegin(GL_QUADS);
        // Create first points (with normals)
        glNormal3f(x, 0.f, z);          // define a normal facing out from the centre (0,0,0)
        glVertex3f(x, 0.f, z);          // bottom (with normal (x,0,z))
        glVertex3f(x, unit, z);          // top (with normal (x,0,z))
        // Iterate around circle
        t += res;                       // add increment to angle
        x = r*cos(t);                   // move x and z around circle
        z = r*sin(t);
        // Close quad (with new vertex normals)
        glNormal3f(x, 0.f, z);          // define a new normal now that x,z have moved around
        glVertex3f(x, unit, z);          // top
        
        glVertex3f(x, 0.f, z);          // bottom
        glEnd();
    } while (t <= 2.001 * M_PI);                // full rotation around circle
    
     //we have to draw a reverse revolution otherwise we would see only half of the cylinder
    do
    {                                    // create branch with multiple QUADS
        glBegin(GL_QUADS);
        // Create first points (with normals)
        glNormal3f(x, 0.f, z);          // define a normal facing out from the centre (0,0,0)
        glVertex3f(x, 0.f, z);          // bottom (with normal (x,0,z))
        
        glVertex3f(x, unit, z);          // top (with normal (x,0,z))
        // Iterate around circle
        t -= res;                       // add increment to angle
        x = r*cos(t);                   // move x and z around circle
        z = r*sin(t);
        // Close quad (with new vertex normals)
        glNormal3f(x, 0.f, z);          // define a new normal now that x,z have moved around
        glVertex3f(x, unit, z);          // top
        glVertex3f(x, 0.f, z);          // bottom
        glEnd();
    } while (t >=0);                // full rotation around circle
    
    glPopAttrib();
}

void Bus_Stand_Pole:: texturedCube(GLint texID, bool two_sided)
{
    glPushAttrib(GL_ALL_ATTRIB_BITS);
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
    
    if (two_sided){ //if we want to texture two side of the cube
        // define texture coordinates for the 4 vertices
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(0.5f, 0.5f, -0.5f);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(0.5f, -0.5f, -0.5f);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(-0.5f, -0.5f, -0.5f);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(-0.5f, 0.5f, -0.5f);
    }
    else{
        glVertex3f(0.5f, 0.5f, -0.5f);
        glVertex3f(0.5f, -0.5f, -0.5f);
        glVertex3f(-0.5f, -0.5f, -0.5f);
        glVertex3f(-0.5f, 0.5f, -0.5f);
    }
    
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
    glPopAttrib();
};
