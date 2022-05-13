#include<GL/gl.h>
#include<GL/glu.h>
#include<GLFW/glfw3.h>

#include "Textura.h"
#include "Primitiva.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl2.h"


//------------------
// Fun��es 
//------------------
void InitWindow(GLFWwindow* window);
void teclado_callback(GLFWwindow * window, int key, int scancode, int action, int mods);
void Resize(int w, int h);
void Desenha();

//--------------------
// Vari�veis
//--------------------
static float clearColor[4] = { 0.f, 0.15f, 0.35f, 1.f};
Textura CuboTex[4];
Textura EsferaTex[4];
Textura SuperTex[4];

std::vector<Primitiva*> objetos;

//--------------------
// Programa Principal
//--------------------
int main() {

	glfwInit();
	GLFWwindow* window= glfwCreateWindow(800, 600, "OpenGL Legacy - Tutorial ImGUI", NULL, NULL);
	glfwMakeContextCurrent(window);
	InitWindow(window);

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL2_Init();

	while (!glfwWindowShouldClose(window)) {
		// Events
		glfwPollEvents();

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL2_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		{ // Janela 1 
			ImGui::SetNextWindowSize(ImVec2(0, 0));
			ImGui::SetNextWindowPos(ImVec2(50, 10));// window pos
			ImGui::Begin("Tutorial OpenGL Legacy - ImGui");
			ImGui::ColorEdit3("Background Color", clearColor);
			ImGui::Text("Primitivas:");
			static int primitiva = 0;
			ImGui::RadioButton("Cubo", &primitiva, 0); ImGui::SameLine();
			ImGui::RadioButton("Esfera", &primitiva, 1); ImGui::SameLine();
			ImGui::RadioButton("Supershape", &primitiva, 2);
			{// Header

				if (ImGui::CollapsingHeader("Texturas")) {
					ImGui::Text("Texturas para Primitiva");
					unsigned texId = 0;
					ImVec2 size = ImVec2(64, 64);
					for (int i = 0; i < 4; i++) {
						ImVec2 uv0 = ImVec2(0, 1);
						ImVec2 uv1 = ImVec2(1, 0);
						
						// Seleciona Textura
						if (primitiva == 0)
							texId = CuboTex[i].GetId();
						else if (primitiva == 1)
							texId = EsferaTex[i].GetId();
						else if (primitiva == 2)
							texId = SuperTex[i].GetId();

						if (ImGui::ImageButton((void*)texId, size, uv0, uv1)) {
							if (primitiva == 0) {
								Textura* tex = &CuboTex[i];
								Cubo* cubo = new Cubo();
								cubo->Create(tex, 2.f);
								objetos.push_back(cubo);
							}
							else if (primitiva == 1) {
								Textura* tex = &EsferaTex[i];
								Esfera* esfera = new Esfera();
								esfera->Create(tex, 2.f, 30, 30);
								objetos.push_back(esfera);
							}
							else if (primitiva == 2) {
								Textura* tex = &SuperTex[i];
								Supershape* super = new Supershape();
								super->Create(tex, 2.f, 30, 30);
								objetos.push_back(super);
							}
						}
						
						
						ImGui::SameLine();
					}

				}
				
			}
			
			ImGui::End();
		}
		{// Janela 2
			ImGui::SetNextWindowPos(ImVec2(950, 10));
			ImGui::SetNextWindowSize(ImVec2(320, 280));
			ImGui::Begin("Apply Transformations");
			
			unsigned currentObj = objetos.size() - 1;
			Primitiva* obj = objetos[currentObj];

			// Header Translation
			if (ImGui::CollapsingHeader("Translation")) {
				//static float posx = 0.f, posy = 0.f, posz = 0.f;
				ImGui::SliderFloat("X position", &obj->m_pos.x, -35.f, 35.f);
				ImGui::SliderFloat("Y position", &obj->m_pos.y, 1.f, 10.f);
				ImGui::SliderFloat("Z position", &obj->m_pos.z, -50.f, 50.f);
			}

			// Header Rotation
			if (ImGui::CollapsingHeader("Rotation")) {
				//static float angx=0.f, angy=0.f, angz = 0.f;
				ImGui::SliderFloat("X Axis", &obj->m_angX, -180.f, 180.f);
				ImGui::SliderFloat("Y Axis", &obj->m_angY, -180.f, 180.f);
				ImGui::SliderFloat("Z Axis", &obj->m_angZ, -180.f, 180.f);
			}

			// Header Scale
			if (ImGui::CollapsingHeader("Scale")) {
				//static float factor = 1.f;
				ImGui::InputFloat("Scale Factor", &obj->m_scale, 0.5f);
				if (obj->m_scale <= 1.f) obj->m_scale = 1.f;
				if (obj->m_scale >= 5.f) obj->m_scale = 5.f;
			}
			ImGui::End();
		}
		// Resize
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		Resize(width, height);

		// Limpa Tecla
		glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Render
		Desenha();
		ImGui::Render();
		ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
		
		// SwapBuffer
		glfwSwapBuffers(window);
	}
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	for (int i = 0; i < objetos.size(); i++)
		delete objetos[i];
	objetos.clear();
	
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}


//------------------
// Inicializar  
//------------------
void InitWindow(GLFWwindow* window) {
	// Janela
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, teclado_callback);
	
	// Habilitar
	glEnable(GL_DEPTH_TEST);

	// Vari�veis
	glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);

	CuboTex[0].load("images/cubo/mask.png");
	CuboTex[1].load("images/cubo/painted_brick.png");
	CuboTex[2].load("images/cubo/wood.png");
	CuboTex[3].load("images/cubo/metal.png");

	EsferaTex[0].load("images/esfera/earth.jpg");
	EsferaTex[1].load("images/esfera/mars.jpg");
	EsferaTex[2].load("images/esfera/moon.jpg");
	EsferaTex[3].load("images/esfera/sun.jpg");

	SuperTex[0].load("images/supershape/metal.jpg");
	SuperTex[1].load("images/supershape/moon.jpg");
	SuperTex[2].load("images/supershape/rust.jpg");
	SuperTex[3].load("images/supershape/yellow.jpg");

	Terreno* terreno = new Terreno();
	terreno->Create(50.f);
	
	Cubo* cubo = new Cubo();
	cubo->Create(&CuboTex[2], 2.f);

	objetos.push_back(terreno);
	objetos.push_back(cubo);

}

//------------------
// Teclado  
//------------------
void teclado_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}


//--------------------
// Redimensionar Tela 
//--------------------
void Resize(int w, int h)
{
	glViewport(0, 0, w, h);

	float aspect = (float)w / (float)h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, aspect, 0.1, 500.0);
	glMatrixMode(GL_MODELVIEW);
}

//------------------
// Render
//------------------
void Desenha()
{
	
	glLoadIdentity();
	vec3 position(0.f, 5.f, 20.f);
	vec3 direction(0.f, 0.f, -1.f);
	vec3 up(0.f, 1.f, 0.f);
	vec3 look = position + direction;

	gluLookAt(
		position.x, position.y, position.z,
		look.x, look.y, look.z,
		up.x, up.y, up.z);

	for (int i = 0; i < objetos.size(); i++)
		objetos[i]->Display();

}
