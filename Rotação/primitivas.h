#include <GL/glu.h>
#include <vector>
#include<cmath>
#include "colors.h"

struct vec3{
    float x, y, z;
    vec3() :x(0.0), y(0.0), z(0.0){}
    vec3(float x_, float y_, float z_):x(x_), y(y_), z(z_){}
};



void rect(vec3 p1,vec3 p2,vec3 p3,vec3 p4, color cor){
    glColor3fv(cor);
    glBegin(GL_QUADS);
        glVertex3fv(&p1.x);
        glVertex3fv(&p2.x);
        glVertex3fv(&p3.x);
        glVertex3fv(&p4.x);
    glEnd();
}

void drawCube(float cubesize){
    float d = cubesize/2.0;

    vec3 v1 = { -d,  d, d};
	vec3 v2 = { -d, -d, d};
	vec3 v3 = {  d, -d, d};
	vec3 v4 = {  d,  d, d};

	vec3 v5 = {  d,  d, -d};
	vec3 v6 = {  d, -d, -d};
	vec3 v7 = { -d, -d, -d};
	vec3 v8 = { -d,  d, -d};

	rect(v1, v2, v3, v4, vermelho);// frente
	rect(v4, v3, v6, v5, azul);// direita
	rect(v5, v8, v7, v6, amarelo);// back
	rect(v1, v8, v7, v2, verde);//esquerda
	rect(v1, v4, v5, v8, laranja);//topo
	rect(v2, v7, v6, v3, violeta);//bottom
}

void drawSpheres(unsigned int& id, GLfloat raio, GLuint nStacks, GLuint nSectors){
    std::vector<std::vector<GLuint> > indices;
    std::vector<vec3> pontos;


    const GLfloat PI = 3.14159265359;
    GLfloat deltaPhi = PI/nSectors;
    GLfloat deltaTheta = 2*PI/nSectors;

for (GLuint i = 0; i <= nStacks; i++)
	{
		GLfloat phi = -PI / 2.0 + i * deltaPhi;
		GLfloat temp = raio * cos(phi);
		GLfloat y = raio * sin(phi);\

        std::vector<GLuint> pt;


		for (GLuint j = 0; j < nSectors; j++)
		{
			GLfloat theta = j * deltaTheta;
			GLfloat x = temp * sin(theta);
			GLfloat z = temp * cos(theta);

			pontos.push_back(vec3(x, y, z));
            GLuint index =  pontos.size()-1;
            pt.push_back(index);

		}// next j
        indices.push_back(pt);

	}// next i

    glNewList(id, GL_COMPILE);
        for (GLuint i = 0; i < nStacks; i++)
        {

            if (i % 3 == 0)
                glColor3fv(laranja);
            else if (i % 3 == 1)
                glColor3fv(cinza);
            else
                glColor3fv(vermelho);

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
                    index = indices[i+1][0];
                    glVertex3fv(&pontos[index].x);
                }
            }
            glEnd();
        }
    glEndList();

}