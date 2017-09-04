all:
	g++ -std=c++11 -I include src/animator.cpp src/newPpm.cpp src/scene.cpp src/render.cpp src/sphere.cpp -o render