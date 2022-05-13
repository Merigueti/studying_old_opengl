#include "Terreno.h"
#include"cores.h"


Terreno::Terreno()
{
	m_id = glGenLists(1);
}


Terreno::~Terreno()
{
}

void Terreno::CriarTerreno(float SIZE,Textura *tex)
{
	float L = SIZE;
	float incr = 1.0;
	float y = -0.5;
	glNewList(m_id, GL_COMPILE);
	glColor3fv(branco_gelo);
	tex->Bind();
	glBegin(GL_QUADS);
	glTexCoord2f(-100,-100);glVertex3f(-L,y,L);
	glTexCoord2f(100,-100);glVertex3f(L,y,L);
	glTexCoord2f(100,100);glVertex3f(L,y,-L);
	glTexCoord2f(-100,100);glVertex3f(-L,y,-L);
	glEnd();
	tex->UnBind();
	glEndList();

}
