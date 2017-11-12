#include "../include/transform.h"


Transform::Transform()
{
	memset(tMatrix, 0, sizeof(tMatrix));
	tMatrix[0][0] = tMatrix[1][1] = tMatrix[2][2] = tMatrix[3][3] = 1;
}

void 
Transform::prod()
{
	float m_[4][4];

	copy(m_);

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			tMatrix[i][j] = m_[i][0]*mGeneral[0][j];
			tMatrix[i][j] += m_[i][1]*mGeneral[1][j];
			tMatrix[i][j] += m_[i][2]*mGeneral[2][j];
			tMatrix[i][j] += m_[i][3]*mGeneral[3][j];
		}
	}
}

void
Transform::scale(float s_)
{
	if (!areadyUsed)
	{
		areadyUsed = true;
		toOrigin();
	}

	memset(mGeneral, 0, sizeof(mGeneral));
	mGeneral[0][0] = mGeneral[1][1] = mGeneral[2][2] = mGeneral[3][3] = 1;

	for (int i = 0; i < 3; ++i)
	{
		mGeneral[i][i] *= s_;
	}

	prod();
}

void
Transform::translation(point3 p_)
{
	if (!areadyUsed)
	{
		areadyUsed = true;
		toOrigin();
	}

	memset(mGeneral, 0, sizeof(mGeneral));
	mGeneral[0][0] = mGeneral[1][1] = mGeneral[2][2] = mGeneral[3][3] = 1;

	mGeneral[0][3] += p_.x();
	mGeneral[1][3] += p_.y();
	mGeneral[2][3] += p_.z();

	prod();
}

void
Transform::rotate(double x_, double y_, double z_)
{
	if (!areadyUsed)
	{
		areadyUsed = true;
		toOrigin();
	}

	double x,y,z;
	double cx, cy, cz;
	double sx, sy, sz;

	x = x_*PI/180;
	y = y_*PI/180;
	z = z_*PI/180;

	cx = cos(x);
	cy = cos(y);
	cz = cos(z);

	sx = sin(x);
	sy = sin(y);
	sz = sin(z);

	memset(mGeneral, 0, sizeof(mGeneral));
	mGeneral[0][0] = mGeneral[1][1] = mGeneral[2][2] = mGeneral[3][3] = 1;

//multiplicação da matriz de transformação em fução do eixo x por eixo y e por z nesse sentido
	
	mGeneral[0][0] = cy*cz;
	mGeneral[0][1] = -(cy*sz);
	mGeneral[0][2] = sy;

	mGeneral[1][0] = sx*sy*cz + cx*sz;
	mGeneral[1][1] = -(sx*sy*sz) + cx*cz;
	mGeneral[1][2] = -(sx*cy);

	mGeneral[2][0] = -(cx*sy*cz) + sx*sz;
	mGeneral[2][1] = cx*sy*sz + sx*cz;
	mGeneral[2][2] = cx*cy;

	prod();
}

void
Transform::toOrigin()
{
	tMatrix[0][3] += refP.x();
	tMatrix[1][3] += refP.y();
	tMatrix[2][3] += refP.z();
}

void
Transform::transform(point3 & p_)
{
	if(!areadyUsed) return;

	float e[3];

	if(!finalized)
	{
		finalized = true;
		translation(-refP);
	}

	for (int j = 0; j < 3; ++j)
	{
		e[j] = tMatrix[j][0]* p_.x();
		e[j] += tMatrix[j][1]* p_.y();
		e[j] += tMatrix[j][2]* p_.z();
		e[j] += tMatrix[j][3]*1;
	}

	p_ = point3(e[0],e[1],e[2]);
}

void
Transform::printM(float m_[4][4])
{
	std::cout << "\n";
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			std::cout << m_[i][j] << " ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}

void
Transform::copy(float m_[4][4])
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			m_[i][j] = tMatrix[i][j];
		}
	}
}