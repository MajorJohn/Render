#ifndef _VIEWPLANE_H_
#define _VIEWPLANE_H_

#include "vec3.h"

class ViewPlane
{
	private:
		point3 lower_left_corner;
		vec3 normal;
		vec3 horizontal;
		vec3 vertical;

	public:
		ViewPlane(point3 llc_,vec3 v_, vec3 h_, vec3 n_)
		: lower_left_corner(llc_), vertical(v_), horizontal(h_),
		normal(n_) {}

		point3 getLlc() {return lower_left_corner;};
		vec3 getNormal() {return normal;};
		vec3 getHorizontal() {return horizontal;};
		vec3 getVertical() {return vertical;};

};

#endif