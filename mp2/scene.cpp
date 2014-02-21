#include "scene.h"
#include "image.h"
#include <iostream>
using namespace std;

Scene::Scene(int max) { //Scene constructor

	maxImages = max;
	theImages = new Image*[maxImages];
	x = new int[max];
	y = new int[max];
	
	
	for (int i = 0; i < maxImages; i++) {
		theImages[i] = NULL;
	}

}

Scene::~Scene() { //Scene destructor. Calls the clear helper function
	
	clear();

}


void Scene::clear() { //clear helper function
	
	delete [] x;
	delete [] y;
	
	if (theImages != NULL) {
		
		for (int i = 0; i < maxImages; i++) {
			delete theImages[i];
		}
	}
	
	delete [] theImages;
	
	

}

void Scene::copy(const Scene &source) { //Scene copy helper function
	
	maxImages = source.maxImages;
	x = new int[maxImages];
	y = new int[maxImages];
	theImages = new Image*[maxImages];
	
	for (int i = 0; i < maxImages; i++) {
		if (source.theImages[i] != NULL) {
			theImages[i] = new Image(*(source.theImages[i]));
			x[i] = source.x[i];
			y[i] = source.y[i];	
			
		} 
		else
		{
			theImages[i]=NULL;
		}
	}
	

}


Scene::Scene(const Scene &source) { //Scene copy constructor. Calls copy helper function

	
	
	copy(source);



}

const Scene& Scene::operator=(const Scene &source) { //Operator = overload for Scene objects

	if (this!=&source) {
		
		clear();
		copy(source);
		
	}
	
	return *this;

}

void Scene::changemaxlayers(int newmax) { //Modifies the size of the array of Image pointers

	

	Image** m = new Image*[newmax];
	m = NULL;
	
	for (int i = 0; i < maxImages; i++) {
		
		*m[i] = *theImages[i];
	}

	theImages = NULL;
	theImages = m;
	
}

void Scene::addpicture(const char *Filename, int index, int xcoord, int ycoord) { //Adds picture to the scene

	if (index > maxImages || index < 0) {
		cout << "index out of bounds" << endl;
		return;
	}
	
	x[index] = xcoord;
	y[index] = ycoord;
	delete theImages[index];
	theImages[index] = new Image;
	theImages[index]->readFromFile(Filename);

}

void Scene::changelayer(int index, int newindex) { //Moves an image from one layer(index) to another layer(newindex)
	
	if (index == newindex) return;
	
	if (index > maxImages || index < 0 || newindex > maxImages || newindex < 0) {
		cout << "invalid index" << endl;
		return;
	}
	
	delete theImages[newindex];
	theImages[newindex] = theImages[index];
	x[newindex] = x[index];
	y[newindex] = y[index];
	theImages[index] = NULL;
	 

}


void Scene::translate(int index, int xcoord, int ycoord) { //Changes the x and y coordinates of an image in the specified layer.

	if (index > maxImages || index < 0 || theImages[index] == NULL) {
		cout << "invalid index" << endl;
		return;
	}
	
	x[index] = xcoord;
	y[index] = ycoord;

}

void Scene::deletepicture(int index) { //Deletes the image at the given index.
	
	if (index > maxImages || index < 0 || theImages[index] == NULL) {
		cout << "invalid index" << endl;
		return;
	}
	
	delete theImages[index];
	theImages[index] = NULL;
	

}

Image* Scene::getpicture(int index) const { //This function will return a pointer to the Image at the specified index, not a copy of it.

	if (index > maxImages || index < 0 || theImages[index] == NULL) {
		cout << "invalid index" << endl;
		return NULL;

	}
	
	return theImages[index];


}

Image Scene::drawscene() const { //This function draws the scene in the frame.
	
	int max_width = 0;
	int max_height = 0;
	
	
	for (int i = 0; i < maxImages; i++) {
		
		if (theImages[i] != NULL) {
		
			if ((theImages[i]->width() + x[i]) > max_width) {
			max_width = (theImages[i]->width() + x[i]);
			}
			
			if ((theImages[i]->height() + y[i]) > max_height) {
			max_height = (theImages[i]->height() + y[i]);
			}
		
		}
	
	}
	
	Image frame;
	frame.resize(max_width, max_height);
	
	
	for (int i = 0; i < maxImages; i++) {
		
		if (theImages[i] != NULL) {
		
			for (int j = 0; j < theImages[i]->width(); j++) {
		
				for (int k = 0; k < theImages[i]->height(); k++) {
			
				
					*(frame)(x[i]+j, y[i]+k) = *(*theImages[i])(j,k);
				}
	
	
			}

		}
	
	}


	return frame;


}
