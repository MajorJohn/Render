#include "../include/render.h"


void 
Render::findColor(Ray & r_, color & c_)
{
	auto x = (r_.get_direction() - r_.get_origin());

	HitRecord t;

	c_ = color(0,0,0);

	if(scene->hit(r_, min_depth, max_depth, t))
	{
		//AMBIENT COLOR
		//===============================================================================================================
		
		c_ += t.material->getColor()*color(scene->getAmbientColor(),scene->getAmbientColor(),scene->getAmbientColor());
		
		//===============================================================================================================

		//DIFFUSE COLOR
		//===============================================================================================================
		
		vec3 uSun = scene->getSun();
		uSun.make_unit_vector();

		float angle = dot(uSun, t.normal);

		if (angle < 0) angle = 0;

		c_ += t.material->getColor()*(angle*scene->getSunColor());

		//===============================================================================================================


		//SPECULAR HIGHLIGHT
		//===============================================================================================================
		
		vec3 reflected = uSun - (2*angle*t.normal);
		vec3 viewDir = t.p - r_.get_origin();

		float specAngle = dot(reflected, viewDir);
		if(specAngle < 0) specAngle = 0;

		float specular = pow(specAngle, t.material->getShininess());

		specular *= 0.8;

		c_ += specular*vec3(1,1,1);
		
		//===============================================================================================================


		if(c_.x() > 1) c_[color::R] = 1;
		if(c_.y() > 1) c_[color::G] = 1;
		if(c_.z() > 1) c_[color::B] = 1;
	}


	else
	{
		x.make_unit_vector();

		x = (x + vec3(1,1,1))/2;
		auto y = x.y();

		color branco(1,1,1);
		color azul(0.5,0.7,1.0);


		c_ = azul * (y) + branco*(1-y);
	}
}

void 
Render::normalColor(Ray & r_, color & c_)
{
	auto x = (r_.get_direction() - r_.get_origin());

	HitRecord t;

	if(scene->hit(r_, min_depth, max_depth, t))
	{
		c_ =  ((t.normal + vec3(1,1,1))*0.5);
	}

	else
	{
		x.make_unit_vector();

		x = (x + vec3(1,1,1))/2;
		auto y = x.y();

		color branco(1,1,1);
		color azul(0.5,0.7,1.0);


		c_ = azul * (y) + branco*(1-y);
	}
}

void 
Render::depthColor(Ray & r_, color & c_)
{
	color depth_background (1,1,1);
	color depth_foreground (0,0,0);
	HitRecord t;

	if(scene->hit(r_, min_depth, max_depth, t))
	{
		vec3 v = t.p - r_.get_origin();
		float length = v.length();


		if(length > max_depth)
			c_ = depth_background;
		else
		{
			length = length / (max_depth - min_depth);
			c_ = length*depth_background + (1 - length)*depth_foreground;
		}
	}
	else
		c_ = depth_background;
}

void
Render::start(float col, float row, int index)
{
	color c;

	bool antiAliasing = true;

	std::random_device rd;
   	std::mt19937 gen(rd());
	color finalColor(0,0,0);
	for (int i = 0; i < samples; ++i)
	{
		auto u = (float(col) + std::generate_canonical<float,10>(gen)) / (image->getWidth()-1);
        auto v = (float(row) + std::generate_canonical<float,10>(gen)) / (image->getHeight()-1);

		vec3 ray_dir ((camera->getLlc() + u*camera->getHorizon() + v*camera->getVert())
					  - camera->getOrigin());

		Ray r( camera->getOrigin() , ray_dir);

		switch(imageType)
		{
			//real color
			case 0:
				findColor(r, c);
				break;
			//normal color
			case 1:
				normalColor(r, c);
				break;
			//depth color
			case 2:
				depthColor(r, c);
				break; 
		}

		finalColor += c;
	}

	c = finalColor/samples;



	
	
	//Gamma correction
	if(gamma)
	{
		c[color::R] = sqrt(c[color::R]);
		c[color::G] = sqrt(c[color::G]);
		c[color::B] = sqrt(c[color::B]);
	}

	int ir = int(255.00f * c[color::R]);
	int ig = int(255.00f * c[color::G]);
	int ib = int(255.00f * c[color::B]);

	image->getBuffer()[index] = char(ir);
	index++;
	image->getBuffer()[index] = char(ig);
	index++;
	image->getBuffer()[index] = char(ib);
	index++;
}