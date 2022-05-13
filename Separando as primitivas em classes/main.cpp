#include<GLFW/glfw3.h>
#include<GL/glu.h>
#include<iostream>
#include<vector>
#include<cstdlib>
#include "Primitiva.h"
#include"Terreno.h"
#include "Cubo.h"
#include "Esfera.h"
#include "Camera.h"
#include "Textura.h"

static float lastMousePos = 0.0;
static bool firstTimeMouse = true;

const GLuint total_objetos = 45;
std::vector<Primitiva*> objetos;

Camera camera(vec3(-100, 0, 0));

enum{GRASS};
Textura FloorTex[1];

enum{BRICK,PAINTED,MASK,WOOD,METAL_CUBO};
Textura CuboTex[5];

enum{SOL,TERRA,MARTE,LUA,METAL_PLANET};
Textura PlanetTex[5];

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
	glLoadIdentity();
	
	camera.ativar();
	
	for (int i = 0; i < total_objetos; i++)
		objetos[i]->Display(dt);
		
}

float aleatorio(float a, float b)
{
	float n = (float)rand() / RAND_MAX;
	float t = b - a;
	float r = a + n * t;
	return r;
}

void teclado_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key==GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
	else if (key==GLFW_KEY_W &&(action == GLFW_PRESS || action==GLFW_REPEAT))
	{
		// Forward
		camera.forward();
	}
	else if (key == GLFW_KEY_S && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		// Back
		camera.back();

	}
	else if (key == GLFW_KEY_A && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		// Left
		camera.left();

	}
	else if (key == GLFW_KEY_D && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		// Right
		camera.right();
	}
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	float dx;

	if (firstTimeMouse)
	{
		dx = 0;
		lastMousePos = xpos;
		firstTimeMouse = false;
	}
	dx = xpos - lastMousePos;
	lastMousePos = xpos;
	camera.updateYaw(dx);
	camera.update();
}

void init(GLFWwindow* window)
{
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetKeyCallback(window, teclado_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwMaximizeWindow(window);
	//glClearColor(0.0, 0.15, 0.25, 1.0); // cor de fundo
	glClearColor(0.0, 0.0, 0.0, 1.0);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	FloorTex[GRASS].load("images/terreno/grass.jpg", true);

	CuboTex[BRICK].load("images/cubo/brick.png", true);
	CuboTex[WOOD].load("images/cubo/wood.png", true);
	CuboTex[METAL_CUBO].load("images/cubo/metal.png", true);
	CuboTex[PAINTED].load("images/cubo/painted_brick.png", true);
	CuboTex[MASK].load("images/cubo/mask.png", true);

	PlanetTex[SOL].load("images/esfera/sun.jpg", true);
	PlanetTex[TERRA].load("images/esfera/earth.jpg", true);
	PlanetTex[MARTE].load("images/esfera/mars.jpg", true);
	PlanetTex[LUA].load("images/esfera/moon.jpg", true);
	PlanetTex[METAL_PLANET].load("images/esfera/metal.jpg", true);


	Terreno* terreno = new Terreno();
	terreno->CriarTerreno(500, &FloorTex[GRASS]);
	objetos.push_back(terreno);

	for (int i = 1; i < total_objetos; i++)
	{
		float x = aleatorio(-200, 200);
		float y = aleatorio(15, 30);
		float z = aleatorio(-300,300);
		vec3 pos = vec3(x, y, z);

		float k = (float)rand() / RAND_MAX;
		if (k <= 0.5)
		{
			Textura* tex;
			Esfera* esfera = new Esfera();
			if (k <= 0.1)
			{
				tex = &PlanetTex[SOL];
				esfera->CriarEsfera(tex, 10.0, 30, 30, pos);
				esfera->RodaX();
				esfera->RodaY();
				esfera->RodaZ();
			}
			else if (k <= 0.2)
			{
				tex = &PlanetTex[TERRA];
				esfera->CriarEsfera(tex, 8, 30, 30, pos);
				esfera->RodaY();
			}
			else if (k <= 0.3)
			{
				tex = &PlanetTex[MARTE];
				esfera->CriarEsfera(tex, 7, 30, 30, pos);
				esfera->RodaY();
			}
			else if (k <= 0.4)
			{
				tex = &PlanetTex[LUA];
				esfera->CriarEsfera(tex, 6, 30, 30, pos);
				esfera->RodaY();
				esfera->RodaX();
				esfera->RodaZ();
			}
			else
			{
				tex = &PlanetTex[METAL_PLANET];
				esfera->CriarSuperShape(tex, 8, 30, 30, pos);
				esfera->RodaZ();
				esfera->RodaX();
				esfera->RodaY();
			}
			objetos.push_back(esfera);
		}
		else
		{
			Textura* tex;
			Cubo* cubo = new Cubo();			
			if (k <= 0.60)
				tex = &CuboTex[WOOD];
			else if (k <= 0.70)
				tex = &CuboTex[METAL_CUBO];
			else if (k <= 0.80)
				tex = &CuboTex[MASK];
			else if (k <= 0.90)
				tex = &CuboTex[PAINTED];
			else
				tex = &CuboTex[BRICK];
			cubo->CriarCubo(tex, 10, pos);
			cubo->RodaX();
			cubo->RodaY();
			cubo->RodaZ();
			objetos.push_back(cubo);
		}
	}

}


int main(void)
{

	const int LARGURA = 800;
	const int ALTURA = 600;

	/* Initialize the library */
	glfwInit();

	/* Create a windowed mode window and its OpenGL context */
	GLFWwindow* window = glfwCreateWindow(LARGURA, ALTURA, "Camera OpenGL", NULL, NULL);

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	// -- inicio
	init(window);

	float valor = 0.0;
	float lastTime = 0.0;

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		float currentTime = (float)glfwGetTime();
		float dt = currentTime - lastTime;
		lastTime = currentTime;

		/* Poll for and process events */
		glfwPollEvents();
		
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		int largura, altura;
		glfwGetFramebufferSize(window, &largura, &altura);

		redimensiona(largura, altura);

		desenha(dt);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);
	}

	for (unsigned i = 0; i < total_objetos; i++)
		delete objetos[i];
	objetos.clear();

	glfwTerminate();
	return 0;
}