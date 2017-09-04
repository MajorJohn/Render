#include "../include/animator.h"



void
Animator::init(Render * render, int frame)
{
	stringstream ss;
	ss << frame;


	string name = "anim_";

	name += ss.str();
	name += ".ppm";


	Scene* scene = new Scene();
    Image* image = new Image();
    Camera* camera = new Camera();

    //>>>>> EDITABLES <<<<<

    // 0 = real Color 
	// debug types
	// 1 = normal color // 2 = depth color
	int imageType = 0;


    //scene->addObject(new Sphere(point3( 0, 0, -1 ), 0.5, new Material(color (1,0.4,0))));
    scene->addObject(new Sphere(point3( 0, -100.5, -1 ), 100, new Material(color (0.6,0.4,0.2), 2*frame)));
    scene->addObject(new Sphere(point3( 0.5, 0, -1.4 ), 0.5, new Material(color (1,0,0.6))));
    //scene->addObject(new Sphere(point3( -0.3, 0, -0.6 ), 0.4, new Material(color (0.4,0.2,0.8))));

    scene->setSun(vec3 (-1,1,1), color(1,1,1));

    image->setDimension(600, 300);
    image->startBuffer();
    image->setName(name);

    camera->setCamera(point3(-2, -1, -1), vec3(4, 0, 0), vec3(0, 2, 0), point3(0, 0, 0));

    render->setMaxDepth(1.5);
    render->setMinDepth(0.0);
    //render->setAntiA(10);

    //>>>>>NON EDITABLES<<<<<
    render->setRender(scene, image, camera);
    render->setImageType(imageType);
}

void
Animator::printLoading(int row, int nRow, int frame)
{
	float v = float(row) / float(nRow);

	v *= 50;

	system("clear"); 
	cout << ">>> Rendering frame " << frame+1 << "/" << frames << endl;
	cout << ">>> Loading [";
	for (int i = 0; i < 50; ++i)
	{
		if ( i < v)
			cout << ">";
		else
			cout << " ";	
	}

	v *= 2;
	cout << "] " << (int)v << '%' << endl;

	v = ((float(frame)) / float(frames))*100 + (v/float(frames));
	v*50;

	cout << ">>> Creating Animation " << endl;
	cout << ">>> Loading [";
	for (int i = 0; i < 50; ++i)
	{
		if ( i < v/2)
			cout << ">";
		else
			cout << " ";	
	}
	cout << "] " << (int)v << '%' << endl;
}

void
Animator::start()
{
	int index;
	int nCol;  //x
	int nRow; 	//y

	for (int i = 0; i < frames; ++i)
	{
		render = new Render;
		init(render, i);

		index = 0;

		nCol = render->getWidth();
		nRow = render->getHeight();

		for (auto row = nRow -1; row >= 0; --row)
		{
			for (int col = 0; col < nCol; ++col)
			{
				render->start(col, row, index);
				index += 3;
			}

			//cout << render[i].getImageName();
			if (row%10 == 0)			
				printLoading(nRow - row, nRow, i);
		}
				
		render->write_file();

		delete render;

	}
		printLoading(1, 1, frames-1);
}

