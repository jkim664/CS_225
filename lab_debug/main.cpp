#include <cstdlib>
#include "png.h"
#include <iostream>
using namespace std;

// sets up the output image
PNG * setupOutput(int w, int h);

// Returns my favorite color
RGBAPixel * myFavoriteColor(int intensity);

int main()
{
	cout << "Check 1" << endl;
	
	// Load in.png
	PNG * original = new PNG;
	cout << "Check 2" << endl;	



	original->readFromFile("in.png");
	int width  = original->width();
	int height = original->height();

	

	cout << "Check 3" << endl;

	// Create out.png
	PNG * output = setupOutput(width, height);
	//setupOutput(width, height);

	cout << "Check 4" << endl;

	// Loud our favorite color to color the outline
	RGBAPixel * myPixel = myFavoriteColor(192);

	cout << "Check 5" << endl;

	// Go over the whole image, and if a pixel differs from that to its upper
	// left, color it my favorite color in the output
	for (int y = 1; y < height; y++)
	{
		for (int x = 1; x < width; x++)
		{
			// Calculate the pixel difference
			RGBAPixel * prev = (*original)(x-1, y-1);
			RGBAPixel * curr = (*original)(x  , y  );
			int diff = abs(curr->red   - prev->red  ) +
					   abs(curr->green - prev->green) +
					   abs(curr->blue  - prev->blue );

			

			// If the pixel is an edge pixel,
			// color the output pixel with my favorite color
			//RGBAPixel * currOutPixel = (*output)(x,y);
			if (diff > 100)
				*(*output)(x,y) = *myPixel;
		}
	}
	
	cout << "Check 6" << endl;
	// Save the output file
	output->writeToFile("out.png");
	cout << "Check 7" << endl;
	// Clean up memory
	
	delete myPixel;
	//*myPixel = NULL;
	cout << "Check 8" << endl;
	delete output;
	cout << "Check 9" << endl;
	delete original;
	cout << "Check 10" << endl;
	return 0;

	cout << "Check 11" << endl;
}


// sets up the output image
PNG * setupOutput(int w, int h)
{
	PNG * image = new PNG(w, h);
	return image;
}


// Returns my favorite color
RGBAPixel * myFavoriteColor(int intensity)
{
	RGBAPixel *color = new RGBAPixel;
	(*color).red   = 0;
	(*color).green = intensity/2;
	(*color).blue  = intensity;
	return color;
}

