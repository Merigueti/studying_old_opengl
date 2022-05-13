#include "Primitiva.h"


Primitiva::Primitiva()
{
	m_id = 0;
	m_pos = vec3(0, 0, 0);
	m_angX = 0;
	m_angY = 0;
	m_angZ = 0;
	m_scale = 1.f;
}


Primitiva::~Primitiva()
{
	glDeleteLists(1, m_id);
}

void Primitiva::Display()
{
	glPushMatrix();
	glTranslatef(m_pos.x, m_pos.y, m_pos.z);

	glRotatef(m_angX, 1.0, 0.0, 0.0);
	glRotatef(m_angY, 0.0, 1.0, 0.0);
	glRotatef(m_angZ, 0.0, 0.0, 1.0);
	glScalef(m_scale, m_scale, m_scale);
	glCallList(m_id);
	glPopMatrix();
}

Terreno::Terreno()
{
	m_id = glGenLists(1);
}

void Terreno::Create(float SIZE)
{
	float L = SIZE;
	float incr = 2.f;
	float y = -0.5f;
	glNewList(m_id, GL_COMPILE);
	glColor3f(0.88f, 0.91f, 0.89f);// branco gelo
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

Cubo::Cubo()
{
	m_id = glGenLists(1);
}

void Cubo::Create(Textura * textura,float SIZE, vec3 pos)
{
	float d = SIZE / 2.0;

	m_pos = vec3(pos);
	// Frontal[v1,v2,v3,v4]=anti-horario
	vec3 v1(-d, d, d);//superior esquerdo
	vec3 v2(-d, -d, d);//inferior esquerdo
	vec3 v3(d, -d, d);//inferior direito
	vec3 v4(d, d, d);// superior direito

	// Visão Frontal do Back
	// Back[v5,v6,v7,v8]=anti-horário
	vec3 v5(d, d, -d);// superior esq
	vec3 v6(d, -d, -d);// inferior esq
	vec3 v7(-d, -d, -d);// inferior dir
	vec3 v8(-d, d, -d);// sup dir


	glNewList(m_id, GL_COMPILE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	textura->Bind();
	// frente
	Rect(v1, v2, v3, v4);

	// direita
	Rect(v4, v3, v6, v5);

	// back
	Rect(v5, v6, v7, v8);

	//esquerda
	Rect(v1, v8, v7, v2);

	//topo
	Rect(v1, v4, v5, v8);

	//bottom
	Rect(v2, v7, v6, v3);

	textura->UnBind();
	glEndList();
}

void Cubo::Rect(vec3 p1, vec3 p2, vec3 p3, vec3 p4)
{
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3fv(&p1.x);
	glTexCoord2f(1.0, 0.0); glVertex3fv(&p2.x);
	glTexCoord2f(1.0, 1.0); glVertex3fv(&p3.x);
	glTexCoord2f(0.0, 1.0); glVertex3fv(&p4.x);
	glEnd();
}


Esfera::Esfera()
{
	m_id = glGenLists(1);
}

void Esfera::Create(Textura * tex, float raio, unsigned nStacks, unsigned nSectors, vec3 pos)
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

Supershape::Supershape()
{
	m_id = glGenLists(1);
}

void Supershape::Create(Textura * tex, float raio, unsigned nStacks, unsigned nSectors, vec3 pos)
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

float Supershape::superShape(float ang, float m, float n1, float n2, float n3)
{
	float val1 = abs(cos(m*ang / 4.0));
	val1 = pow(val1, n2);

	float val2 = abs(sin(m*ang / 4.0));
	val2 = pow(val2, n3);

	float val = val1 + val2;
	val = pow(val, -1.0 / n1);
	return val;

}
