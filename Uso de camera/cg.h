#pragma once
#include<cmath>
struct vec3 {
	float x, y, z;
	vec3() :x(0.0), y(0.0), z(0.0) {}
	vec3(float x_, float y_, float z_) :x(x_), y(y_), z(z_) {}
    vec3 operator+(const vec3& v)const { return vec3(x + v.x, y + v.y, z + v.z);}
	vec3 operator*(float k){return vec3(x*k, y*k, z*k);}
	float mag(){return sqrt(x*x+y*y+z*z);}
	void normalize(){
		float m = mag();
		x=x/m;
		y=y/m;
		z=z/m;
	}
	vec3 produtoVetorial(vec3 v){
		//a2b3 − a3b2, a3b1 − a1b3, a1b2 − a2b1
		float a1,a2,a3,b1,b2,b3;
		b1=v.x;
		b2=v.y;
		b3=v.z;
		a1=x;
		a2=y;
		a3=z;
		return vec3(a2*b3 - a3*b2, a3*b1 - a1*b3, a1*b2 - a2*b1);
	}
};