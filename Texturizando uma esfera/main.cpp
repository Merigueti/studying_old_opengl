#include<GLFW/glfw3.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<iostream>
#include<vector>
#include"cores.h"
#include "Esfera.h"


unsigned int esferaID;
float angulo = 0.0;

Textura PlanetTex[5];
enum{TERRA, MARTE, METAL, LUA, SOL};

Esfera terra, marte, metal, lua, sol;

void redimensiona(int w, int h)
{
	glViewport(0, 0, w, h);

	float aspect = (float)w / (float)h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, aspect, 0.1, 500.0);

	glMatrixMode(GL_MODELVIEW);
}

void desenha(float dt){
	glLoadIdentity();
	terra.Display(dt);
	sol.Display(dt);
}


void init() {

	glClearColor(0.0, 0.15f, 0.25f, 1.f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	PlanetTex[TERRA].load("earth.jpg");
	PlanetTex[SOL].load("sun.jpg");

	terra.criarEsfera(&PlanetTex[TERRA], 7, 30, 30, vec3(10, 0, -50));
	sol.criarEsfera(&PlanetTex[SOL], 7, 30, 30, vec3(-10, 0, -50));
	sol.rodarY();
	terra.rodarY();
	//desenhaEsfera(esferaID, &PlanetTex[TERRA], 8, 30, 30);
}




int main(void)
{

	const int LARGURA = 800;
	const int ALTURA = 600;

	glfwInit();
	GLFWwindow* window = glfwCreateWindow(LARGURA, ALTURA, "Textura Esfera", NULL, NULL);
	glfwMakeContextCurrent(window);

	init();

	float lastTime = (float)glfwGetTime();
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		float currentTime = (float)glfwGetTime();
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

		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		desenha(dt);


		/* Swap front and back buffers */
		glfwSwapBuffers(window);
	}
	glDeleteLists(esferaID, 1);
	glDisable(GL_TEXTURE_2D);
	glfwTerminate();
	return 0;
}