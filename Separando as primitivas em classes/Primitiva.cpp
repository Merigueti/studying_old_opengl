#include "Primitiva.h"


Primitiva::Primitiva():
	m_id(0),m_pos(vec3(0,0,0)),
	m_ang(0),m_rodax(false),
	m_roday(false),m_rodaz(false)
{
	m_fps = aleatorio(30, 60);
}


Primitiva::~Primitiva()
{
	glDeleteLists(1, m_id);
}

void Primitiva::Display(float dt)
{
	float velocAng = m_fps * dt;
	glPushMatrix();
	glTranslatef(m_pos.x, m_pos.y, m_pos.z);
	if (m_rodax)
		glRotatef(m_ang, 1.0, 0.0, 0.0);
	if (m_roday)
		glRotatef(m_ang, 0.0, 1.0, 0.0);
	if (m_rodaz)
		glRotatef(m_ang, 0.0, 0.0, 1.0);
	glCallList(m_id);
	glPopMatrix();
	m_ang += velocAng;
	if (m_ang >= 360.0)
		m_ang = 0.0;
}

void Primitiva::RodaX()
{
	m_rodax = true;
}

void Primitiva::RodaY()
{
	m_roday = true;
}

void Primitiva::RodaZ()
{
	m_rodaz = true;
}

float Primitiva::aleatorio(float a, float b)
{
	float comp = b - a;
	float r = (float)rand() / (float)RAND_MAX;
	return a+r*comp;
}

