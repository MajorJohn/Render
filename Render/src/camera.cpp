#include "../include/camera.h"

void
Camera::setVP(float h_,float v_, float d_)
{
	point3 o;
	vec3 hor;
	vec3 vert;
	point3 llc;
	vec3 normal;

	// origin + d*w (d == 0)
	if(pespective){
		float proporcion;

		o = origin + focalD*-w;

		proporcion = focalD/d_;
		//vertical & horizontal
		hor = u*h_;
		vert = (-v)*v_;

		hor *= proporcion;
		vert *= proporcion;

		//LLC
		llc = o - (hor/2) - (vert/2);

		//normal
		normal = -w;
	}
	else{
		o = origin;

		//vertical & horizontal
		hor = u*h_;
		vert = (-v)*v_;

		//LLC
		llc = o - (hor/2) - (vert/2);

		//normal
		normal = -w;
	}

	//new viewplane
	vp = std::make_shared<ViewPlane>(llc,vert,hor,normal);
}

Ray
Camera::getRay(float u_, float v_)
{
	if(pespective){

		vec3 rand = blur*random_in_unit_disc();
		point3 o = origin + u*rand + v*rand;

		vec3 ray_dir ((vp->getLlc() + u_*vp->getHorizontal() + v_*vp->getVertical()) - o);

		ray_dir.make_unit_vector();

		Ray r( o , ray_dir);
		return r;
	}

	else{
		vec3 ray_dir (vp->getNormal());

		point3 o = (vp->getLlc() + u_*vp->getHorizontal() + v_*vp->getVertical());

		ray_dir.make_unit_vector();
		
		Ray r( o , ray_dir);
		return r;
	}

}

void
Camera::setCamera(point3 o_, point3 lookAt, vec3 vUp)
{
	origin = o_;

	w = o_ - lookAt;
	w.make_unit_vector();

	u = cross(vUp, w);
	u.make_unit_vector();

	v = cross(u,w);
	v.make_unit_vector();
}
