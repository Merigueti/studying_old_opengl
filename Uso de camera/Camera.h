#pragma once

#include "cg.h"

class Camera
{
private:
	vec3 m_pos;
	vec3 m_dir;
	vec3 m_left;
	vec3 m_up;
	vec3 m_veloc;
	float m_scl;
	float m_yaw;
	float m_pi;

public:
	Camera(vec3 pos);
	~Camera();
	void ativar();
	void forward();
	void back();
	void left();
	void right();
	void updateYaw(float dYaw);
	void update();


private:
	float cvtToRad(float ang);


};

