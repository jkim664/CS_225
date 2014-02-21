COMPILER = g++
COMPILER_FLAGS = -c -g -O0 -Wall -Werror
LINKER = g++

all : testimage testscene

testscene : image.o rgbapixel.o png.o testscene.o scene.o
	$(LINKER) image.o rgbapixel.o png.o testscene.o scene.o  -lpng -o testscene
	
testimage : image.o rgbapixel.o png.o testimage.o scene.o
	$(LINKER) image.o rgbapixel.o png.o testimage.o scene.o  -lpng -o testimage
	
	
scene.o : scene.cpp scene.h
	$(COMPILER) $(COMPILER_FLAGS) scene.cpp 	
	
testscene.o : testscene.cpp scene.h image.h
	$(COMPILER) $(COMPILER_FLAGS) testscene.cpp 	

image.o : image.cpp image.h
	$(COMPILER) $(COMPILER_FLAGS) image.cpp

png.o : png.cpp png.h
	$(COMPILER) $(COMPILER_FLAGS) png.cpp

rgbapixel.o : rgbapixel.cpp rgbapixel.h
	$(COMPILER) $(COMPILER_FLAGS) rgbapixel.cpp
