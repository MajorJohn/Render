#include "../include/mesh.h"

Mesh::Mesh(string meshtxt, std::shared_ptr<Material> m_)
{
	material = m_;
	pObj = meshtxt;

	readTxt();

	setReferP(point3());
}

bool 
Mesh::hit(const Ray &ray, float t_min, float t_max, HitRecord &hr) const
{
	bool hitted = false;
	real_type throne = t_max;
	HitRecord testeHt;
	bool canNegative = false;

	for (int i = 0; i < trinagleMesh.size(); ++i)
	{
		if(trinagleMesh[i]->hit(ray, t_min, t_max, testeHt))
		{
			if (testeHt.t >= t_min && testeHt.t < throne)
			{
				hitted = true;
				throne = testeHt.t;
				hr = testeHt;
			}
		}
	}

	return hitted;
}

void
Mesh::transform(double rotate[3], float scale, point3 translation)
{
	for (int i = 0; i < trinagleMesh.size(); ++i)
	{
		trinagleMesh[i]->transform(rotate, scale, translation);
	}
}

void
Mesh::setReferP(point3 p_)
{
	for (int i = 0; i < trinagleMesh.size(); ++i)
	{
		trinagleMesh[i]->setReferP(p_);
	}
}

void
Mesh::endTransform()
{
	for (int i = 0; i < trinagleMesh.size(); ++i)
	{
		trinagleMesh[i]->endTransform();
	}
}

void
Mesh::readTxt()
{
	ifstream myfile (pObj);

	string line;

	if (myfile.is_open()) //if it was open with succed
	{
		while(!myfile.eof())
		{
			getline (myfile, line);									
			transline(line);
		}
		myfile.close();
	}
	else{
		cout << "Unable open the file\n";
		//return 1;
	}
}

void
Mesh::transline(string line)
{
	int i, n;
	int lhs;
	int start = 1;

	//para as faces
	int idx, tmp;
	float axisInt[3];

	float axis[3];

	bool vertice = false;
	bool verticeNormal = false;
	bool face = false;

	if(line[0] == '#') return;

	if(line[0] == 'g') return;

	if(line[0] == 'v' && line[1] != 'n') vertice = true;
	else if(line[0] == 'v' && line[1] == 'n') verticeNormal = true;
	else if(line[0] == 'f') face = true;
	else return;

	if(vertice)
	{
		//cout << "vertice ";
	}
	else if(verticeNormal)
	{
		//cout << "vertice Normal ";
		start = 2;
	}
	else if (face)
	{
		//cout << "face ";
	}

	while(line[start] == ' ')
		start++;

	n = 0;
	lhs = start;
	for (i = start; i < line.size(); ++i)
	{
		if(vertice || verticeNormal)
		{
			if(line[i] == ' ')
			{
				transToNum(line, axis[n], lhs, i);
				while(line[i] == ' ')
					i++;
				lhs = i;
				n++;
			}
		}
		else if(face)
		{
			if(line[i] == ' ')
			{
				tmp = lhs;
				while(line[tmp] != '/')
					tmp++;

				transToNum(line, axisInt[n], lhs, tmp);

				while(line[i] == ' ')
					i++;

				lhs = i;
				n++;

			}
		}
	}
	if(face)
		transToNum(line, axisInt[n], lhs, i);
	else if (vertice || verticeNormal)	
		transToNum(line, axis[n], lhs, i);

	point3 p(axis[0], axis[1], axis[2]);

	//cout << p << endl;
	if(vertice)
		vertices.push_back(p);
	else if(verticeNormal)
		verticesNormal.push_back(p);
	else if (face)
		trinagleMesh.push_back(std::make_shared<Triangle> (vertices[axisInt[0] - 1], vertices[axisInt[1] - 1], vertices[axisInt[2] - 1], material));
		//cout << vertices[axisInt[0]] << " " << axisInt[1] << " " << axisInt[2] << endl;
	
}


void 
Mesh::transToNum(string line, vec3::value_type & num, int lhs, int rhs)
{
	char n[256];
	int i;
	int j = 0;

	if(rhs == 0) rhs = line.size();

	//cout << lhs << " " << rhs << endl;
	for (i = lhs; i < rhs; ++i)
	{
		n[j] = line[i];
		j++;
	}

	n[j] = '\0';

	num = atof(n);

}

void 
Mesh::printMesh()
{
	for (int i = 0; i < trinagleMesh.size(); ++i)
	{
		trinagleMesh[i]->printTri();
	}
}

void 
Mesh::setTexture(std::shared_ptr<Texture> t_)
{
	material->setTexture(t_);
	for (int i = 0; i < trinagleMesh.size(); ++i)
	{
		trinagleMesh[i]->setTexture(t_);
	}
}
