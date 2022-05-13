#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include "primitivas.h"
#include "Camera.h"
#include "colors.h"

static float angulo = 5.0;
static float lastMousePos = 0;
static bool firstTimeMouse = true;

// Display List
struct Objeto {
	GLuint id;
	vec3 pos;
	Objeto() :id(0), pos(vec3(0.0, 0.0, 0.0)) {}
};


const GLuint total_objetos = 25;
std::vector<Objeto> objetos;

Camera camera(vec3(-100, 0, 0));

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

	float veloc_ang = 60.0*dt;// 60 graus por segundo

	glLoadIdentity();


	camera.ativar();

	glCallList(objetos[0].id);

	for (int i = 1; i < total_objetos; i++)
	{
		float x = objetos[i].pos.x;
		float y = objetos[i].pos.y;
		float z = objetos[i].pos.z;

		glPushMatrix();
		glTranslatef(x, y, z);
		glRotatef(angulo, 1.0, 1.0, 0.0);
		glCallList(objetos[i].id);
		glPopMatrix();
	}

	angulo += veloc_ang;
	if (angulo >= 360.0)
		angulo = 0.0;
}

float aleatorio(float a, float b)
{
	float n = (float)rand() / RAND_MAX;
	float t = b - a;
	float r = a + n * t;
	return r;
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos){
	float dx;

	if(firstTimeMouse){
		dx = 0;
		lastMousePos = (float)xpos;
		firstTimeMouse = false;
	}
	
	dx = (float)xpos-lastMousePos;
	lastMousePos = (float)xpos;
	camera.updateYaw(dx);
	camera.update();

}



void teclado_callback(GLFWwindow* window,int key, int scancode, int action, int mods){

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
	if (key == GLFW_KEY_W && (action == GLFW_PRESS || action == GLFW_REPEAT)){
		camera.forward();
	
	}
	if (key == GLFW_KEY_S && (action == GLFW_PRESS || action == GLFW_REPEAT)){
		camera.back();
	
	}
	if (key == GLFW_KEY_A && (action == GLFW_PRESS || action == GLFW_REPEAT)){
		camera.left();
	
	}
	if (key == GLFW_KEY_D && (action == GLFW_PRESS || action == GLFW_REPEAT)){
		camera.right();
	}
}

void init(GLFWwindow* window)
{
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetKeyCallback(window, teclado_callback);
	glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_DISABLED);

	//glClearColor(0.0, 0.15, 0.25, 1.0); // cor de fundo
	glClearColor(0.0, 0.0, 0.0, 1.0);

	glEnable(GL_DEPTH_TEST);

	for (int i = 0; i < total_objetos; i++)
	{
		Objeto p;
		objetos.push_back(p);
	}

	objetos[0].id = glGenLists(total_objetos);
	desenhaTerreno(objetos[0].id);

	for (int i = 1; i < total_objetos; i++)
	{
		objetos[i].id = objetos[0].id + i;
		float x = aleatorio(-100, 100);
		float y = aleatorio(8, 20);
		float z = aleatorio(-450, -20);
		objetos[i].pos = vec3(x, y, z);

		float k = (float)rand() / RAND_MAX;
		if (k <= 0.5)
		{
			color* cor;
			if (k <= 0.15)
				cor = &verde;
			else
				cor = &laranja;
			desenhaEsfera(objetos[i].id, *cor, 5.0, 20.0, 20.0);
		}
		else
		{
			desenhaCubo(objetos[i].id, 5.0);
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
	GLFWwindow* window = glfwCreateWindow(LARGURA, ALTURA, "Desenha Esfera", NULL, NULL);

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

	glDeleteLists(objetos[0].id, total_objetos);
	glfwTerminate();
	return 0;
}