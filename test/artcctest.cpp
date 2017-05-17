#include <iostream>
#include <sstream>
#include "schedule.h"

using namespace std;
using namespace artcc;

int
main()
{
	Schedule schedule[] = {
		Schedule(1, "Item 1"),
		Schedule(2, "Item 2"),
		Schedule(3, "Item 3"),
		Schedule(4, "Item 4")
	};

	for(auto i : schedule)
		cout << "Title: " << i.getTitle() << endl
			<< "Weight: " << i.getWeight() << endl;

	schedule[2].setTitle("Change title");
	for(auto i : schedule)
		cout << "Title: " << i.getTitle() << endl
			<< "Weight: " << i.getWeight() << endl;

	return 0;
}

