#ifndef _SCENE_H_
#define _SCENE_H_

#include "sphere.h"
#include "object.h"
#include "light.h"

#include <vector>
#include <algorithm>

using namespace std;

typedef float real_type;

class Scene{
	private:		
		vector<std::shared_ptr<Object>> objects;
		vector<std::shared_ptr<Light>> tmpLights;
		vector<std::shared_ptr<Light>> lights;

		float ambientColor = 0.03;

	public:
		Scene() {}

		void addObject(std::shared_ptr<Object> object) { objects.push_back(object); };
		void addLight(std::shared_ptr<Light> light) { tmpLights.push_back(light); };

		bool hit(const Ray &ray, real_type t_min, real_type t_max, HitRecord &ht) const;
		void setAmbientColor(float c_) {ambientColor = c_/100;};

		int GetNofLights() {return lights.size();};
		vec3 getSun(int l_, point3 p_) {return lights[l_]->getNormal(p_);};
		color getSunColor(int l_, point3 p_ = point3()) {return lights[l_]->getColor(p_);};
		float getSunIntensity(int l_) {return lights[l_]->getIntensity();}
		bool shadow(HitRecord t_, float dist, int l_) {return lights[l_]->shadow(t_, dist);};
		bool shadow(HitRecord t_, int l_) {return lights[l_]->shadow(t_);};

		float getAmbientColor() {return ambientColor;};

		void endSceane()
		{
			for (int i = 0; i < tmpLights.size(); ++i)
			{
				if(tmpLights[i]->getLights(lights))
				{
					lights.push_back(tmpLights[i]);
				}
			}
		}

};

#endif