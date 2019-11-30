#include "Chair.h"

Chair::Chair(){}

Chair::Chair(const std::string& filename) : Chair()
{
    texID = Scene::GetTexture(filename);
}

void Chair::Display()
{
    glPushMatrix();
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    
    // Project from Object Space to World Space
    glTranslatef(pos[0], pos[1], pos[2]);               // Position
    glScalef(scale[0], scale[1], scale[2]);             // Scale
    glRotatef(rotation[0], 1.f, 0.f, 0.f);              // Set orientation (X)
    glRotatef(rotation[1], 0.f, 1.f, 0.f);              // Set orientation (Y)
    glRotatef(rotation[2], 0.f, 0.f, 1.f);              // Set orientation (Z)

    Draw_left_leg();
    Draw_right_leg();
    Draw_Connector();   //draw the support around the legs
    Draw_horizontal_seat();
    Draw_back();
    
    glPopAttrib();
    glPopMatrix();
}

void Chair::Draw_right_leg(){
    /* draw the right legs*/
    glPushMatrix();{
        /* draw the front right leg*/
        glTranslatef(dist_left_leg_to_right_leg, 0, 0);     //translate to draw front right leg
        
        glPushMatrix();{
            glScalef(1, leg_height, 1);                     //scale to draw the legs
            Textured_Cube();                                //draw back right leg
        }glPopMatrix();
        
        /* draw the front right leg*/
        glPushMatrix();{
            glTranslatef(0, 0, dist_back_leg_to_front_leg);     //translate to draw the front right leg
            glScalef(0.5, leg_height, 1);                       //front leg is a big smaller than back leg
            Textured_Cube();                                    //draw front right leg
        }glPopMatrix();
        
    }glPopMatrix();
}
void Chair::Draw_left_leg(){
    /* draw the back left legs*/
    glPushMatrix();{
        glScalef(1, leg_height, 1);                         //scale to draw the legs
        Textured_Cube();                                    //draw back left leg
    }glPopMatrix();
    
    /* draw the front left legs*/
    glPushMatrix();{
        glTranslatef(0, 0, dist_back_leg_to_front_leg);     //translate to draw front left leg
        glScalef(0.5, leg_height, 1);                       //front leg is a big smaller than back leg
        Textured_Cube();                                    //draw front left leg
    }glPopMatrix();
}

void Chair::Draw_horizontal_seat(){
    /*draw long pieces of wood next to each other separated by a certain amount of gap*/
    glPushMatrix();{
        /* translate to place to draw the seat*/
        glTranslatef(dist_left_leg_to_right_leg/2, leg_height/2, wood_slice_thickness/2);
        glScalef(dist_left_leg_to_right_leg-0.3, 0.2, wood_slice_thickness);    //scale it into a long piece
        Textured_Cube();
        /* keep drawing long pieces of wood to fill the seat */
        glTranslatef(0, 0, wood_slice_thickness/2+gap_horizontal_seat);
        Textured_Cube();
        
        glTranslatef(0, 0, wood_slice_thickness/2+gap_horizontal_seat);
        Textured_Cube();
        
        glTranslatef(0, 0, wood_slice_thickness/2+gap_horizontal_seat);
        Textured_Cube();
        
        glTranslatef(0, 0, wood_slice_thickness/2+gap_horizontal_seat);
        Textured_Cube();
    }glPopMatrix();
}

