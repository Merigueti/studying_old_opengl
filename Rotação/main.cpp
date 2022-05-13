#include <iostream>
#include <GLFW/glfw3.h>
#include "primitivas.h"

float angulo = 0;
unsigned int idEsfera;


void resize(int width,int height){
    glViewport(0,0,width,height);

    float aspect = (float)width/(float)height;

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();
    gluPerspective(45.5,aspect,0.1,500);

    glMatrixMode(GL_MODELVIEW);

}

void draw(){

	glLoadIdentity();
	

	glTranslatef(0.0, 0.0, -50.0);
	glRotatef(angulo, 1.0, 1.0, 0.0);
	
	glCallList(idEsfera);
	
	angulo += 0.5;
}

void init(){
    //--Start
    glClearColor(0.0,0.15,0.25,1.0);//background color
    glEnable(GL_DEPTH_TEST);

    idEsfera = glGenLists(1);
    drawSpheres(idEsfera,10,16,16);

}

int main(void)
{   
    int width = 800;
    int height = 600;
    /* Initialize the library */
	glfwInit();

	/* Create a windowed mode window and its OpenGL context */
	GLFWwindow* window = glfwCreateWindow(width, height, "Merigueti Draw Forms", NULL, NULL);

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

    init();



    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Poll for and process events */
        glfwPollEvents();
        if((glfwGetKey(window,GLFW_KEY_ESCAPE)==GLFW_PRESS)){
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        glfwGetFramebufferSize(window, &width,&height);
        resize(width,height);
        draw();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);


    }

    glfwTerminate();
    return 0;
}