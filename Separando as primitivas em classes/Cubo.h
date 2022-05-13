#pragma once
#include"Primitiva.h"
#include"Textura.h"

class Cubo:public Primitiva
{
public:
	Cubo();
	~Cubo();
	void CriarCubo(Textura* textura, float SIZE, vec3 pos);
private:
	void rect(vec3 p1, vec3 p2, vec3 p3, vec3 p4);
};

