#include "image.h"

void Image::flipleft() {
		
	RGBAPixel* x = new RGBAPixel;
	for (int i=0; i < (width()/2); i++) {
		for (int j=0; j < height(); j++) {

			*x = *(*this)((width()-1)-i, j);

			*(*this)((width()-1)-i, j) = *(*this)(i, j);

			*(*this)(i, j) = *x; 

		}

	}
	delete x;		
}

void Image::adjustbrightness(int r, int g, int b) {

	
	for (int i=0; i< width(); i++) {
		for (int j=0; j< height(); j++) {

			int red = (*this)(i, j)->red;
			int green = (*this)(i, j)->green;
			int blue = (*this)(i, j)->blue;
			
			if ((red + r) >= 0 && (red + r) <= 255) {
				(*this)(i, j)->red = (red + r);
			}
			else if ((red + r) < 0) (*this)(i, j)->red = 0;
			else if ((red + r) > 255) (*this)(i, j)->red = 255;

			if ((green + g) >= 0 && (green + g) <= 255) {
				(*this)(i, j)->green = (green + g);
			}
			else if ((green + g) < 0) (*this)(i, j)->green = 0;
			else if ((green + g) > 255) (*this)(i, j)->green = 255;

			if ((blue + b) >= 0 && (blue + b) <= 255) {
				(*this)(i, j)->blue = (blue + b);
			}
			else if ((blue + b) < 0) (*this)(i, j)->blue = 0;
			else if ((blue + b) > 255) (*this)(i, j)->blue = 255;


			


		}
	}




}


void Image::invertcolors() {

	for (int i=0; i< width(); i++) {
		for (int j=0; j< height(); j++) {

			int red = (*this)(i, j)->red;
			int green = (*this)(i, j)->green;
			int blue = (*this)(i, j)->blue;
			(*this)(i, j)->red = (255 - red);
			(*this)(i, j)->green = (255 - green);
			(*this)(i, j)->blue = (255 - blue);


		}
	}

}
