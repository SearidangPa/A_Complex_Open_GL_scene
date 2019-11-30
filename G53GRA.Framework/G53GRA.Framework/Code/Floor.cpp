#include "Floor.h"
Floor::Floor(const std::string& filename, int ind, int range) : Floor()
{
    texid = Scene::GetTexture(filename);
    index = ind;
    _range = range;
}
void Floor::Display()
{
    glPushMatrix();                                 // save transformation state
    glPushAttrib(GL_ALL_ATTRIB_BITS);               // save style attributes (and more)
    
    // Project from Object Space to World Space
    glTranslatef(pos[0], pos[1], pos[2]);           //position
    glScalef(scale[0], scale[1], scale[2]);         //scale
    glRotatef(rotation[0], 1.f, 0.f, 0.f);          // Set orientation (X)
    glRotatef(rotation[1], 0.f, 1.f, 0.f);          // Set orientation (Y)
    glRotatef(rotation[2], 0.f, 0.f, 1.f);          // Set orientation (Z)
    
    //set material properties: diffuse, specular, and shininess
    if (index==1){      //road
        float Diffuse_temp[4] = { 0.7f, 0.7f, 0.7f, 1.0f};
        _Diffuse = Diffuse_temp;
    }
    else if (index==2){  //side walk
        float Diffuse_temp[4] = { 0.58f, 0.27f, 0.21f, 1.0f};
        _Diffuse = Diffuse_temp;
    }
    else if (index==3){  //side walk connect to road
        float Diffuse_temp[4] = { 0.38f, 0.07f, 0.01f, 1.0f};
        _Diffuse = Diffuse_temp;
    }
    else if (index==4){   //yellow strip
        float Diffuse_temp[4] = { 0.9f, 0.8f, 0.4f, 1.0f};
        _Diffuse = Diffuse_temp;
    }
    else if (index==5){   //white strip
        float Diffuse_temp[4] = { 0.9f, 0.9f, 0.9f, 1.0f};
        _Diffuse = Diffuse_temp;
    }
    float specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float shininess = 128.0f;
    
	glDisable(GL_COLOR_MATERIAL);                   // Draws an exciting chequered floor
    glEnable(GL_TEXTURE_2D);                        // Enable Texturing
    glBindTexture(GL_TEXTURE_2D, texid);            // Tell openGL which texture buffer to use
    
    glBegin(GL_QUADS);{
        glMaterialfv(GL_FRONT, GL_SPECULAR, static_cast<GLfloat*>(specular));
        glMaterialf(GL_FRONT, GL_SHININESS, static_cast<GLfloat>(shininess));
        /* draw the floor by drawing many small quads*/
        for (int i = -_range; i < _range; i++){
            for (int j = -10; j < 10; j++){
                glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, static_cast<GLfloat*>(_Diffuse));
                glNormal3f(0.0f, 1.0f, 0.0f);
                
                glTexCoord2f(0.0f, 1.0f);
                glVertex3f(scale[0] * static_cast<float>(i)+scale[0], 0, scale[2] * static_cast<float>(j)+scale[2]);
                
                glTexCoord2f(0.0f, 0.0f);
                glVertex3f(scale[0] * static_cast<float>(i)+scale[0], 0, scale[2] * static_cast<float>(j));
                
                glTexCoord2f(1.0f, 0.0f);
                glVertex3f(scale[0] * static_cast<float>(i), 0, scale[2] * static_cast<float>(j));
                
                glTexCoord2f(1.0f, 1.0f);
                glVertex3f(scale[0] * static_cast<float>(i), 0, scale[2] * static_cast<float>(j)+scale[2]);
            }
        }
    }glEnd();
    
    
    // Bind to the blank buffer to stop ourselves accidentaly using the wrong texture in the next draw call
    glBindTexture(GL_TEXTURE_2D, NULL);
    
    // Stop performing texturing
    glDisable(GL_TEXTURE_2D);
	glEnable(GL_COLOR_MATERIAL);
    
	glPopAttrib();
	glPopMatrix();
}
