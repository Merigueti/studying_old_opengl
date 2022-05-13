#pragma once
#include"cg.h"
#include<GL/gl.h>

class Primitiva
{
protected:
	unsigned int m_id;
	vec3 m_pos;
	float m_ang, m_fps;
	bool m_rodax, m_roday, m_rodaz;

public:
	Primitiva();
	~Primitiva();
	void Display(float dt);
	void RodaX();
	void RodaY();
	void RodaZ();
private:
	float aleatorio(float a, float b);
};

