#include "../include/animator.h"



void
Animator::init(Render * render, int frame)
{
	stringstream ss;
	ss << frame;


	string name = "anim_";

	if (frame < 10)
		name += "00";
	else if(frame < 100)
		name += "0";

	name += ss.str();
	name += ".ppm";


	//screen resolution
// t -> amount of pixels
// h:v -> resolution proportion
//================================
	int t = 150;
	int h = 4;
	int v = 2;
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

//ADD OBJECTS
//====================================================================================================================================
    //scene->addObject(std::make_shared<Sphere>(point3( 0, 0, -1 ), 0.5, std::make_shared<Lambertian>(color (1,0.4,0))));
    //scene->addObject(std::make_shared<Sphere>(point3( 0.5, 0, -1.4 ), 0.5, std::make_shared<Lambertian>(color (1,0,0.6))));
    //scene->addObject(std::make_shared<Sphere>(point3( -0.3, 0, -0.6 ), 0.4, std::make_shared<Lambertian>(color (0.4,0.2,0.8))));
    scene->addObject(std::make_shared<Sphere>(point3( -1, 0, -1 ), 0.5, std::make_shared<Lambertian>(color (1,0.4,0))));
    scene->addObject(std::make_shared<Sphere>(point3( 2, 0, -1 ), 0.5, std::make_shared<Lambertian>(color (1,0,0.6))));
    //scene->addObject(std::make_shared<Sphere>(point3( 0.5, 0, -1 ), 0.4, std::make_shared<Lambertian>(color (0.4,0.2,0.8))));
    scene->addObject(std::make_shared<Sphere>(point3( 0, -100.5, -1 ), 100, std::make_shared<Lambertian>(color (0.6,0.4,0.2))));
	//scene->addObject(std::make_shared<Sphere>(point3( 0.2, 0, -0.9 ), 0.1, std::make_shared<Lambertian>(color (1,0.5,0.6))));

    //scene->addObject(std::make_shared<Sphere>(point3( 0, 1, -1 ), 0.2, std::make_shared<Lambertian>(color (1,0.4,0))));
//====================================================================================================================================

//ADD LIGHTS
//====================================================================================================================================
    scene->addLight(std::make_shared<SpotLight>(vec3 ( 0.5, 0, -1), color(1,1,1),vec3 (1.5,-1,0),1.0 - (2.0*(float)frame/63.0)));
    //scene->addLight(std::make_shared<PointLight>(vec3 ( 0.5, 0, -1 ), color(1,1,1), 0.5));
    //scene->addLight(std::make_shared<GlobalLight>(vec3 (-2,1,1), color(1,1,1)));
    //scene->addLight(std::make_shared<GlobalLight>(vec3 (2,1,1), color(0,0,1)));
//====================================================================================================================================


    image->setDimension(h*t, v*t);
    image->startBuffer();
    image->setName(name);

//CAMERA
//================================================================================
    float distance = 10;
    point3 cameraOrigin(0,40, 40);
    point3 lookAt(0.5, 0, -1);
    vec3 vUp(0,1,0);
    float blur = 0.0;
//--------------------------------------------------------------------------------
    camera->setPespective(blur);
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

