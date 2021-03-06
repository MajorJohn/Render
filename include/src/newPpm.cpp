#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <sys/time.h>

#include "../include/vec3.h"
#include "../include/ray.h"
#include "../include/texture.h"
#include "../include/sphere.h"
#include "../include/triangle.h"
#include "../include/scene.h"
#include "../include/camera.h"
#include "../include/image.h"
#include "../include/render.h"
#include "../include/material.h"
#include "../include/animator.h"
#include "../include/light.h"
#include "../include/surface.h"
#include "../include/mesh.h"

using namespace std;

void init(Render* render)
{

//screen resolution
// t -> amount of pixels
// h:v -> resolution proportion
//================================
	int t = 150;
	int h = 6;
	int v = 3;
//================================


	Scene* scene = new Scene();
    Image* image = new Image();
    Camera* camera = new Camera();

//>>>>> EDITABLES <<<<<

// 0 = real Color 
// debug types
// 1 = normal color // 2 = depth color // 3 = Blinn Phong
// 4 = toon shader  //
	int imageType = 3;

std::shared_ptr<Triangle> t1;
std::shared_ptr<Triangle> t2;
std::shared_ptr<Triangle> t3;
std::shared_ptr<Triangle> t4;
std::shared_ptr<Triangle> floor1;
std::shared_ptr<Triangle> floor2;

std:: shared_ptr<Sphere> s1;
std:: shared_ptr<Sphere> s2;
std:: shared_ptr<Sphere> s3;
std:: shared_ptr<Sphere> s4;
std:: shared_ptr<Sphere> s5;

std::shared_ptr<Surface> floor;

std::shared_ptr<Texture> mate;
std::shared_ptr<Texture> mate2;

std::shared_ptr<Texture> green;
std::shared_ptr<Texture> blue;
std::shared_ptr<Texture> red;
std::shared_ptr<Texture> brown;
std::shared_ptr<Texture> orange;
std::shared_ptr<Texture> yellow;
std::shared_ptr<Texture> white;
std::shared_ptr<Texture> black;

std::shared_ptr<Mesh> cube;

red = std::make_shared<Constant_texture>(color (1,0.0,0.05));
green = std::make_shared<Constant_texture>(color (0.05,0.5,0.0));
blue = std::make_shared<Constant_texture>(color (0.0,0.3,0.8));
brown = std::make_shared<Constant_texture>(color (0.43,0.28,0.16));
orange = std::make_shared<Constant_texture>(color (0.8,0.2,0.0));
yellow = std::make_shared<Constant_texture>(color (1,0.75,0.0));
white = std::make_shared<Constant_texture>(color (1,1,1));
black = std::make_shared<Constant_texture>(color (0.0,0.0,0.0));

cube = std::make_shared<Mesh>("cube.obj");

s1 = std::make_shared<Sphere>(point3( 0.5, 0.5, 1.5 ), 0.3, std::make_shared<Lambertian>(color (1,0.4,0)));
s2 = std::make_shared<Sphere>(point3( 0.8, 0.4, -1 ), 0.3, std::make_shared<Metal>(color (1,0.4,0)));
s3 = std::make_shared<Sphere>(point3( 0, 0.4, -1 ), 0.3, std::make_shared<Lambertian>(color (1,0.4,0)));
s4 = std::make_shared<Sphere>(point3( -0.8, 0.4, -1 ), 0.3, std::make_shared<Dielectric>(1.5));
s5 = std::make_shared<Sphere>(point3( -1.6, 0.4, -1 ), 0.3, std::make_shared<Lambertian>(color (1,0.4,0)));


mate = std::make_shared<Checker_texture>(green, yellow);
mate2 = std::make_shared<Checker_texture>(orange, blue);

point3 p0(0,0,1);
point3 p1(1,0,1);
point3 p2(1,1,1);
point3 p3(0,1,1);

floor = std::make_shared<Surface> ();

floor1 = std::make_shared<Triangle> (point3( 10, 0.1, 10 ), point3( -10, 0.1, -10 ), point3( -10, 0.1, 10 ), std::make_shared<Lambertian>(color (0.52,0.34,0.07))); 
floor2 = std::make_shared<Triangle> (point3( 10, 0.1, 10 ), point3( 10, 0.1, -10 ), point3( -10, 0.1, -10 ), std::make_shared<Lambertian>(color (0.52,0.34,0.07))); 

t1 = std::make_shared<Triangle> (p0, p1, p2, std::make_shared<Lambertian>(color (1,0,0)));
t2 = std::make_shared<Triangle> (p0, p2, p3, std::make_shared<Lambertian>(color (0,1,0))); 
t3 = std::make_shared<Triangle> (p0, p1, p2, std::make_shared<Lambertian>(color (0,0,1))); 
t4 = std::make_shared<Triangle> (p0, p1, p2, std::make_shared<Lambertian>(color (1,1,0))); 

double rot[3];
rot[0] = 0.0;
rot[1] = 0.0;
rot[2] = 0.0;

floor->transform(rot, 1, point3(0,1,0));
floor->endTransform();
floor->setTexture(mate);

cube->setTexture(blue);

s1->setTexture(orange);
s2->setTexture(red);
s3->setTexture(mate2);
s4->setTexture(white);
s5->setTexture(blue);

floor1->setTexture(mate);
floor2->setTexture(mate);

t1->setTexture(blue);
t2->setTexture(blue);

/*
t1->setTexture(mate);
rot[1] = 90;
t2->setReferP(p0);
t2->transform(rot);
t2->endTransform();
t2->setTexture(mate);
rot[1] = 180.0;
t3->setReferP(p0);
t3->transform(rot);
t3->endTransform();
t3->setTexture(mate);
rot[1] = 270.0;
t4->setReferP(p0);
t4->transform(rot);
t4->endTransform();
t4->setTexture(mate);
*/

//ADD OBJECTS
//====================================================================================================================================
    //scene->addObject(std::make_shared<Sphere>(point3( 0, 0, -1 ), 0.5, std::make_shared<Lambertian>(color (1,0.4,0))));
    //scene->addObject(std::make_shared<Sphere>(point3( 0.5, 0, -1.4 ), 0.5, std::make_shared<Lambertian>(color (1,0,0.6))));
    //scene->addObject(std::make_shared<Sphere>(point3( -0.3, 0, -0.6 ), 0.4, std::make_shared<Lambertian>(color (0.4,0.2,0.8))));
    //scene->addObject(std::make_shared<Sphere>(point3( -1, 0, -1 ), 0.5, std::make_shared<Lambertian>(color (1,0.4,0))));
    //scene->addObject(std::make_shared<Sphere>(point3( 2, 0, -1 ), 0.5, std::make_shared<Lambertian>(color (1,0,0.6))));
    //scene->addObject(std::make_shared<Sphere>(point3( 0.5, 0, -1 ), 0.4, std::make_shared<Lambertian>(color (0.4,0.2,0.8))));
    //scene->addObject(std::make_shared<Sphere>(point3( 0, -100.5, -1 ), 100, std::make_shared<Lambertian>(color (0.6,0.4,0.2))));
    //scene->addObject(t1);
    //scene->addObject(t2);
    //scene->addObject(t3);
    //scene->addObject(t4);
    //scene->addObject(floor1);
    //scene->addObject(floor2);
	//scene->addObject(floor);
	//scene->addObject(s1);
	//scene->addObject(s2);
	//scene->addObject(s3);
	//scene->addObject(s4);
	//scene->addObject(s5);
	scene->addObject(cube);
	//scene->addObject(std::make_shared<Sphere>(point3( 0.2, 0, -0.9 ), 0.1, std::make_shared<Lambertian>(color (1,0.5,0.6))));
    //scene->addObject(std::make_shared<Sphere>(point3( 0, 1, -1 ), 0.2, std::make_shared<Lambertian>(color (1,0.4,0))));
    //scene->addObject(std::make_shared<Triangle>(point3( 1, 0.5, -1 ), point3( 0.5, 1, -1 ), point3( 0, 0.5, -1 ), std::make_shared<Lambertian>(color (0.6,0.4,0.2))));
//====================================================================================================================================

//ADD LIGHTS
//====================================================================================================================================
    //scene->addLight(std::make_shared<SpotLight>(vec3 ( -1.6, 2, 2), color(1,1,1),vec3 (0.5, 0.5, 0.5)));
    scene->addLight(std::make_shared<SpotLight>(vec3 ( 1.5, 0.5, 1.5), color(1,1,1),vec3 (0.5, 0.5, 0.5)));
    //scene->addLight(std::make_shared<AreaLight>(vec3 ( 1.6, 2, -1), color(1,1,1),vec3 (1.6,1,0)));
    //scene->addLight(std::make_shared<PointLight>(vec3 ( 0, 4, 2 ), color(1,1,1), 0.5));
    //scene->addLight(std::make_shared<GlobalLight>(vec3 (2,1,1), color(1,1,1)));
    //scene->addLight(std::make_shared<GlobalLight>(vec3 (2,1,1), color(0,0,1)));
//====================================================================================================================================


    image->setDimension(h*t, v*t);
    image->startBuffer();

//CAMERA
//================================================================================
    float distance = 10;
    point3 cameraOrigin(3, 6, 10);
    point3 lookAt(0, 0, 0);
    vec3 vUp(0,1,0);
    float blur = 0.0;
    float dFocal = distance;
//--------------------------------------------------------------------------------
    camera->setPespective(blur, dFocal);
    //camera->setOrtogonal();
    camera->setCamera(cameraOrigin, lookAt, vUp);
    camera->setVP(h, v, distance);
//================================================================================


//RENDER
//================================================================================
    int samples = 10;
    float maxDepth = 1000;
    float minDepth = 0.001;
//-------------------------------------------------------------------------------- 
    render->setMaxDepth(maxDepth);
    render->setMinDepth(minDepth);
    render->setAntiA(samples);
    render->setGamma();
//================================================================================

//TOON SHADER
//================================================================================
 	float borderSize = 0.2;
//-------------------------------------------------------------------------------- 
    if (imageType == 4)
    {
    	render->setBorder(borderSize);
    	render->setGradient(0.25, 1.0);
    	render->setGradient(0.1, 0.6);
    	//scene->setAmbientColor(0.9);
    }
//================================================================================

//>>>>>NON EDITABLES<<<<<
    render->setRender(scene, image, camera);
    render->setImageType(imageType);
    scene->endSceane();
}

