#include "Cubo.h"



Cubo::Cubo()
{
	m_id = glGenLists(1);
}


Cubo::~Cubo()
{
}

void Cubo::CriarCubo(Textura * textura, float SIZE, vec3 pos)
{
	float d = SIZE / 2.0;

	m_pos = vec3(pos);
	vec3 v1(-d, d, d);
	vec3 v2(-d, -d, d);
	vec3 v3(d, -d, d);
	vec3 v4(d, d, d);

	vec3 v5(d, d, -d);
	vec3 v6(d, -d, -d);
	vec3 v7(-d, -d, -d);
	vec3 v8(-d, d, -d);


	glNewList(m_id, GL_COMPILE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	textura->Bind();
	// frente
	rect(v1, v2, v3, v4);

	// direita
	rect(v4, v3, v6, v5);

	// back
	rect(v5, v8, v7, v6);

	//esquerda
	rect(v1, v8, v7, v2);

	//topo
	rect(v1, v4, v5, v8);

	//bottom
	rect(v2, v7, v6, v3);

	textura->UnBind();
	glEndList();
}

void Cubo::rect(vec3 p1, vec3 p2, vec3 p3, vec3 p4)
{
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3fv(&p1.x);
	glTexCoord2f(1.0, 0.0); glVertex3fv(&p2.x);
	glTexCoord2f(1.0, 1.0); glVertex3fv(&p3.x);
	glTexCoord2f(0.0, 1.0); glVertex3fv(&p4.x);
	glEnd();
}
