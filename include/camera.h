#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <memory>

#include "vec3.h"
#include "viewplane.h"
#include "ray.h"

class Camera
{
	private:

		point3 origin;

		point3 u = point3(1,0,0);
		point3 v = point3(0,1,0);
		point3 w = point3(0,0,1);

		bool pespective = true;

		float blur;
		float focalD;

		std::shared_ptr<ViewPlane> vp;

	public:

		Camera (point3 o_ = point3(0,0,0))
		: origin(o_) {}

		Ray getRay(float u_, float v_);

		//dimensions ex.: 16:9 // disntace from the camera
		void setVP(float h_,float v_, float d_);

		void setPespective(float b_ = 0, float d_ = 1.0) {pespective = true; blur = b_; focalD = d_;};
		void setOrtogonal() {pespective = false;};

		void setCamera(point3 o_, point3 lookAt, vec3 vUp);

};

#endif