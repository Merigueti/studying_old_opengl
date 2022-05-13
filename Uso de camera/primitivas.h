#pragma once
#include<vector>
#include<cmath>
#include "colors.h"
#include "cg.h"


void rect(vec3 p1, vec3 p2, vec3 p3, vec3 p4, color cor)
{
	glColor3fv(cor);
	glBegin(GL_QUADS);
	glVertex3fv(&p1.x);
	glVertex3fv(&p2.x);
	glVertex3fv(&p3.x);
	glVertex3fv(&p4.x);
	glEnd();
}
void desenhaCubo(GLuint id, float s)
{
	float d = s / 2.0;

	vec3 v1(-d, d, d);
	vec3 v2(-d, -d, d);
	vec3 v3(d, -d, d);
	vec3 v4(d, d, d);

	vec3 v5(d, d, -d);
	vec3 v6(d, -d, -d);
	vec3 v7(-d, -d, -d);
	vec3 v8(-d, d, -d);


	glNewList(id, GL_COMPILE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	// frente
	rect(v1, v2, v3, v4, vermelho);

	// direita
	rect(v4, v3, v6, v5, azul);

	// back
	rect(v5, v8, v7, v6, amarelo);

	//esquerda
	rect(v1, v8, v7, v2, verde);

	//topo
	rect(v1, v4, v5, v8, laranja);

	//bottom
	rect(v2, v7, v6, v3, violeta);
	glEndList();
}


void desenhaEsfera(unsigned int& id, color cor, GLfloat raio, GLuint nStacks, GLuint nSectors)
{
	std::vector< std::vector<GLuint> > indices;

	std::vector<vec3> pontos;
	const GLfloat PI = 3.14159265359;

	GLfloat deltaPhi = PI / nStacks;
	GLfloat deltaTheta = 2 * PI / nSectors;

	for (GLuint i = 0; i <= nStacks; i++)
	{
		GLfloat phi = -PI / 2.0 + i * deltaPhi;
		GLfloat temp = raio * cos(phi);
		GLfloat y = raio * sin(phi);

		std::vector<GLuint> pt;

		for (GLuint j = 0; j < nSectors; j++)
		{
			GLfloat theta = j * deltaTheta;
			GLfloat x = temp * sin(theta);
			GLfloat z = temp * cos(theta);

			pontos.push_back(vec3(x, y, z));
			GLuint index = pontos.size() - 1;
			pt.push_back(index);
		}// next j

		indices.push_back(pt);
	}// next i


	// --- plota pontos 
	/*glColor3fv(vermelho);
	glPointSize(2.5);
	glBegin(GL_POINTS);
	for (GLuint i = 0; i < pontos.size(); i++)
	{
		glVertex3fv(&pontos[i].x);
	}
	glEnd();*/


	glNewList(id, GL_COMPILE);

	glColor3fv(cor);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);

	for (GLuint i = 0; i < nStacks; i++)
	{
		glBegin(GL_TRIANGLE_STRIP);

		for (GLuint j = 0; j < nSectors; j++)
		{
			GLuint index = indices[i][j];
			glVertex3fv(&pontos[index].x);
			index = indices[i + 1][j];
			glVertex3fv(&pontos[index].x);

			if (j == nSectors - 1)
			{
				index = indices[i][0];
				glVertex3fv(&pontos[index].x);
				index = indices[i + 1][0];
				glVertex3fv(&pontos[index].x);
			}
		}
		glEnd();
	}
	glDisable(GL_CULL_FACE);
	glEndList();
}


void desenhaTerreno(unsigned int id)
{
	float L = 500.0;
	float incr = 1.0;
	float y = -0.5;
	glNewList(id, GL_COMPILE);
	glColor3fv(branco_gelo);
	glBegin(GL_LINES);
	for (float i = -L; i <= L; i += incr)
	{
		// Verticais
		glVertex3f(i, y, -L);
		glVertex3f(i, y, L);

		// Horizontais
		glVertex3f(-L, y, i);
		glVertex3f(L, y, i);
	}
	glEnd();
	glEndList();
}