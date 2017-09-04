#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "vec3.h"

class Camera
{
	private:
		point3 lower_left_corner;
		vec3 horizontal;
		vec3 vertical;
		point3 origin;

	public:

		Camera (point3 llc_ = point3(-2,-1,-1), vec3 h_ = vec3(4,0,0), vec3 v_ = vec3(0,2,0), point3 o_ = point3(0,0,0))
		: lower_left_corner(llc_), horizontal(h_), vertical(v_), origin(o_) {}

		void setLlc(point3 llc_) {lower_left_corner = llc_;};
		void setHorizon (vec3 h_) {horizontal = h_;};
		void setVert (vec3 v_) {vertical = v_;};
		void setOrigin (point3 o_) {origin = o_;};

		point3 getLlc() {return lower_left_corner;};
		vec3 getHorizon() {return horizontal;};
		vec3 getVert() {return vertical;};
		point3 getOrigin() {return origin;};

		void setCamera(point3 llc_, vec3 h_, vec3 v_, point3 o_)
		{lower_left_corner = llc_; horizontal = h_;
		 vertical = v_; origin = o_;};

};

#endif