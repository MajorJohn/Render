#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Image
{
	private:
		int width;
		int height;
		char* buffer;
		int bufferSize;
		bool p6 = false;
		string name;

	public:

		Image(string n_= "image.ppm", int w_=1280, int h_=720) 
		: name(n_), width(w_), height(h_) {}

		int getWidth() {return width;};
		int getHeight() {return height;};
		string getName() {return name;};
		char* getBuffer() {return buffer;};

		void setWidth(int w_) {width = w_;};
		void setHeight(int h_) {height = h_;};
		void setName(string n_) {name = n_;};
		void setDimension (int w_, int h_) {width = w_; height = h_;};
		void setP6() {p6 = true;};
		void setP3() {p6 = false;};

		void startBuffer() {bufferSize = width*height*3; buffer = new char[bufferSize];};

		void write_file()
		{
			if(!p6){
				ofstream imageFile (name) ;

				imageFile << "P3\n";
				imageFile << width << " " << height << "\n";
				imageFile << "255\n";
				for (int i = 0; i < bufferSize; i+=3)
				{
					imageFile << int((unsigned char )buffer[i]) << " " 
							  << int((unsigned char )buffer[i+1]) << " " 
							  << int((unsigned char )buffer[i+2]) << "\n";
				}
			}
			else
			{
				ofstream imageFile (name , fstream::out | ios::binary) ;

				imageFile << "P6\n";
				imageFile << width << " " << height << "\n";
				imageFile << "255\n";
				for (int i = 0; i < bufferSize; i+=3)
				{
					imageFile << (unsigned char )buffer[i]  
							  << (unsigned char )buffer[i+1] 
							  << (unsigned char )buffer[i+2];
				}
			}
		}

};//(unsigned char )buffer[i])

#endif