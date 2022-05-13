#pragma once
#include"Primitiva.h"
#include"Textura.h"

class Esfera:public Primitiva
{
public:
	Esfera();
	~Esfera();
	void CriarEsfera(Textura* tex, float raio, unsigned nStacks, unsigned nSectors, vec3 pos);
	void CriarSuperShape(Textura* tex, float raio, unsigned nStacks, unsigned nSectors, vec3 pos);
private:
	float superShape(float ang, float m, float n1, float n2, float n3);
};

