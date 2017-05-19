#include <iostream>
#include <sstream>
#include "task.h"
#include "scheduler.h"

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

    Scheduler scheduler(5);

	for(auto i : tasks)
    {
		cout << "ID: " << i.getId() << endl
            << "Title: " << i.getTitle() << endl
			<< "Weight: " << i.getWeight() << endl
            << "Priority: " << i.getPriority() << "\n" << endl;
        scheduler.addTask(std::move(i));
    }

   /*tasks[2].setTitle("Change title");
	for(auto i : tasks)
		cout << "ID: " << i.getId() << endl
            << "Title: " << i.getTitle() << endl
			<< "Weight: " << i.getWeight() << endl
            << "Priority: " << i.getPriority() << "\n" << endl;*/

	return 0;
}

