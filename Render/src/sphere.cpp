#include "../include/sphere.h"

bool 
Sphere::hit(const Ray &ray, float t_min, float t_max, HitRecord &hr) const
{

	auto d = ray.get_direction();
	auto o = ray.get_origin();
	auto oc = o - center;

	float A = dot(d,d);
	float B = 2*(dot(oc,d));
	float C = dot(oc,oc)-radius*radius;

	float delta = B*B - 4* A * C;

	if (delta >= 0)
	{
		float t =  (-B - sqrt(delta))/(2*A); 

		if (t >= t_min && t <= t_max)
		{
			if(!negative)
			{
				hr.t = t;
				hr.p = ray.point_at(t);
				hr.normal = unit_vector(hr.p - center);
				hr.material = material;
				hr.negative = false;
			}
			else
			{
				hr.t = t;
				hr.p = ray.point_at(t);
				hr.normal = unit_vector(hr.p - center);
				hr.normal *= -1;
				hr.negative = true;
			}
			return true;
		}

		t =  (-B + sqrt(delta))/(2*A); 
		if (t >= t_min && t <= t_max)
		{
			if(!negative)
			{
				hr.t = t;
				hr.p = ray.point_at(t);
				hr.normal = unit_vector(hr.p - center);
				hr.material = material;
				hr.negative = false;
			}
			else
			{
				hr.t = t;
				hr.p = ray.point_at(t);
				hr.normal = unit_vector(hr.p - center);
				hr.normal *= -1;
				hr.negative = true;
			}
			return true;
		}				
	}

	return false;
}