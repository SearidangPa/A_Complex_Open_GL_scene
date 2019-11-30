#include "Robot.h"
#include "VectorMath.h"
#include<iostream>
Robot::Robot():animationTime(2.f), speed(7)
{
}
Robot::~Robot(){}

/* Overloaded update function */
void Robot::Update(const double& dT)
{    
    if (dir == 0){              //stand still
        adjust_sit_down = 0;
        rotate_right_upper_leg = 0.f; rotate_right_low_leg = 0.f;
        rotate_left_upper_leg = 0.f; rotate_left_low_leg = 0.f;
        rotate_right_up_arm =0; rotate_right_low_arm =0;
        rotate_left_up_arm =0; rotate_left_low_arm =0;
    }
    else if (dir == 1){         //forward
        adjust_sit_down = 0;
        rotation[1] = -90;
        pos[0] -= speed;
    }
    else if (dir == 2){         //left
        adjust_sit_down = 0;
        rotation[1] = 0;
        pos[2] += speed;
    }
    else if (dir == 3){         //back
        adjust_sit_down = 0;
        rotation[1] = 90;
        pos[0] += speed;
    }
    else if (dir == 4){         //right
        adjust_sit_down = 0;
        rotation[1] = 180;
        pos[2] -= speed;
    }
    else{                       //sit down
        adjust_sit_down = 2.25;
        rotate_right_upper_leg = 90.f; rotate_right_low_leg = -80.f;
        rotate_left_upper_leg = 90.f; rotate_left_low_leg = -80.f;
        
        rotate_right_up_arm =0; rotate_right_low_arm =45;
        rotate_left_up_arm =0; rotate_left_low_arm =45;
    }
    if (!stop){                                     //if the robot is not standing still
        aT = fmod(aT + dT, animationTime);          // update time in animation cycle
        float aS = 8.f*aT / animationTime;          // calculate stage (out of 8)
        if (aS < 1.f){                              //first stage
            rotate_right_upper_leg = -20.f; rotate_right_low_leg = -20.f;
            rotate_left_upper_leg = 20.f; rotate_left_low_leg = 0.f;
            
            rotate_right_up_arm=10; rotate_right_low_arm =35;
            rotate_left_up_arm=-15; rotate_left_low_arm =0;
        }
        
        else if(aS < 2.f){                          //second stage
            rotate_right_upper_leg = 0.f; rotate_right_low_leg = -50.f;
            rotate_left_upper_leg = 15.f; rotate_left_low_leg = -30.f;
            
            rotate_right_up_arm = 0; rotate_right_low_arm = 25;
            rotate_left_up_arm =-10; rotate_left_low_arm = 5;
        }
        
        else if(aS < 3.f ){                         //third stage
            rotate_right_upper_leg = 20.f; rotate_right_low_leg = -50.f;
            rotate_left_upper_leg = 5.f; rotate_left_low_leg = -20.f;
            
            rotate_right_up_arm = 0; rotate_right_low_arm = 0;
            rotate_left_up_arm =0; rotate_left_low_arm = 20;
        }
        
        else if(aS < 4.f ){                         //fourth stage
            rotate_right_upper_leg = 35.f; rotate_right_low_leg = -45.f;
            rotate_left_upper_leg = -10.f; rotate_left_low_leg = -20.f;
            
            rotate_right_up_arm = -10; rotate_right_low_arm = 5;
            rotate_left_up_arm = 10; rotate_left_low_arm = 15;
        }
        else if(aS < 5.f){                          //fifth stage
            rotate_right_upper_leg = 20.f; rotate_right_low_leg = 0.f;
            rotate_left_upper_leg = -20.f; rotate_left_low_leg = -20.f;
            
            rotate_right_up_arm = -15; rotate_right_low_arm = 0;
            rotate_left_up_arm = 10; rotate_left_low_arm = 35;
        }
        
        else if(aS < 6.f){                          //sixth stage
            rotate_right_upper_leg = 15.f; rotate_right_low_leg = -30.f;
            rotate_left_upper_leg = 0.f; rotate_left_low_leg = -50.f;

            rotate_right_up_arm = -10; rotate_right_low_arm = 5;
            rotate_left_up_arm =0; rotate_left_low_arm = 25;
        }
        else if(aS < 7.f){                          //seventh stage
            rotate_right_upper_leg = 5.f; rotate_right_low_leg = -20.f;
            rotate_left_upper_leg = 20.f; rotate_left_low_leg = -50.f;
            
            rotate_right_up_arm = 0; rotate_right_low_arm = 20;
            rotate_left_up_arm =-10; rotate_left_low_arm = 5;
        }
        else if(aS < 8.f){                          //eigth stage
            rotate_right_upper_leg = -10.f; rotate_right_low_leg = -20.f;
            rotate_left_upper_leg = 35.f; rotate_left_low_leg = -45.f;
            
            rotate_right_up_arm= 10; rotate_right_low_arm =35;
            rotate_left_up_arm=-15; rotate_left_low_arm=0;
        }
     
    }
}

