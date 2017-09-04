#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <sys/time.h>

#include "../include/vec3.h"
#include "../include/ray.h"
#include "../include/sphere.h"
#include "../include/scene.h"
#include "../include/camera.h"
#include "../include/image.h"
#include "../include/render.h"
#include "../include/material.h"
#include "../include/animator.h"

using namespace std;

void init(Render* render)
{
	Scene* scene = new Scene();
    Image* image = new Image();
    Camera* camera = new Camera();

    //>>>>> EDITABLES <<<<<

    // 0 = real Color 
	// debug types
	// 1 = normal color // 2 = depth color
	int imageType = 0;


    //scene->addObject(new Sphere(point3( 0, 0, -1 ), 0.5, new Material(color (1,0.4,0))));
    //scene->addObject(new Sphere(point3( 0, -100.5, -1 ), 100, new Material(color (0.6,0.4,0.2), 8)));
    scene->addObject(new Sphere(point3( 0.5, 0, -1.4 ), 0.5, new Material(color (1,0,0.6))));
    //scene->addObject(new Sphere(point3( 0.2, 0, -0.9 ), 0.1, new Material(color (1,0.5,0.6)), true));
    //scene->addObject(new Sphere(point3( -0.3, 0, -0.6 ), 0.4, new Material(color (0.4,0.2,0.8))));

    scene->setSun(vec3 (-1,1,1), color(1,1,1));

    image->setDimension(1200, 600);
    image->startBuffer();

    camera->setCamera(point3(-2, -1, -1), vec3(4, 0, 0), vec3(0, 2, 0), point3(0, 0, 0));

    render->setMaxDepth(1.5);
    render->setMinDepth(0.0);
    render->setAntiA(10);

    //>>>>>NON EDITABLES<<<<<
    render->setRender(scene, image, camera);
    render->setImageType(imageType);
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

	Animator animator(16);
	bool anim = false;

	if (anim)
	{
		animator.start();
	}

	else
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

	cout << ">>> Time spent: " << finalTime << "s \n";

	delete render;

	return 0;
}

//perguntar se é pra inicializar rgb ou color (um novo vec3)