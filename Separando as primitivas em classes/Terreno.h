#pragma once
#include "Primitiva.h"
#include "Textura.h"

class Terreno:public Primitiva
{
public:
	Terreno();
	~Terreno();
	void CriarTerreno(float SIZE,Textura *tex);
};

