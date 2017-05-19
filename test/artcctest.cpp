#include <iostream>
#include <sstream>
#include "task.h"

using namespace std;
using namespace artcc;

int
main()
{
	Task tasks[] = {
		Task(1, "Item 1"),
		Task(2, "Item 2"),
		Task(3, "Item 3"),
		Task(4, "Item 4")
	};

	for(auto i : tasks)
		cout << "Title: " << i.getTitle() << endl
			<< "Weight: " << i.getWeight() << endl;

    tasks[2].setTitle("Change title");
	for(auto i : tasks)
		cout << "Title: " << i.getTitle() << endl
			<< "Weight: " << i.getWeight() << endl;

	return 0;
}