void Robot::Display()
{
    glPushMatrix();                     // save transformation state
    glPushAttrib(GL_ALL_ATTRIB_BITS);   // save style attributes (and more)
    glColor3f(0.4f, 0.f, 0.f);          // colour robot red

    // Project from Object Space to World Space
    glTranslatef(pos[0], pos[1], pos[2]);               // Position
    glScalef(scale[0], scale[1], scale[2]);             // Scale
    glRotatef(rotation[0], 1.f, 0.f, 0.f);              // Set orientation (X)
    glRotatef(rotation[1], 0.f, 1.f, 0.f);              // Set orientation (Y)
    glRotatef(rotation[2], 0.f, 0.f, 1.f);              // Set orientation (Z)
    
    /* translate down so that the head is drawn at height 0 which make
       it easier to calculate the robot position in Myscene */
    glTranslatef(0, -body_height-up_leg_length-low_arm_length-0.5, 0);
    glTranslated(0, -adjust_sit_down, 0);               //adjust for when the robot sitting down
    DrawRobot();                                        // draw robot
    
    glPopAttrib();                                      // restore style attributes
    glPopMatrix();                                      // restore transformation state
}

/* handle keyboard input */
void Robot::HandleKey(unsigned char key, int state, int mx, int my)
{
    if (state && key == 'i'){       //going foward
        stop = false;
        dir = 1;
    }
    else if (state && key == 'j'){  //going left
        stop = false;
        dir = 2;
    }
    else if (state && key == 'k'){  //going back
        stop = false;
        dir = 3;
    }
    else if (state && key == 'l'){  //going right
        stop = false;
        dir = 4;
    }
    else if (state && key == ' '){  //standing still
        dir = 0;
        stop = true;
    }
    else if (state && key == '+'){  //increase the speed of the robot walking
        if (animationTime > 0.3){
            animationTime -=0.3;
        }
        speed +=3;
    }
    else if (state && key == '-'){  //decrease the speed of the robot walking
        animationTime +=0.3;
        speed -=3;
    }
    else if (state && key == 'p'){  //sit down
        dir = 5;
        stop = true;
    }
}



/* Draw the robot */
void Robot::DrawRobot()
{
    glPushMatrix();                                          // save state
        glutSolidSphere(r_head, 20, 20);                     // draw head
        glTranslatef(0.f, -r_head-body_height/2, 0.f);       // move down to the center of the body
        box(body_width, body_height, body_thickness);        // draw body
    
        /*----------------------------------draw left arm------------------------------*/
        glPushMatrix();    // save position in centre of body
            //translate to the right upper corner of the body
            glTranslatef(body_width/2 + r_big_joint, body_height/2 - r_big_joint, 0.f);
            Draw_left_Arm();
        glPopMatrix();
    
        /*----------------------------------draw right arm------------------------------*/
        glPushMatrix();    // save position in centre of body
            //translate to the left upper corner of the body
            glTranslatef(-body_width/2 - r_big_joint, body_height/2 - r_big_joint, 0.f);
            Draw_right_Arm();
        glPopMatrix();
    
        /*----------------------------------draw left leg------------------------------*/
        glPushMatrix();    // save position in centre of body
            //translate to the left lower corner of the body
            glTranslatef(body_width/2-r_big_joint-0.5, -body_height/2-r_big_joint, 0.f);
            DrawLeftLeg();
        glPopMatrix();
        /*----------------------------------draw right leg------------------------------*/
        glPushMatrix();    // save position in centre of body
            //translate to the right lower corner of the body
            glTranslatef(-body_width/2+r_big_joint+0.5, -body_height/2-r_big_joint, 0.f);
            DrawRightLeg();
        glPopMatrix();
    
    glPopMatrix();
}


void Robot::Draw_left_Arm()
{
    glutSolidSphere(r_big_joint, 20, 20);         // draw big joint
    glRotatef(190, 0.0f, 0.0f, 1.0f);             // rotate around the Z-axis to seperate the arm from the body a bit
    
    /* draw upper arm*/
    glRotatef(rotate_left_up_arm, 1.0f, 0.0f, 0.0f);
    glTranslatef(0, up_arm_length/2, 0.f);                 // translate to draw up arm
    box(up_arm_width, up_arm_length, up_arm_thickness);    // draw up arm
    
    /* translate from upper to lower arm */
    glTranslatef(0, up_arm_length/2 + r_small_joint, 0.f); // translate to draw joint
    glutSolidSphere(r_small_joint , 20, 20);               // draw small joint
    
    /* draw lower arm*/
    glRotatef(rotate_left_low_arm, 1.0f, 0.0f, 0.0f);      // rotate  around the x-axis
    glTranslatef(0, r_small_joint + low_arm_length/2, 0.f);// translate to draw low arm
    box(low_arm_width, low_arm_length, low_arm_thickness); // draw low arm
}

