#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include <iostream>

#include "object.h"
#include "material.h"

using namespace std;

class Triangle: public Object{
	typedef float real_type;

	private:
		point3 p0;		
		point3 p1;		
		point3 p2;
		vec3 E1;
		vec3 E2;
		vec3 normal;
		std::shared_ptr<Material> material;
		bool culling;

		Transform trans;
		point3 center;


	public:

		Triangle(point3 p0_= point3(), point3 p1_= point3(), point3 p2_= point3(), std::shared_ptr<Material> m_ = nullptr, bool c_ = false) 
			: p0(p0_), p1(p1_), p2(p2_), material(m_), culling(c_) 
			{E1 = p1_ - p0_; E2 = p2_ - p0_; normal = cross(E1, E2);center = (p0_ + p1_ + p2_)/3; trans.setReferP(center);}

		bool hit(const Ray &ray, float t_min, float t_max, HitRecord &hr) const;
		void transform(double rotate[3], float scale = 1, point3 translation = point3());
		void endTransform();

		void setReferP(point3 p_) {trans.setReferP(p_);};
		void setTexture(std::shared_ptr<Texture> t_) {material->setTexture(t_);};

		void printTri() {cout << p0 << p1 << p2 << endl;};
};

#endif