void printLoading (int row, int nRow)
{
	float v = float(row) / float(nRow);

	v *= 50;

	system("clear"); 
	cout << ">>> Creating Image.ppm\n";
	cout << ">>> Loading [";
	for (int i = 0; i < 50; ++i)
	{
		if ( i < v)
			cout << ">";
		else
			cout << " ";	
	}
	cout << "] " << (int)(v*2) << '%' << endl;
}


int main ()
{
	struct timeval tempo1, tempo2;
	double finalTime;

	gettimeofday(&tempo1, NULL);

	Render* render =  new Render;

	init(render);

	int nCol(render->getWidth());  //x
	int nRow(render->getHeight()); 	//y

	int index = 0;

	Animator animator(360);
	bool anim = false;

	bool debug = false;

	if (anim && !debug)
	{
		animator.start();
	}
	
	else if(!debug)
	{	
		for (auto row = nRow -1; row >= 0; --row)
		{
			for (int col = 0; col < nCol; ++col)
			{
				render->start(col, row, index);
	
				index += 3;
			}
	
			printLoading(nRow - row, nRow);
			
		}
	
		render->write_file();	
	
		printLoading(nRow, nRow);
		cout << ">>> Image.cpp COMPLETE!\n";
	}
	
	gettimeofday(&tempo2, NULL);
	finalTime = double((tempo2.tv_sec * 1000000 + tempo2.tv_usec) - (tempo1.tv_sec * 1000000 + tempo1.tv_usec))/1000000 ;

	cout << ">>> Time spent!: " << finalTime << "s \n";

	delete render;

	return 0;
}

//perguntar se é pra inicializar rgb ou color (um novo vec3)