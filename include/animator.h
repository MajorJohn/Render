#ifndef _ANIMATOR_H_
#define _ANIMATOR_H_

#include "render.h"

class Animator
{
	private:

		int frames;
		Render * render;

		void init(Render* render, int frame);
		void printLoading(int row, int nRow, int frame);

	public:	

		Animator(int f_) : frames(f_) {}

		void start();



};

#endif