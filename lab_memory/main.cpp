#include <algorithm>
#include <vector>
#include <iostream>
#include <utility>

#include "fileio.h"
#include "letter.h"
#include "room.h"
#include "allocator.h"

using namespace std;

/**
 * Main routine.
 * Creates an Allocator object and allocates the students
 */
int main()
{
	cout << endl;
	fileio::init();
	cout << "1" <<endl;
	Allocator theAllocator("students.txt", "rooms.txt");
	cout << "2" <<endl;
	theAllocator.allocate();
	cout << "3" <<endl;
	theAllocator.printRooms();
	cout << "4" <<endl;
	fileio::halt();
	cout << endl;
	return 0;
}
