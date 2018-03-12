#ifndef _RENDER_H_
#define _RENDER_H_

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <cstdlib>
#include <limits>
#include <random>
#include <math.h>

#include "ray.h"
#include "sphere.h"
#include "scene.h"
#include "image.h"
#include "camera.h"

using namespace std;

class Render
{
	private:
		Scene* scene;
		Image* image;
		Camera* camera;

		float max_depth;
		float min_depth;

		// 0 = real Color 
		// debug types
		// 1 = normal color // 2 = depth color
		int imageType = 1; 
		int samples = 1;

		bool gamma = false;

		//TOON SHADER
		float border = 0.2;
		vector<float> angles;
		vector<float> intensities;



		// >>>>>>  FUNCTIONS  <<<<<<
		color findColor(Ray & r_, int times);
		color blinnPhong(Ray & r_);
		color normalColor(Ray & r_);
		color depthColor(Ray & r_);
		color toonShader(Ray & r_);


	public:
		Render(){}
		~Render()
		{
			delete scene;
		}

		void setScene(Scene* s_) {scene = s_;};
		void setImage(Image* i_) {image = i_;};
		void setCamera(Camera* c_) {camera = c_;};
		void setImageType(int it_) {imageType = it_;};
		void setMaxDepth (float md_) {max_depth = md_;};
		void setMinDepth (float md_) {min_depth = md_;};
		void setAntiA(int s_) {samples = s_;};
		void setGamma() {gamma = true;};

		//TOON SHADER SETS
		void setBorder(float b_) {border = b_;};
		void setGradient(float a_, float i_) {angles.push_back(a_); intensities.push_back(i_);}

		void setImageName(string s_) {image->setName(s_);};

		void setRender(Scene* s_, Image* i_, Camera* c_) 
		{scene = s_; image = i_; camera = c_;};
		void start(float col, float row, int index);
		void write_file() {image->write_file();};

		int getWidth() {return image->getWidth();};
		int getHeight() {return image->getHeight();};
		string getImageName() {return image->getName();};


};

#endif 