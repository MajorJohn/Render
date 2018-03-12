#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include <iostream>
#include <math.h>
#include <string.h>

#include "vec3.h"

class Transform
{
	private:
		point3 refP;

		float PI = 3.14159265;

		float tMatrix[4][4];

		float mGeneral[4][4];

		bool areadyUsed = false;
		bool finalized = false;

		void prod();
		void toOrigin();
		void printM(float m_[4][4]);
		void copy(float m_[4][4]);

	public:
		Transform();

		void setReferP(point3 r_= point3()) {refP = r_;};

		//Edita a escala do vetor em fução do parametro da função
		// > 1 almenta || < 1 diminui
		void scale(float s_);
	
		//Translaçao
		void translation(point3 p_);

		//calcula a nova posição dos pontos;
		void transform(point3 & p_);

		//rotaciona em graus
		//x graus em função ao eixo x
		//y graus em função ao eixo y
		//z graus em função ao eixo z
		void rotate(double x_, double y_, double z_);

};

#endif