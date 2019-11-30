#include "Bus_shelter.h"
#include "VectorMath.h"
#define _TRACK_RADIUS 20.0f
#define _ACCELERATION 10.0f

Bus_shelter::Bus_shelter(){}

Bus_shelter::Bus_shelter(const std::string& f1, const std::string& f2, const std::string& f3): Bus_shelter()
{
    texID1 = Scene::GetTexture(f1);
    texID2 = Scene::GetTexture(f2);
    texID3 = Scene::GetTexture(f3);
    spriteFrame = 0;
    spriteWidth = 20;
    sCoord = 0;
}

void Bus_shelter::Display()
{
    glPushMatrix();
    glPushAttrib(GL_ALL_ATTRIB_BITS);

    // Project from Object Space to World Space
    glTranslatef(pos[0], pos[1], pos[2]);               // Position
    glScalef(scale[0], scale[1], scale[2]);             // Scale
    glRotatef(rotation[0], 1.f, 0.f, 0.f);              // Set orientation (X)
    glRotatef(rotation[1], 0.f, 1.f, 0.f);              // Set orientation (Y)
    glRotatef(rotation[2], 0.f, 0.f, 1.f);              // Set orientation (Z)
    
    glTranslatef(0, pole_height, 0);
    glColor3fv(black);

    DrawTop();
    DrawLeftside();
    DrawRightside();
    DrawBackside();
    Drawseat();
    
    glPopAttrib();
    glPopMatrix();
    
}

void Bus_shelter::Update(const double& deltaTime)
{
    time += deltaTime;
    /* subtract the time on the frame that shows the advertisement fully so that
       the screen displays the ads most of the time and only change once in a while */
    if (spriteFrame == spriteWidth/2 || spriteFrame == spriteWidth){
        time -= deltaTime*0.98;
    }
    if (time > 0.1){
        spriteFrame = spriteFrame > spriteWidth-1? 0 : spriteFrame + 1; // shift frame up by 1 (wrap at 19)
        time = 0.0; // reset frame counter
    }
    
    sCoord = (float)(spriteFrame +spriteWidth/2)/ (float)spriteWidth;
    
    texCoords[0] = 0; // (s,t) texture coord at [0, 1]
    texCoords[1] = sCoord;
    
    texCoords[6] = 1; // (s,t) texture coord at [1, 1]
    texCoords[7] = sCoord;
    
    sCoord = (float)(spriteFrame) / (float)spriteWidth;
    
    texCoords[2] = 0; // (s,t) texture coord at [0, 0]
    texCoords[3] = sCoord;
    
    texCoords[4] = 1; // (s,t) texture coord at [1, 0]
    texCoords[5] = sCoord;
    
}

void Bus_shelter::SpriteFrame_Display(float width, float height, GLuint texID){
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texID);
    
    glPushMatrix();
    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f);
    glNormal3f(0, 0, 1);
    
    glTexCoord2d(texCoords[0], texCoords[1]); // Texture coordinate index into the top left sprite coord
    glVertex3f(-width / 2.0f, height/2, 0.0f);    // Vertex coordinate of the top left of the quad
    
    glTexCoord2d(texCoords[2], texCoords[3]); // Texture coordinate index into the bottom left sprite coord
    glVertex3f(-width / 2.0f, -height/2, 0.0f);       // Vertex coordinate of the bottom left of the quad
    
    glTexCoord2d(texCoords[4], texCoords[5]); // Texture coordinate index into the bottom right sprite coord
    glVertex3f(width / 2.0f, -height/2, 0.0f);        // Vertex coordinate of the bottom right of the quad
    
    glTexCoord2d(texCoords[6], texCoords[7]); // Texture coordinate index into the top right sprite coord
    glVertex3f(width / 2.0f, height/2, 0.0f);     // Vertex coordinate of the top right of the quad
    glEnd();

    glPopMatrix();
    
    glBindTexture(GL_TEXTURE_2D, NULL); // Bind to the blank (null) buffer to stop ourselves accidentaly using the wrong texture in the next draw call
    glDisable(GL_TEXTURE_2D);
    
}