void Robot::Draw_right_Arm()
{
    glutSolidSphere(r_big_joint, 20, 20);       // draw big joint
    glRotatef(-190, 0.0f, 0.0f, 1.0f);          // rotate around the Z-axis to seperate the arm from the body a bit
    
    /* draw upper arm*/
    glRotatef(rotate_right_up_arm, 1.0f, 0.0f, 0.0f);
    glTranslatef(0, up_arm_length/2, 0.f);                 // translate to draw up arm
    box(up_arm_width, up_arm_length, up_arm_thickness);    // draw up arm
    
    /* translate from upper to lower arm */
    glTranslatef(0, up_arm_length/2 + r_small_joint, 0.f); // translate to draw joint
    glutSolidSphere(r_small_joint , 20, 20);               // draw small joint
    
    /* draw lower arm*/
    glRotatef(rotate_right_low_arm, 1.0f, 0.0f, 0.0f);     // rotate  around the x-axis
    glTranslatef(0, r_small_joint + low_arm_length/2, 0.f);// translate to draw low arm
    box(low_arm_width, low_arm_length, low_arm_thickness); // draw low arm
}

// Draw the right leg of the robot
void Robot::DrawRightLeg()
{
    glutSolidSphere(r_big_joint, 20, 20);                     // draw big joint
    glRotatef(-180.f, 0.0f, 0.0f, 1.0f);                       // rotate around the Z-axis
    
    /* draw upper leg*/
    glRotated(rotate_right_upper_leg, 1, 0, 0);
    glTranslatef(0, up_leg_length/2, 0.f);                     // translate to draw upper leg
    box(up_leg_width, up_leg_length, up_leg_thickness);        // draw uppper leg
    
    /* translate from upper to lower leg */
    glTranslatef(0, up_leg_length/2 + r_small_joint, 0.0f);     // translate to draw joint
    glutSolidSphere(r_small_joint, 20, 20);                     // draw small joint
    
    /* draw lower leg*/
    glRotated(rotate_right_low_leg, 1, 0, 0);
    glTranslatef(0, r_small_joint + low_leg_length/2, 0.f);     // translate to draw low leg
    box(low_leg_width, low_leg_length, low_leg_thickness);     // draw lower leg
    
    /* draw foot to make it look more realistic*/
    glTranslatef(0, low_leg_length/2, 0.f);                    //translate to the end of the lower leg
    glRotatef(90.f, 1.0f, 0.0f, 0.0f);
    glTranslatef(0, feet_length/2-0.5, 0.f);                     //translate to draw the feet
    box(1.2, feet_length, 0.5);
}

// Draw the left leg of the robot
void Robot::DrawLeftLeg()
{
    glutSolidSphere(r_big_joint, 20, 20);                      // draw big joint
    glRotatef(-180.f, 0.0f, 0.0f, 1.0f);                       // rotate around the Z-axis
    
    /* draw upper leg*/
    glRotated(rotate_left_upper_leg, 1, 0, 0);                 // rotate the upper leg around the x-axis
    glTranslatef(0, up_leg_length/2, 0.f);                     // translate to draw upper leg
    box(up_leg_width, up_leg_length, up_leg_thickness);        // draw uppper leg
    
    /* translate from upper to lower leg */
    glTranslatef(0, up_leg_length/2 + r_small_joint, 0.0f);     // translate to draw joint
    glutSolidSphere(r_small_joint, 20, 20);                     // draw small joint
    
    /* draw lower leg*/
    glRotated(rotate_left_low_leg, 1, 0, 0);                    //rotate the lower leg around the x-axis
    glTranslatef(0, r_small_joint + low_leg_length/2, 0.f);     // translate to draw low leg
    box(low_leg_width, low_leg_length, low_leg_thickness);      // draw lower leg
    
    /* draw foot to make it look more realistic*/
    glTranslatef(0, low_leg_length/2, 0.f);                     //translate to the end of the lower leg
    glRotatef(90.f, 1.0f, 0.0f, 0.0f);
    glTranslatef(0, feet_length/2-0.5, 0.f);                    //translate to draw the feet
    box(1.2, feet_length, 0.5);
    
}


/* draw basic polygonal componenent: scale the coordinate by the specified inputs sx, sy, sz
   and draw a basic cube.
 */
void Robot::box(float sx, float sy, float sz) {
    glPushMatrix();         //save the states
    glScalef(sx, sy, sz);   //scale the coordinates
    glutSolidCube(1.f);     //draw a unit cube
    glPopMatrix();          //return to the original state
}


