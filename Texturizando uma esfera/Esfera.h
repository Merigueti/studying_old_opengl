#pragma once
#include "cg.h"
#include "Textura.h"
class Esfera
{
private:
    unsigned int m_id;
    vec3 m_pos;
    float m_ang, m_fps;
    bool m_rodax, m_roday, m_rodaz;

public:
    Esfera(/* args */);
    ~Esfera();
    void criarEsfera(Textura* tex, float raio, unsigned int nStacks,unsigned int nSectors, vec3 pos);
    void Display(float dt);
    void rodarX();
    void rodarY();
    void rodarZ();

private:
    float aleatorio(float a, float b);
};