void Bus_shelter:: DrawTop(){
    glPushMatrix();{
        glTranslatef(-3, 0, 0);
        glScaled(top_width, top_height, top_thick);
        glutSolidCube(1);
    }glPopMatrix();
    
    /* draw a textured rectangle displaying the name of the bus
       stop at each side of the roof*/
    
    //the left side
    glPushMatrix();{
        glTranslated(-top_width/2-3, 0, 0);
        glScaled(0.1, top_height, top_thick);
        TexturedCube(texID3);
    }glPopMatrix();
    
    //the right side
    glPushMatrix();{
        glTranslated(top_width/2-3, 0, 0);
        glScaled(0.1, top_height, top_thick);
        glRotated(180, 0, 1, 0);
        TexturedCube(texID3);
    }glPopMatrix();
    
    // the one in the middle
    glPushMatrix();{
        glTranslated(-2, 0, top_thick/2);
        glRotated(90, 0, 1, 0);
        glScaled(0.1, top_height, top_thick*2);
        TexturedCube(texID3);
    }glPopMatrix();
}


void Bus_shelter::Drawseat(){
    //draw a red seat consisting of the three rectangular cuboid
    glPushMatrix();{
        glColor3fv(red);
        
        //the middle part
        glTranslatef(-top_width*0.055, -pole_height*0.7, -top_thick/6);
        glPushMatrix();{
            glScaled(top_width*0.6, 0.5, 2);
            glutSolidCube(1);
        }glPopMatrix();
        
        //the right part
        glPushMatrix();{
            glTranslated(top_width*0.3-0.5, -4, 0);
            glScaled(1, 8, 2);
            glutSolidCube(1);
        }glPopMatrix();
        
        //the left part
        glPushMatrix();{
            glTranslated(-top_width*0.3+0.5, -4, 0);
            glScaled(1, 8, 2);
            glutSolidCube(1);
        }glPopMatrix();
        
        glColor3fv(black);
    }glPopMatrix();
}

void Bus_shelter::DrawLeftside(){
    glPushMatrix();
    //draw back pole
    glPushMatrix();{
        glTranslatef(-top_width/2, -pole_height/2, -top_thick/2+1);
        glScaled(pole_width, pole_height, pole_thick);
        glutSolidCube(1);
    }
    glPopMatrix();
    
    //draw front pole
    glPushMatrix();{
        glTranslatef(-top_width/2, -pole_height/2, top_thick/3-1);
        glScaled(pole_width, pole_height, pole_thick);
        glutSolidCube(1);
    }
    glPopMatrix();
    
    //draw lowest horizontal bar
    glPushMatrix();{
        glTranslatef(-top_width/2, -0.95*pole_height, -top_thick*0.1);
        glScaled(0.5, 0.5, top_thick*0.66);
        glutSolidCube(1);
    }
    glPopMatrix();
    
    //draw middle horizontal bar
    glPushMatrix();{
        glTranslatef(-top_width/2, -0.6*pole_height, -top_thick*0.1);
        glScaled(0.5, 0.5, top_thick*0.67);
        glutSolidCube(1);
    }
    glPopMatrix();
    
    //draw highest horizontal bar
    glPushMatrix();{
        glTranslatef(-top_width/2, -0.05*pole_height, -top_thick*0.1);
        glScaled(0.5, 1.5, top_thick*0.66);
        glutSolidCube(1);
    }
    glPopMatrix();
    glPopMatrix();
}
void Bus_shelter::DrawRightside(){
    //draw the ads
    glPushMatrix();{
        //draw the front ads
        glTranslatef(top_width/2-4, -pole_height/2+0.1, -0.2);
        glRotated(-90, 0, 1, 0);
        glScaled(top_thick-2.5, pole_height-2.8, pole_width+2);
        SpriteFrame_Display(1, 1, texID1);
        
        //draw the backside ads
        glRotated(180, 0, 1, 0);
        SpriteFrame_Display(1, 1, texID1);
    }
    glPopMatrix();
    
    //draw the back pole
    glColor3fv(black);
    glPushMatrix();{
        glTranslatef(top_width/2-4, -pole_height/2, -top_thick/2+0.5);
        glScaled(pole_width+1, pole_height, pole_thick+0.5);
        glutSolidCube(1);
    }
    glPopMatrix();
    
    //draw the front pole
    glPushMatrix();{
        glTranslatef(top_width/2-4, -pole_height/2, top_thick/2-1);
        glScaled(pole_width*2, pole_height, 1.5);
        glutSolidCube(1);
    }
    glPopMatrix();
    
    
    //draw the lowest bar
    glPushMatrix();{
        glTranslatef(top_width/2-4, -0.95*pole_height, 0);
        glScaled(pole_width*2, 1, top_thick-1);
        glutSolidCube(1);
    }
    glPopMatrix();
    
    //draw highest horizontal bar
    glPushMatrix();{
        glTranslatef(top_width/2-4, -0.03*pole_height, 0);
        glScaled(pole_width, 1.5, top_thick-2);
        glutSolidCube(1);
    }glPopMatrix();
    glColor3fv(black);
}




