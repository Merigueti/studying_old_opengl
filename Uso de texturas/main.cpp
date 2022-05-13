#include <GLFW/glfw3.h>
#include<GL/glu.h>
#include<iostream>
#include"stb_image.h"

static float angulo = 0.0;
GLuint obj[3];
GLuint texID[3];

void carregaTextura(GLuint tex_id, std::string filePath)
{
	unsigned char* imgData;
	int largura, altura, canais;

	stbi_set_flip_vertically_on_load(true);
	imgData = stbi_load(filePath.c_str(), &largura, &altura, &canais, 4);
	if (imgData)
	{
		glBindTexture(GL_TEXTURE_2D, tex_id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, largura, altura, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgData);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		
		stbi_image_free(imgData);
	}
	else {
		std::cout << "ERRO:: Nao foi possivel carregar a textura!" << filePath.c_str() << std::endl;
	}
	
}


void triangulo(GLuint id,GLuint texid,float SIZE)
{
	glNewList(id, GL_COMPILE);
	glBindTexture(GL_TEXTURE_2D, texid);
	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.0, 0.0); glVertex3f(-SIZE, -SIZE, 0.0);
	glTexCoord2f(1.0, 0.0); glVertex3f(SIZE, -SIZE, 0.0);
	glTexCoord2f(0.5, 1.0); glVertex3f(0.0, SIZE, 0.0);
	glEnd();
	glEndList();
}

void quadrado(GLuint id, GLuint texid, float SIZE)
{
	glNewList(id, GL_COMPILE);
	glColor3f(1.0, 1.0, 1.0);
	glBindTexture(GL_TEXTURE_2D, texid);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-SIZE, -SIZE, 0.0);
	glTexCoord2f(1.0, 0.0); glVertex3f(SIZE, -SIZE, 0.0);
	glTexCoord2f(1.0, 1.0); glVertex3f(SIZE, SIZE, 0.0);
	glTexCoord2f(0.0, 1.0); glVertex3f(-SIZE, SIZE, 0.0);
	glEnd();
	glEndList();
}


void init()
{
	glClearColor(0.0, 0.15, 0.25, 1.0); // cor de fundo
	glEnable(GL_DEPTH_TEST);
	
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glGenTextures(3, texID);
	carregaTextura(texID[0], "images/brick.png");
	carregaTextura(texID[1], "images/painted_brick.png");
	carregaTextura(texID[2], "images/wood.png");

	obj[0] = glGenLists(3);
	obj[1] = obj[0] + 1;
	obj[2] = obj[0] + 2;

	quadrado(obj[0],texID[0],8);
	quadrado(obj[1],texID[1],8);
	triangulo(obj[2],texID[2],8);
}

void redimensiona(int w, int h)
{
	glViewport(0, 0, w, h);

	float aspect = (float)w / (float)h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, aspect, 0.1, 500.0);

	glMatrixMode(GL_MODELVIEW);
}


void desenha(float dt)
{
	float veloc_ang = 60 * dt;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	glPushMatrix();
	glTranslatef(-20.0, 0.0, -50.0);
	glRotatef(angulo, 1.0, 1.0, 0.0);
	glCallList(obj[0]);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(20.0, 0.0, -50.0);
	glRotatef(-angulo, 1.0, 1.0, 0.0);
	glCallList(obj[1]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, -60.0);
	glRotatef(-angulo, 0.0, 1.0, 0.0);
	glCallList(obj[2]);
	glPopMatrix();

	angulo += veloc_ang;
}


int main(void)
{
	
	const int LARGURA = 800;
	const int ALTURA = 600;
	glfwInit();
	GLFWwindow* window = glfwCreateWindow(LARGURA, ALTURA, "Textura", NULL, NULL);
	glfwMakeContextCurrent(window);

	init();

	float lastTime = glfwGetTime();
	while (!glfwWindowShouldClose(window))
	{
		float currentTime = glfwGetTime();
		float dt = currentTime - lastTime;
		lastTime = currentTime;

		glfwPollEvents();
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		}

		
		int largura, altura;
		glfwGetFramebufferSize(window, &largura, &altura);

		redimensiona(largura, altura);

		desenha(dt);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);
	}
	glDisable(GL_TEXTURE_2D);
	glDeleteTextures(3, texID);
	glfwTerminate();
	return 0;
}