#include "../include/surface.h"

Surface::Surface()
{
	point3 p0, p1, p2, p3;

	std::shared_ptr<Material> m_ = std::make_shared<Lambertian>(color (0.52,0.34,0.07));
	bool c_ = false;

	p0 = point3(-1, 0, -1);
	p1 = point3(1, 0, -1);
	p2 = point3(-1, 0, 1);
	p3 = point3(1,0,1);
	t1 = std::make_shared<Triangle> (p0, p2, p3, m_, c_);
	t2 = std::make_shared<Triangle> (p0, p3, p1, m_, c_);

	setReferP(center);
	culling = false;
	material = m_;
}

bool 
Surface::hit(const Ray &ray, float t_min, float t_max, HitRecord &hr) const
{
	if(t1->hit(ray,t_min,t_max,hr))
		return true;
	if(t2->hit(ray,t_min,t_max,hr))
		return true;

	return false;
}

void 
Surface::transform(double rotate[3], float scale, point3 translation)
{
	t1->transform(rotate, scale, translation);

	t2->transform(rotate, scale, translation);	
}

void 
Surface::endTransform()
{
	t1->endTransform();
	t2->endTransform();
}