#ifndef _MESH_H_
#define _MESH_H_

#include "material.h"
#include "triangle.h"
#include "vec3.h"

#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;

class Mesh: public Object
{
	
	private:
		vector<std::shared_ptr<Triangle>> trinagleMesh;
		vector<point3> vertices;
		vector<point3> verticesNormal;		
		std::shared_ptr<Material> material;

		bool culling = true;
		Transform trans;
		point3 center;

		string pObj;

		void readTxt();
		void transline(string line);
		void transToNum(string line, vec3::value_type & num, int lhs = 0, int rhs = 0);
		void printMesh();
	public:

		Mesh(string meshtxt, std::shared_ptr<Material> m_ = std::make_shared<Lambertian>(color (0.3,0.3,0.3)));

		bool hit(const Ray &ray, float t_min, float t_max, HitRecord &hr) const;
		
		void transform(double rotate[3], float scale = 1, point3 translation = point3());
		void endTransform();
		void setReferP(point3 p_);

		void setTexture(std::shared_ptr<Texture> t_);
};


#endif