void Bus_shelter::DrawBackside(){
    glPushMatrix();
    float top_width = 40, top_thick = 10;
    float pole_width = 1, pole_height = 20, pole_thick = 1;
    
    //draw the first pole
    glPushMatrix();{
        glTranslatef(-top_width/3.5, -pole_height/2, -top_thick/2);
        glScaled(pole_width, pole_height, pole_thick);
        glutSolidCube(1);
    }
    glPopMatrix();

    //draw the second pole
    glPushMatrix();{
        glTranslatef(top_width*0.4, 0, 0);
        glTranslatef(-top_width/3.5, -pole_height/2, -top_thick/2);
        glScaled(pole_width, pole_height, pole_thick);
        glutSolidCube(1);
    }glPopMatrix();
    
    DrawBackbars();
    
    //draw the bus schedule in the middle
    glTranslatef(top_width*0.2, 0, 0);
    glTranslatef(-top_width/3.5, -pole_height*0.35, -top_thick/2);
    
    glPushMatrix();{
        glScaled(top_width*0.3, pole_height*0.4, 0.5);
        glColor3fv(white);
        glRotated(90, 0, 1, 0);
        TexturedCube(texID2);
    }glPopMatrix();
    
    glColor3fv(black);
    glTranslated(0, -2.5, 0);
    glScaled(top_width/3+1.6, pole_height-0.25, 0.2);
    glutSolidCube(1);
    
    glPopMatrix();
}

void Bus_shelter::DrawBackbars(){
    //draw lowest bar
    glPushMatrix();{
        glTranslatef(-2.5, -pole_height*0.95, -top_thick/2+1);
        glScaled(top_width-4.8, 0.5, 0.5);
        glutSolidCube(1);
    }
    glPopMatrix();
    
    //draw middle bar
    glPushMatrix();{
        glTranslatef(-2.5, -pole_height*0.6, -top_thick/2+1);
        glScaled(top_width-4.8, 0.5, 0.5);
        glutSolidCube(1);
    }
    glPopMatrix();
    
    //draw highest bar
    glPushMatrix();{
        glTranslatef(-2.5, -pole_height*0.05, -top_thick/2+1);
        glScaled(top_width-4.8, 1.6, 0.5);
        glutSolidCube(1);
    }
    glPopMatrix();
}





void Bus_shelter::TexturedCube(GLint texID)
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
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    
    // draw the back face
    
    // set the normal of the front face
    glNormal3f(0.0f, 0.0f, -1.0f);
    
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    
    // draw the left face
    glColor3fv(white);
    // set the normal of the left face
    glNormal3f(-1.0f, 0.0f, 0.0f);
    
    // define texture coordinates for the 4 vertices
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f);
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
}


