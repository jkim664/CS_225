/**
 * @file filler.cpp
 * Implementation of functions in the filler namespace. Heavily based on
 * old MP4 by CS225 Staff, Fall 2010.
 * 
 * @author Chase Geigle
 * @date Fall 2012
 */
#include "filler.h"

animation filler::dfs::fillSolid( PNG & img, int x, int y, 
        RGBAPixel fillColor, int tolerance, int frameFreq ) {
	
	solidColorPicker temp = solidColorPicker(fillColor);
    	
	return fill(img, x, y, temp, tolerance, frameFreq);
}

animation filler::dfs::fillGrid( PNG & img, int x, int y, 
        RGBAPixel gridColor, int gridSpacing, int tolerance, int frameFreq ) {
        
        gridColorPicker temp = gridColorPicker(gridColor, gridSpacing);
    
	return fill(img, x, y, temp, tolerance, frameFreq);
}

animation filler::dfs::fillGradient( PNG & img, int x, int y, 
        RGBAPixel fadeColor1, RGBAPixel fadeColor2, int radius, 
        int tolerance, int frameFreq ) {
	
	gradientColorPicker temp = gradientColorPicker(fadeColor1, fadeColor2, radius, x, y);	
	  
	return fill(img, x, y, temp, tolerance, frameFreq);
}

animation filler::dfs::fill( PNG & img, int x, int y, 
        colorPicker & fillColor, int tolerance, int frameFreq ) {
        
	return filler::fill<Stack>(img, x, y, fillColor, tolerance, frameFreq);
}

animation filler::bfs::fillSolid( PNG & img, int x, int y, 
        RGBAPixel fillColor, int tolerance, int frameFreq ) {
    
	solidColorPicker temp = solidColorPicker(fillColor);
    	
	return fill(img, x, y, temp, tolerance, frameFreq);
}

animation filler::bfs::fillGrid( PNG & img, int x, int y, 
        RGBAPixel gridColor, int gridSpacing, int tolerance, int frameFreq ) {
    
	gridColorPicker temp = gridColorPicker(gridColor, gridSpacing);
    
	return fill(img, x, y, temp, tolerance, frameFreq);
}

animation filler::bfs::fillGradient( PNG & img, int x, int y, 
        RGBAPixel fadeColor1, RGBAPixel fadeColor2, int radius, 
        int tolerance, int frameFreq ) {
    
	gradientColorPicker temp = gradientColorPicker(fadeColor1, fadeColor2, radius, x, y);	
	  
	return fill(img, x, y, temp, tolerance, frameFreq);
}

animation filler::bfs::fill( PNG & img, int x, int y, 
        colorPicker & fillColor, int tolerance, int frameFreq ) {
    
	return filler::fill<Queue>(img, x, y, fillColor, tolerance, frameFreq);
}

template <template <class T> class OrderingStructure>
animation filler::fill( PNG & img, int x, int y,
        colorPicker & fillColor, int tolerance, int frameFreq ) {
        
        int start_red = img(x,y)->red;
        int start_green = img(x,y)->green;
        int start_blue = img(x,y)->blue;
        
        int W = img.width();
        int H = img.height();
        
        int pixelCount = 0;
        
        animation A;
        
        bool** processed = new bool *[img.width()];
        
        for (int i = 0; i < img.width(); i++) {
        	processed[i] = new bool [img.height()];
        	for (int j = 0; j < img.height(); j++) {
        		processed[i][j] = false;
        	}
        	
        }
        
    
        OrderingStructure<int> xcoords;
        
        OrderingStructure<int> ycoords;
        
        xcoords.add(x);
        ycoords.add(y);
        
        while (!xcoords.isEmpty() && !ycoords.isEmpty()) {
        
        
        	int curr_x = xcoords.remove();
        	int curr_y = ycoords.remove();
        	
        	if ( ((pow((img(curr_x, curr_y)->red - start_red), 2)
        	 +     pow((img(curr_x, curr_y)->green - start_green), 2)
        	  +    pow((img(curr_x, curr_y)->blue - start_blue), 2) ) <= tolerance) && !processed[curr_x][curr_y]) {
        		
        			*img(curr_x, curr_y) = fillColor(curr_x, curr_y);
        			processed[curr_x][curr_y] = true;
        	
        	
        			pixelCount++;
        	
        			if (pixelCount%frameFreq == 0) A.addFrame(img);
        	
        			if ((curr_x + 1) < W) {				//add RIGHT neighbor
        				xcoords.add(curr_x + 1);			
        				ycoords.add(curr_y);
        			}
        	
        			if ((curr_y + 1) < H) {				//add DOWN neighbor
        				xcoords.add(curr_x);
        				ycoords.add(curr_y + 1);
        			}
        	
        			if ((curr_x - 1) >= 0) {				//add LEFT neighbor		
        				xcoords.add(curr_x - 1);
        				ycoords.add(curr_y);
        			}
        	
        			if ((curr_y - 1) >= 0) {				//add UP neighbor
        				xcoords.add(curr_x);
        				ycoords.add(curr_y - 1);
        			}
        	}
        }	
    		
    		for (int i=0; i < img.width(); i++) {
    			delete [] processed[i];
    		}
    		delete [] processed;
    		
		return A;
}





