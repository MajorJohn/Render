#ifndef _SURFACE_H_
#define _SURFACE_H_

#include <iostream>

#include "object.h"
#include "material.h"
#include "triangle.h"
#include "transform.h"


class Surface: public Object{

	private:
		std::shared_ptr<Triangle> t1;
		std::shared_ptr<Triangle> t2;

		std::shared_ptr<Material> material;
		bool culling;

		Transform trans;
		point3 center;


	public:

		Surface();
		
		bool hit(const Ray &ray, float t_min, float t_max, HitRecord &hr) const;
		void transform(double rotate[3], float scale = 1, point3 translation = point3());
		void endTransform();

		void setReferP(point3 p_) {t1->setReferP(p_);t2->setReferP(p_);};
};

#endif