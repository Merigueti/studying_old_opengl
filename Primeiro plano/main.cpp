#include <iostream>
#include <GLFW/glfw3.h>

void resize(int width,int height){
    glViewport(0,0,width,height);
    float aspect = (float)width/(float)height;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(width>height)
        glOrtho(-10*aspect,10*aspect,-10,10,1,-1);
    else
        glOrtho(-10,10,-10/aspect,10/aspect,1,-1);
}

void draw(){
    glColor3f(0.25,0.0,0.0);
    glBegin(GL_QUADS);
        glVertex3f(-2.5,-2.5,0);
        glVertex3f(-2.5,2.5,0);
        glVertex3f(2.5,2.5,0);
        glVertex3f(2.5,-2.5,0);
        glEnd();
}

int main(void)
{   
    int width = 800;
    int height = 600;
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(width, height, "DrawSquare", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    std::cout<<"Go!: "<<GLFW_TRUE;

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    //--Start
    glClearColor(0.0,0.15,0.25,1.0);//background color



    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Poll for and process events */
        glfwPollEvents();
        if((glfwGetKey(window,GLFW_KEY_ESCAPE)==GLFW_PRESS)){
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        glfwGetFramebufferSize(window, &width,&height);
        resize(width,height);
        draw();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);


    }

    glfwTerminate();
    return 0;
}