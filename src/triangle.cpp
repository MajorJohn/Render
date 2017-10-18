#include "../include/triangle.h"

bool 
Triangle::hit(const Ray &ray, float t_min, float t_max, HitRecord &hr) const
{

	vec3 O = ray.get_origin();	
	vec3 D = ray.get_direction();	

	float EPSILON = 0.000001;

	vec3 P = cross(D, E2);

	float det = dot(E1,P);

	float t, u, v;


	vec3 T = O - p0;
	
	if(culling)
	{
		if(det < EPSILON)
			return false;

		u = dot(T,P);
		if (u < 0.0 || u > det)
			return false;
		
		vec3 Q = cross(T, E1);
		v = dot(D,Q);	
		if (v < 0.0 || u + v > det)
			return false;
		
		float iDet = 1/det;
		t = dot(E2,Q)*iDet;

		if(t > t_max || t < t_min)
			return false;
		
		u *= iDet;
		v *= iDet;
	}
	else
	{
		if (det > -EPSILON && det < EPSILON)
			return false;

		float iDet = 1/det;
		u = dot(T,P)*iDet;
		if(u  < 0.0 || u > 1)
			return false;
		
		vec3 Q = cross(T, E1);
		v = dot(D,Q)*iDet;

		if(v < 0.0 || v + u > 1.0)
			return false;

		t = dot(E2,Q) * iDet; 
		if(t > t_max || t < t_min)
			return false;
	}

	hr.t = t;
	hr.p = ray.point_at(t);
	hr.normal = normal;
	hr.material = material;

	return true;
}