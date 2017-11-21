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

		hr.normal = normal;
	}
	else
	{
		if (det > -EPSILON && det < EPSILON)
			return false;

		float iDet = 1/det;
		u = dot(T,P)*iDet;
		if(u  < 0.0 || u > 1.0)
			return false;
		
		vec3 Q = cross(T, E1);
		v = dot(D,Q)*iDet;

		if(v < 0.0 || v + u > 1.0)
			return false;

		t = dot(E2,Q) * iDet; 
		if(t > t_max || t < t_min)
			return false;
		if(det > 0)
			hr.normal = normal;
		else
			hr.normal = -normal;
	}

	hr.normal.make_unit_vector();
	hr.t = t;
	hr.p = ray.point_at(t);
	hr.material = material;

	return true;
}

void 
Triangle::transform(double rotate[3], float scale, point3 translation)
{
	trans.rotate(rotate[0],rotate[1],rotate[2]);
	
	trans.scale(scale);
	
	trans.translation(translation);
}

void 
Triangle::endTransform()
{
	trans.transform(p0);
	trans.transform(p1);
	trans.transform(p2);

	E1 = p1 - p0;
	E2 = p2 - p0;
	normal = cross(E1, E2);
	center = (p0 + p1 + p2)/3;
}