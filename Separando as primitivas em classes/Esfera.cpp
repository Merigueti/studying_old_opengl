#include "Esfera.h"
#include<vector>


Esfera::Esfera()
{
	m_id = glGenLists(1);
}


Esfera::~Esfera()
{
}

void Esfera::CriarEsfera(Textura * tex, float raio, unsigned nStacks, unsigned nSectors, vec3 pos)
{
	std::vector<std::vector<vec3> > pontos;
	std::vector<std::vector<vec2> > texCoords;

	const GLfloat PI = 3.14159265359;
	const GLfloat TWO_PI = 2 * PI;
	const GLfloat HALF_PI = PI / 2.0;

	GLfloat deltaPhi = PI / nStacks;
	GLfloat deltaTheta = TWO_PI / nSectors;

	m_pos = vec3(pos);

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
			glTexCoord2fv(&texCoords[i + 1][j].x); glVertex3fv(&pontos[i + 1][j].x);
		}
		glEnd();
	}
	glDisable(GL_CULL_FACE);
	tex->UnBind();
	glEndList();

}

void Esfera::CriarSuperShape(Textura * tex, float raio, unsigned nStacks, unsigned nSectors, vec3 pos)
{
	std::vector<std::vector<vec3> > pontos;
	std::vector<std::vector<vec2> > texCoords;

	const GLfloat PI = 3.14159265359;
	const GLfloat TWO_PI = 2 * PI;
	const GLfloat HALF_PI = PI / 2.0;

	GLfloat deltaPhi = PI / nStacks;
	GLfloat deltaTheta = TWO_PI / nSectors;

	m_pos = vec3(pos);
	
	for (GLuint i = 0; i <= nStacks; i++)
	{
		GLfloat phi = -HALF_PI + i * deltaPhi;
		float r1 = superShape(phi, 7, 0.2, 1.7, 1.7);
		GLfloat temp = r1 * raio * cos(phi);
		GLfloat y = r1 * raio * sin(phi);

		std::vector<vec3> pts;
		std::vector<vec2> texs;

		for (GLuint j = 0; j <= nSectors; j++)
		{
			GLfloat theta = j * deltaTheta;
			float r2 = superShape(theta, 7, 0.2, 1.7, 1.7);
			GLfloat x = r2 * temp * sin(theta);
			GLfloat z = r2 * temp * cos(theta);

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
			glTexCoord2fv(&texCoords[i + 1][j].x); glVertex3fv(&pontos[i + 1][j].x);
		}
		glEnd();
	}
	glDisable(GL_CULL_FACE);
	tex->UnBind();
	glEndList();
}

float Esfera::superShape(float ang, float m, float n1, float n2, float n3)
{
	float val1 = abs(cos(m*ang / 4.0));
	val1 = pow(val1, n2);

	float val2 = abs(sin(m*ang / 4.0));
	val2 = pow(val2, n3);

	float val = val1 + val2;
	val = pow(val, -1.0 / n1);
	return val;

}
