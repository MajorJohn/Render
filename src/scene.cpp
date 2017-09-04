#include "../include/scene.h"

bool
Scene::hit(const Ray &ray, real_type t_min, real_type t_max, HitRecord &ht) const
{
	bool hitted = false;
	real_type throne = t_max;
	HitRecord testeHt;
	bool canNegative = false;


	for (int i = 0; i < spheres.size(); ++i)
	{
		if(spheres[i]->hit(ray, t_min, t_max, testeHt))
		{
			hitted = true;
			if (testeHt.t < throne)
			{
				throne = testeHt.t;
				ht = testeHt;
			}
		}
	}

	return hitted;
}