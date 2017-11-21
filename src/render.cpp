#include "../include/render.h"

color 
Render::findColor(Ray & r_, int times)
{
	HitRecord rec;

	if (times == 10)
		return color (0,0,0);

	if(scene->hit(r_, min_depth, max_depth, rec))
	{
		Ray scattered;
		vec3 attenuation;
		if (rec.material->scatter(r_, rec, attenuation, scattered))
			return attenuation*findColor(scattered, times+1);
	}
	else
	{		
		if(times == 0)
		{
			vec3 unit_direction = unit_vector(r_.get_direction());
			float t = 0.5*(unit_direction.y() + 1.0);
			return (1.0 - t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
		}
		else
		{
			color cLight;

			for (int i = 0; i < scene->GetNofLights(); ++i)
			{
				cLight += scene->getSunColor(i);
			}
			normalizeColor(cLight);
			return cLight;
		}
	}
}


color 
Render::blinnPhong(Ray & r_)
{
	color ka, kd, ks;
	color c_, tmp;

	auto x = (r_.get_direction() - r_.get_origin());

	HitRecord t;

	if(scene->hit(r_, min_depth, max_depth, t))
	{
		
//===============================================================================================================
//AMBIENT COLOR
//===============================================================================================================
		ka = t.material->getColor()*scene->getAmbientColor();
//===============================================================================================================

//===============================================================================================================
//ALl LIGHTS
//===============================================================================================================
		for (int nLight = 0; nLight < scene->GetNofLights(); ++nLight)
		{			
//===============================================================================================================
//DIFFUSE COLOR
//===============================================================================================================
			vec3 uSun = scene->getSun(nLight, t.p);
			uSun.make_unit_vector();

			float angle = dot(uSun, t.normal);

			if (angle < 0) angle = 0;

			kd = t.material->getColor()*(angle*scene->getSunColor(nLight, t.p));
//===============================================================================================================

//===============================================================================================================
//SPECULAR HIGHLIGHT
//===============================================================================================================
			
			//vec3 reflected = reflect(uSun, t.normal);
			vec3 viewDir = r_.get_direction();
			
			auto h = (-viewDir + uSun);
			h.make_unit_vector();
			float specAngle = dot (t.normal, h);
			//float specAngle = dot(reflected, viewDir);

			
			if(specAngle < 0) specAngle = 0;
			//cout << specAngle << endl; 

			float specular = pow(specAngle, t.material->getShininess());

			//specular *= 0.8;

			ks = specular*t.material->getSpecularColor()*scene->getSunIntensity(nLight);
			
//===============================================================================================================
			
//===============================================================================================================
//SHADOW
//===============================================================================================================
			HitRecord trash;

			c_ += ka;
			//if doenst hit anything in the direction of the light
			if(!scene->hit(Ray(t.p, uSun), min_depth, max_depth, trash))
			{
				if(!scene->shadow(t, nLight))
					c_ += kd + ks;
			}
			//if it isnt a global light
			//and one object is doing a wrong shadow (ex. case: o1 <- l -> o2, shadow form o1 to o2 and vice-versa)
			else if(!scene->shadow(t, distance(t.p, trash.p), nLight))
				c_ += kd + ks;
//===============================================================================================================
		}

		normalizeColor(c_);

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

	return c_;
}

color 
Render::toonShader(Ray & r_)
{
	color ka, kd, ks;
	color c_, tmp;

	auto x = (r_.get_direction() - r_.get_origin());

	HitRecord t;

	if(scene->hit(r_, min_depth, max_depth, t))
	{

		if(dot(-r_.get_direction(), t.normal) < border)
			return color(0,0,0);		
		//===============================================================================================================
		//AMBIENT COLOR
		//===============================================================================================================
		
		ka = t.material->getColor()*scene->getAmbientColor();
		
		//===============================================================================================================
		//ALl LIGHTS
		//===============================================================================================================
		
		for (int nLight = 0; nLight < scene->GetNofLights(); ++nLight)
		{			
			//===============================================================================================================
			//DIFFUSE COLOR
			//===============================================================================================================
			vec3 uSun = scene->getSun(nLight, t.p);
			uSun.make_unit_vector();

			float angle = dot(uSun, t.normal);


			if (angle < 0) angle = 0;

			kd = t.material->getColor()*(scene->getSunColor(nLight, t.p));
			for (int i = 0; i < angles.size(); ++i)
			{
				if(angle < angles[i])
					kd *= intensities[i];
			}

			//===============================================================================================================
			//SPECULAR HIGHLIGHT
			//===============================================================================================================
			
			//vec3 reflected = reflect(uSun, t.normal);
			vec3 viewDir = r_.get_direction();
			
			auto h = (-r_.get_direction() + uSun);
			h.make_unit_vector();
			float specAngle = dot (t.normal, h);
			//float specAngle = dot(reflected, viewDir);

			
			if(specAngle < 0) specAngle = 0;
			//cout << specAngle << endl; 

			float specular = pow(specAngle, t.material->getShininess());

			//specular *= 0.8;

			if(specular >= 0.5)
				ks = t.material->getColor()*1.1;
			

			//todo -> uma esfera causa sombra na outra, mesmo que esteja entre a luz
			// o1 <- l -> o2 (o1 causa sombra em o2 e vice e versa)
			//===============================================================================================================
			//SHADOW
			//===============================================================================================================
			HitRecord trash;

			//c_ += ka;
			if(scene->hit(Ray(t.p, uSun), min_depth, max_depth, trash)) 
					kd = t.material->getColor()*(scene->getSunColor(nLight, t.p))*intensities[intensities.size()-1];
			c_ += kd + ks;

			
			//===============================================================================================================
		}

		//if(dot(-r_.get_direction(), t.normal) < 0.2)
		//	c_ *= 0;

		normalizeColor(c_);

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

	return c_;

	return color(0,0,0);
}

color 
Render::normalColor(Ray & r_)
{
	color c_;

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

	return c_;
}

color 
Render::depthColor(Ray & r_)
{
	color c_;

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

	return c_;
}

void
Render::start(float col, float row, int index)
{
	color c;
	color tmp;

	std::random_device rd;
   	std::mt19937 gen(rd());
	
	for (int i = 0; i < samples; ++i)
	{		
		auto u = (float(col) + std::generate_canonical<float,10>(gen)) / (image->getWidth()-1);
        auto v = (float(row) + std::generate_canonical<float,10>(gen)) / (image->getHeight()-1);

		Ray r = camera->getRay(u, v);

		switch(imageType)
		{
			//real color
			case 0:
				c += findColor(r, 0);
				break;
			//normal color
			case 1:
				c += normalColor(r);
				break;
			//depth color
			case 2:
				c += depthColor(r);
				break;
			case 3:
				c += blinnPhong(r);
				break;
			case 4:
				c += toonShader(r);
				break;
		}
		
		c += tmp;

	}

	c /= samples;
	
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