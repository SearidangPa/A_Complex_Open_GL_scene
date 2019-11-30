#include "Skybox.h"

Skybox::Skybox(GLuint texTop, GLuint texLeft, GLuint texRight, GLuint texNear, GLuint texFar) :
_texTop(texTop), _texLeft(texLeft), _texRight(texRight), _texNear(texNear), _texFar(texFar),
night_time(false)
{

}

Skybox::~Skybox()
{

}
/* press v to visualize or unvisualize the lights */
void Skybox::HandleKey(unsigned char key, int state, int x, int y)
{
    //if we don't check the state, visualization will only last when you hold the key
    if (!state) return;
    switch (key){
        case 'n':
            night_time = !night_time;
            break;
    }
}
void Skybox::Display()
{
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	
	glTranslatef(pos[0], pos[1], pos[2]);
	glScalef(scale[0], scale[1], scale[2]);

    /* display darker color at night time */
    if (!night_time)    //day time
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    else{               //night time
        glColor4f(0.1f, 0.1f, 0.1f, 1.0f);
    }
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);

	// LEFT SIDE
	glBindTexture(GL_TEXTURE_2D, _texLeft); 
	glBegin(GL_QUADS);
	{
		glTexCoord2f(1.f, 1.f);  // (s,t) = (1,1)
		glVertex3f(-1.f, 1.f, -1.f);
		glTexCoord2f(0.f, 1.f);  // (s,t) = (0,1)
		glVertex3f(-1.f, 1.f, 1.f);
		glTexCoord2f(0.f, 0.f);  // (s,t) = (0,0)
		glVertex3f(-1.f, -1.f, 1.f);
		glTexCoord2f(1.f, 0.f);  // (s,t) = (1,0)
		glVertex3f(-1.f, -1.f, -1.f);
	}
	glEnd();

	// RIGHT SIDE
	glBindTexture(GL_TEXTURE_2D, _texRight);
	glBegin(GL_QUADS);
	{
		glTexCoord2f(1.f, 1.f);  // (s,t) = (1,1)
		glVertex3f(1.f, 1.f, 1.f);
		glTexCoord2f(0.f, 1.f);  // (s,t) = (0,1)
		glVertex3f(1.f, 1.f, -1.f);
		glTexCoord2f(0.f, 0.f);  // (s,t) = (0,0)
		glVertex3f(1.f, -1.f, -1.f);
		glTexCoord2f(1.f, 0.f);  // (s,t) = (1,0)
		glVertex3f(1.f, -1.f, 1.f);
	}
	glEnd();

	//  FAR SIDE
	glBindTexture(GL_TEXTURE_2D, _texFar); 
	glBegin(GL_QUADS);
	{
		glTexCoord2f(1.f, 1.f);  // (s,t) = (1,1)
		glVertex3f(1.f, 1.f, -1.f);
		glTexCoord2f(0.f, 1.f);  // (s,t) = (0,1)
		glVertex3f(-1.f, 1.f, -1.f);
		glTexCoord2f(0.f, 0.f);  // (s,t) = (0,0)
		glVertex3f(-1.f, -1.f, -1.f);
		glTexCoord2f(1.f, 0.f);  // (s,t) = (1,0)
		glVertex3f(1.f, -1.f, -1.f);
	}
	glEnd();

	// NEAR SIDE
	glBindTexture(GL_TEXTURE_2D, _texNear);
	glBegin(GL_QUADS);
	glTexCoord2f(1.f, 1.f);  // (s,t) = (1,1)
	glVertex3f(-1.f, 1.f, 1.f);
	glTexCoord2f(0.f, 1.f);  // (s,t) = (0,1)
	glVertex3f(1.f, 1.f, 1.f);
	glTexCoord2f(0.f, 0.f);  // (s,t) = (0,0)
	glVertex3f(1.f, -1.f, 1.f);
	glTexCoord2f(1.f, 0.f);  // (s,t) = (1,0)
	glVertex3f(-1.f, -1.f, 1.f);
	glEnd();

	// TOP SIDE
	glBindTexture(GL_TEXTURE_2D, _texTop); 
	glBegin(GL_QUADS);
	{
		glTexCoord2f(1.f, 1.f);  // (s,t) = (1,1)
		glVertex3f(1.f, 1.f, 1.f);
		glTexCoord2f(0.f, 1.f);  // (s,t) = (0,1)
		glVertex3f(-1.f, 1.f, 1.f);
		glTexCoord2f(0.f, 0.f);  // (s,t) = (0,0)
		glVertex3f(-1.f, 1.f, -1.f);
		glTexCoord2f(1.f, 0.f);  // (s,t) = (1,0)
		glVertex3f(1.f, 1.f, -1.f);
	}
	glEnd();

	glBindTexture(GL_TEXTURE_2D,NULL);

	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);

	glPopAttrib();
	glPopMatrix();
}
