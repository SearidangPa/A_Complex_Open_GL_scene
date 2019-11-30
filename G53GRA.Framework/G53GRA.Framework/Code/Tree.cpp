#include "Tree.h"
#include <cmath>
#include <iostream>

Tree::Tree(){}

Tree::Tree(const std::string& filename) : Tree()
{
    texID = Scene::GetTexture(filename);
}

void Tree::Display()
{
    glPushMatrix();
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    
    // Project from Object Space to World Space
    glTranslatef(pos[0], pos[1], pos[2]);               // Position
    glScalef(scale[0], scale[1], scale[2]);             // Scale
    glRotatef(rotation[0], 1.f, 0.f, 0.f);              // Set orientation (X)
    glRotatef(rotation[1], 0.f, 1.f, 0.f);              // Set orientation (Y)
    glRotatef(rotation[2], 0.f, 0.f, 1.f);              // Set orientation (Z)
    
    float angle = 22.5f;
    branch();
    char curr;
    
    for (unsigned int i = 0; i < sequence.size(); i++)
    {
        curr = sequence[i];             // for each char in sequence
        switch (curr){                  // check current char command
            case 'f':                   // draw branch, move forward
                glScalef(0.93f,0.93f,0.93f);
                branch();
                break;
            case '+':                   // yaw clockwise
                glRotatef(-angle, 0.f, 0.f, 1.f);
                break;
            case '-':                   // yaw counter-clockwise
                glRotatef(angle, 0.f, 0.f, 1.f);
                break;
            case '^':                   // pitch clockwise
                glRotatef(-angle, 1.f, 0.f, 0.f);
                break;
            case '&':                   // pitch counter-clockwise
                glRotatef(angle, 1.f, 0.f, 0.f);
                break;
            case '<':                   // roll clockwise
                glRotatef(-angle, 0.f, 1.f, 0.f);
                break;
            case '>':                   //roll counter-clockwise
                glRotatef(angle, 0.f, 1.f, 0.f);
                break;
            case '|':                   // roll upside-down
                glRotatef(180.f, 0.f, 1.f, 0.f);
                break;
            case '[':   // "Save"
                glPushMatrix();
                break;
            case ']':   // "Restore"
                glPopMatrix();
                break;
        }
    }
    
    glPopAttrib();
    glPopMatrix();
}

void Tree::branch()
{
    glPushAttrib(GL_ALL_ATTRIB_BITS);       // save current style attributes (inc. material properties)
    float res = 0.2f*M_PI;                  // resolution (in radians: equivalent to 18 degrees)
    float r = 0.15f;                        // ratio of radius to height
    float x = r, z = 0.f;                   // initialise x and z on right of cylinder centre
    float t = 0.f;                          // initialise angle as 0

    glColor3f(0.6, 0.5, 0.5);
    glEnable(GL_TEXTURE_2D);                // enable texturing
    glBindTexture(GL_TEXTURE_2D, texID);    // bind 2D texture to shape
    
    do
    {                                    // create branch with multiple QUADS
        glBegin(GL_QUADS);
        // Create first points (with normals)
        glNormal3f(x, 0.f, z);          // define a normal facing out from the centre (0,0,0)
        glTexCoord2f(0.f, 0.f);  // assign texture coordinates to next vertex (u,v) = (0,0)
        glVertex3f(x, 0.f, z);          // bottom (with normal (x,0,z))
        
        glTexCoord2f(0.f, 1.f);  // assign texture coordinates to next vertex (u,v) = (0,1)
        glVertex3f(x, 1, z);          // top (with normal (x,0,z))
        // Iterate around circle
        t += res;                       // add increment to angle
        x = r*cos(t);                   // move x and z around circle
        z = r*sin(t);
        // Close quad (with new vertex normals)
        glNormal3f(x, 0.f, z);          // define a new normal now that x,z have moved around
        glTexCoord2f(1.f, 1.f);  // assign texture coordinates to next vertex (u,v) = (1,1)
        glVertex3f(x, 1, z);          // top
        
        glTexCoord2f(1.f, 0.f);  // assign texture coordinates to next vertex (u,v) = (1,0)
        glVertex3f(x, 0.f, z);          // bottom
        glEnd();
    } while (t <= 2.1 * M_PI);                // full rotation around circle
    glDisable(GL_TEXTURE_2D);    // disable texturing following this point
    
    glTranslatef(0.f, 0.99f, 0.f);            // translate to top of branch
    glColor3f(0.58f, 0.27f, 0.21f);
    glutSolidSphere(r,3,4);
    glPopAttrib();
}

void Tree::getSequence()
{
    
    int gen = 0, j = 0;
    std::string next;
    bool changed;
    sequence = init;
    char curr;
    while (gen < iter){                     // Iterative scheme
        next = "";                          // Start with blank
        for (unsigned int i = 0; i < sequence.size(); i++){
            curr = sequence[i];             // For each letter in the sequence
            changed = false;
            j = 0;
            for (std::vector<char>::iterator it = flags.begin(); it != flags.end(); ++it, j++){
                if (curr == *it){           // Iterate through vector of 'flags'
                    next += change[j];      // Replace flag with corresponding change string
                    changed = true;
                    break;
                }
            }
            if (!changed)                   // If current char does not match a flag
                next += curr;               // ... add it to sequence string
        }
        sequence = next;                    // Update sequence string
        gen++;                              // Recurse
    }
    //std::cout << sequence << "\n";
}


void Tree::addReplaceString(char flag, std::string str)
{
    flags.push_back(flag);                          // Add char to flags
    change.push_back(str);                          // Add string to change
    getSequence();                                  // Recompute sequence
}

void Tree::setReplaceString(char flag, std::string str)
{
    //flags.erase(flags.begin(), flags.end());        // Empty flags
    //change.erase(change.begin(), change.end());     // Empty change
    flags.push_back(flag);                          // Add char to flags
    change.push_back(str);                          // Add string to change
    getSequence();                                  // Recompute sequence
}

void Tree::setNumIter(unsigned int num)
{
    iter = num;
}

void Tree::setInitString(std::string str)
{
    init = str;
}


