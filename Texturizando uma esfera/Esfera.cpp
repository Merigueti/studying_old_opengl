#include <vector>
#include <GL/gl.h>
#include "Esfera.h"

Esfera::Esfera(/* args */):
    m_id(0),
    m_pos(vec3(0,0,0)),m_ang(0), m_fps(0), 
    m_rodax(false), m_roday(false), m_rodaz(false)
{

}

Esfera::~Esfera()
{
    glDeleteLists(m_id,1);
}

void Esfera::criarEsfera(Textura* tex, float raio, unsigned int nStacks,unsigned int nSectors, vec3 pos)
{
	std::vector<std::vector<vec3> > pontos;
	std::vector<std::vector<vec2> > texCoords;

	const GLfloat PI = 3.14159265359;
	const GLfloat TWO_PI = 2*PI;
	const GLfloat HALF_PI = PI/2.0;

    m_id = glGenLists(1);
    m_pos = vec3(pos);
    m_fps = aleatorio(30,60);

	GLfloat deltaPhi = PI / nStacks;
	GLfloat deltaTheta = TWO_PI / nSectors;

	for (GLuint i = 0; i <= nStacks; i++)
	{
		GLfloat phi = -HALF_PI + i * deltaPhi;
		GLfloat temp = raio * cos(phi);
		GLfloat y = raio * sin(phi);

		std::vector<vec3> pts;
		std::vector<vec2> texs;

		for (GLuint j = 0; j <= nSectors; j++)
		{
			GLfloat theta = j * deltaTheta;
			GLfloat x = temp * sin(theta);
			GLfloat z = temp * cos(theta);
			
			GLfloat s = theta / TWO_PI;
			GLfloat t = phi / PI + 0.5;

			pts.push_back(vec3(x, y, z));
			texs.push_back(vec2(s, t));
		}// next j

		pontos.push_back(pts);
		texCoords.push_back(texs);
	}// next i


	
	glNewList(m_id, GL_COMPILE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	
	tex->Bind();
	
	for (GLuint i = 0; i < nStacks; i++)
	{
		glBegin(GL_TRIANGLE_STRIP);

		for (GLuint j = 0; j <= nSectors; j++)
		{
			glTexCoord2fv(&texCoords[i][j].x); glVertex3fv(&pontos[i][j].x);
			glTexCoord2fv(&texCoords[i+1][j].x); glVertex3fv(&pontos[i+1][j].x);
		}
		glEnd();
	}
	glDisable(GL_CULL_FACE);
	tex->UnBind();
	glEndList();
}




void Esfera::Display(float dt){
    float velocAng = m_fps * dt;
	glLoadIdentity();
	glTranslatef(m_pos.x, m_pos.y, m_pos.z);
    if(m_rodax)
	    glRotatef(m_ang, 1.0, 0.0, 0.0);
    if(m_roday)
	    glRotatef(m_ang, 0.0, 1.0, 0.0);
    if(m_rodaz)
	    glRotatef(m_ang, 0.0, 0.0, 1.0);
	glCallList(m_id);
	
	m_ang += velocAng;
	if (m_ang >= 360.0)
		m_ang = 0.0;
}
void Esfera::rodarX(){m_rodax=true;}
void Esfera::rodarY(){m_roday=true;}
void Esfera::rodarZ(){m_rodaz=true;}

float Esfera::aleatorio(float a, float b)
{
	float comp = b - a;
	float r = (float)rand() / (float)RAND_MAX;

	return a+r*comp;
}

