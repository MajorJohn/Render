#ifndef _SCENE_H_
#define _SCENE_H_

#include "sphere.h"
#include "object.h"

#include <vector>

using namespace std;

typedef float real_type;

class Scene{
	private:
		vector<Object*> spheres;
		vec3 sun;
		color colorSun;
		float ambientColor = 0.03;

	public:
		Scene() {}
		~Scene()
		 {
			for(int i = 0; i < spheres.size(); i++)
			{
				delete spheres[i];
			}
		}

		void addObject(Object* sphere) { spheres.push_back(sphere); };
		bool hit(const Ray &ray, real_type t_min, real_type t_max, HitRecord &ht) const;
		void setSun(vec3 v_, color c_) {sun = v_; colorSun = c_;};
		void setAmbientColor(float c_) {ambientColor = c_/100;};

		float getAmbientColor() {return ambientColor;};
		vec3 getSun() {return sun;};
		color getSunColor() {return colorSun;};

};

#endif