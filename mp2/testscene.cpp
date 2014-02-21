/**********************************************************
 * testscene.cpp -- part of CS225 MP2
 *		  	
 * This file performs some basic tests of the Scene class.
 * It is not intended to catch every possible error.You may 
 * modifty this or write your own testscene.cpp to perform 
 * additional tests.
 *		  	
 *   Author: Jonathan Ray
 *   Date: 02 Feb 2007
 */
		  	
#include "image.h"
#include "scene.h"
#include <iostream>
using namespace std;

int main()
{
	Scene* set = new Scene(5);
	set->addpicture("in_01.png", 0, 0, 0);
	set->addpicture("in_02.png", 1, 60, 60);
	set->addpicture("in_03.png", 2, 150, 0);
	Image result = set->drawscene();
	result.writeToFile("scene.png");
	
	cout << "check 1" << endl;	

	set->changelayer(1, 3);
	result = set->drawscene();
	result.writeToFile("scene2.png");
	
	cout << "check 2" << endl;

	set->translate(0, 50, 50);
	result = set->drawscene();
	result.writeToFile("scene3.png");
	
	cout << "check 3" << endl;

	set->getpicture(0)->adjustbrightness(-70,-70,-70);
	result = set->drawscene();
	result.writeToFile("scene4.png");
	
	cout << "check 4" << endl;

	set->deletepicture(3);
	result = set->drawscene();
	result.writeToFile("scene5.png");
	
	cout << "check 5" << endl;

	Scene* sc = new Scene(*set);
	
	cout << "check 5.5" << endl;
	
	sc->getpicture(0)->flipleft();
	cout << "check 5.6" << endl;
	result = set->drawscene();
	cout << "check 5.7" << endl;
	result.writeToFile("scene6.png");  //scene 5 and scene 6 should be the same
	cout << "check 5.8" << endl;
	result = sc->drawscene();
	result.writeToFile("scene7.png");
	
	cout << "check 6" << endl;

	delete set;
	cout << "7" << endl;
	set = new Scene(5);
	cout << "8" << endl;
	*set = *sc;
	cout << "9" << endl;
	result = set->drawscene();
	cout << "10" << endl;
	result.writeToFile("scene8.png");   //scene7 and scene8 should be the same.
	cout << "11" << endl;
	delete set;
	cout << "12" << endl;
	delete sc;
	cout << "13" << endl;

	return 0;
	cout << "14" << endl;
}

