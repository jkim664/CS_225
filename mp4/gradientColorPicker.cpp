#include <stdlib.h>
#include "gradientColorPicker.h"

/**
 * Constructs a new gradientColorPicker.
 *
 * @param fadeColor1 The first color to start the gradient at.
 * @param fadeColor2 The second color to end the gradient with.
 * @param radius How quickly to transition to fadeColor2.
 * @param centerX X coordinate for the center of the gradient.
 * @param centerY Y coordinate for the center of the gradient.
 */
gradientColorPicker::gradientColorPicker( RGBAPixel fadeColor1, 
		RGBAPixel fadeColor2, int radius, int centerX, int centerY ) {
	
	fade1 = fadeColor1;
	fade2 = fadeColor2;
	the_radius = radius;
	center_x = centerX;
	center_y = centerY;
}

/**
 * Picks the color for pixel (x, y).
 *
 * The first color fades into the second color as you move from the initial
 * fill point, the center, to the radius. Beyond the radius, all pixels
 * should be just color2. 
 *
 * You should calculate the distance between two points using the standard
 * Manhattan distance formula, 
 * 
 * \f$d = |center\_x - given\_x| + |center\_y - given\_y|\f$
 *
 * Then, scale each of the three channels (R, G, and B) from fadeColor1 to
 * fadeColor2 linearly from d = 0 to d = radius. 
 *
 * For example, the red color at distance d where d is less than the radius
 * must be
 *
 * \f$ redFill = fadeColor.red - \left\lfloor
   \frac{d*fadeColor1.red}{radius}\right\rfloor +
   \left\lfloor\frac{d*fadeColor2.red}{radius}\right\rfloor\f$
 *
 * Note that all values are integers. If you do not follow this formula,
 * your colors may be very close but round differently than ours.
 *
 * @param x The x coordinate to pick a color for.
 * @param y The y coordinate to pick a color for.
 * @return The color selected for (x, y).
 */
RGBAPixel gradientColorPicker::operator()(int x, int y)
{	
	distance = abs(center_x - x) + abs(center_y - y);
	
	if (distance < the_radius) {
	
	unsigned char redFill = fade1.red - ((distance*fade1.red)/the_radius) + ((distance*fade2.red)/the_radius);
	
	unsigned char greenFill = fade1.green - ((distance*fade1.green)/the_radius) + ((distance*fade2.green)/the_radius);
	
	unsigned char blueFill = fade1.blue - ((distance*fade1.blue)/the_radius) + ((distance*fade2.blue)/the_radius);
	
	RGBAPixel g_color(redFill, greenFill, blueFill);
	
	return g_color;
	
	}
	
	
	return fade2;
}







