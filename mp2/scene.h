#ifndef SCENE_H
#define SCENE_H
#include "image.h"


class Scene {

	public:
	
	Scene(int max);

	~Scene();

	Scene(const Scene &source);

	const Scene & operator=(const Scene &source);

	void changemaxlayers(int newmax);

	void addpicture(const char *Filename, int index, int xcoord, int ycoord);

	void changelayer(int index, int newindex);

	void translate(int index, int xcoord, int ycoord);

	void deletepicture(int index);

	Image* getpicture(int index) const;

	Image drawscene() const;

	private:
	
	
	void clear();
	void copy(const Scene &source);
	Image ** theImages;
	int maxImages;
	int * x;
	int * y;

	

};
#endif