void Chair::Draw_Connector(){
    //draw the lower connector from front left leg to back left leg
    glPushMatrix();{
        glTranslatef(0, -leg_height/6, dist_back_leg_to_front_leg/2);
        glScalef(0.3, 1, dist_back_leg_to_front_leg -1);
        Textured_Cube();
    }glPopMatrix();
    
    //draw the upper connector from front left leg to back left leg
    glPushMatrix();{
        glTranslatef(0, leg_height*2/5, dist_back_leg_to_front_leg/2);
        glScalef(0.3, 1, dist_back_leg_to_front_leg -1);
        Textured_Cube();
    }glPopMatrix();
    
    //draw the connector from front right leg to back right leg
    glPushMatrix();{
        glTranslatef(dist_left_leg_to_right_leg, 0, 0); //translate to the back right leg
        
        //draw the lower connector from front right leg to back right leg
        glPushMatrix();{
            glTranslatef(0, -leg_height/6, dist_back_leg_to_front_leg/2);
            glScalef(0.3, 1, dist_back_leg_to_front_leg -1);
            Textured_Cube();
        }glPopMatrix();
        
        //draw the upper connector from front right leg to back right leg
        glPushMatrix();{
            glTranslatef(0, leg_height*2/5, dist_back_leg_to_front_leg/2);
            glScalef(0.3, 1, dist_back_leg_to_front_leg -1);
            Textured_Cube();
        }glPopMatrix();
        
    }glPopMatrix();
    
    //draw a lower connector from the back left leg to the back right leg
    glPushMatrix();{
        glTranslatef(dist_left_leg_to_right_leg/2, -leg_height/6, 0);
        glScalef(dist_left_leg_to_right_leg, 1, 0.3);
        Textured_Cube();
    }glPopMatrix();
    
    //draw the connector from back left leg to back right leg
    glPushMatrix();{
        glTranslatef(dist_left_leg_to_right_leg/2, leg_height*2/5, 0);
        glScalef(dist_left_leg_to_right_leg, 1, 0.3);
        Textured_Cube();
    }glPopMatrix();
    
    //draw the connector from front left leg to front right leg
    glPushMatrix();{
        glTranslatef(dist_left_leg_to_right_leg/2, leg_height*2/5, dist_back_leg_to_front_leg);
        glScalef(dist_left_leg_to_right_leg, 1, 0.3);
        Textured_Cube();
    }glPopMatrix();
}

void Chair::Draw_back(){
    glPushMatrix();{
        /* draw the back structure of the seat leaning back */
        glRotatef(-8, 1.f, 0.f, 0.f);
        glTranslatef(0,leg_height,0.3);
        
        glPushMatrix();{
            glScalef(1,leg_height,1);
            Textured_Cube();
            glTranslatef(dist_left_leg_to_right_leg, 0, 0);
            Textured_Cube();
        }glPopMatrix();
        
        /* top bar */
        glTranslatef(dist_left_leg_to_right_leg/2, leg_height*2/5, 0);
        glPushMatrix();{
            glScalef(dist_left_leg_to_right_leg, 1, 0.2);
            Textured_Cube();
        }glPopMatrix();
        
        /*draw a bunch of vertical short wood slice to the right for the back*/
            //the middle piece
        glTranslatef(0, -leg_height/2, 0);
        glScalef(0.9, leg_height-1, 0.2);
        Textured_Cube();
        
            //the pieces to the left
        glPushMatrix();{
            glTranslatef(gap_back, 0, 0);
            Textured_Cube();
            glTranslatef(gap_back, 0, 0);
            Textured_Cube();
            glTranslatef(gap_back, 0, 0);
            Textured_Cube();
            glTranslatef(gap_back, 0, 0);
            Textured_Cube();
            glTranslatef(gap_back, 0, 0);
            Textured_Cube();
        }glPopMatrix();
        
            //the pieces to the right
        glPushMatrix();{
            glTranslatef(-gap_back, 0, 0);
            Textured_Cube();
            glTranslatef(-gap_back, 0, 0);
            Textured_Cube();
            glTranslatef(-gap_back, 0, 0);
            Textured_Cube();
            glTranslatef(-gap_back, 0, 0);
            Textured_Cube();
            glTranslatef(-gap_back, 0, 0);
            Textured_Cube();
        }glPopMatrix();
        
    }glPopMatrix();
}

void Chair::Textured_Cube()
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
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    
    // draw the left face
    
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
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    
    // draw the top face
    
    // set the normal of the top face
    glNormal3f(0.0f, 1.0f, 0.0f);
    
    // define texture coordinates for the 4 vertices
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    
    // draw the bottom face
    
    // set the normal of the bottom face
    glNormal3f(0.0f, -1.0f, 0.0f);
    
    // define texture coordinates for the 4 vertices
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f);
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


