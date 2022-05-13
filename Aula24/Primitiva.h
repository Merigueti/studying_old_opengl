#pragma once
#include<GL/gl.h>
#include"Vetor.h"
#include"Textura.h"
#include<vector>

class Primitiva
{

public:
	vec3 m_pos;
	float m_angX, m_angY, m_angZ;
	float m_scale;

protected:
	unsigned int m_id;
	
public:
	Primitiva();
	~Primitiva();
	void Display();
	
};


class Terreno :public Primitiva
{
public:
	Terreno();
	void Create(float SIZE);
};

class Cubo :public Primitiva
{
public:
	Cubo();
	~Cubo() {}
	void Create(
		Textura * textura, 
		float SIZE, 
		vec3 pos=vec3(0.f,2.f,0.f));

private:
	void Rect(vec3 p1, vec3 p2, vec3 p3, vec3 p4);
};

class Esfera :public Primitiva
{
public:
	Esfera();
	~Esfera() {}
	void Create(
		Textura* tex,				 // Textura da Esfera
		float raio,					 // Raio
		unsigned nStacks,			 // N�mero de Stacks
		unsigned nSectors,			 // N�mero de Setores
		vec3 pos = vec3(0.f, 2.f, 0.f)); // Posi��o
};

class Supershape :public Primitiva
{
public:

	Supershape();
	~Supershape(){}
	void Create(
		Textura* tex, 
		float raio, 
		unsigned nStacks, 
		unsigned nSectors,
		vec3 pos = vec3(0.f, 2.f, 0.f));
private:
	float superShape(float ang, float m, float n1, float n2, float n3);
};
