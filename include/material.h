#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "vec3.h"

class Material
{
	protected:
		color cor;
		float shininess;

	public:
		Material(color c_, float s_ = 16) :
		cor(c_), shininess(s_) {}

		void setShininess (float s_) {shininess = s_;};

		color getColor() {return cor;};
		float getShininess() {return shininess;};

};

#endif