#include "../include/camera.h"

void
Camera::setVP(float h_,float v_, float d_)
{
	point3 o;
	// origin + d*w (d == 0)
	if(pespective)
		o = origin + d_*-w;
	else
		o = origin;

	//vertical & horizontal
	vec3 hor = u*h_;
	vec3 vert = (-v)*v_;

	//LLC
	point3 llc = o - (hor/2) - (vert/2);

	//normal
	vec3 normal = -w;

	//new viewplane
	vp = std::make_shared<ViewPlane>(llc,vert,hor,normal);
}

Ray
Camera::getRay(float u_, float v_)
{
	if(pespective){
		point3 o = origin + blur*random_in_unit_disc();

		vec3 ray_dir ((vp->getLlc() + u_*vp->getHorizontal() + v_*vp->getVertical()) - o);

		Ray r( o , ray_dir);
		return r;
	}

	else{
		vec3 ray_dir (vp->getNormal());

		point3 o = (vp->getLlc() + u_*vp->getHorizontal() + v_*vp->getVertical());

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
