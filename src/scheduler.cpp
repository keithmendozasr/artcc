#include <iostream>
#include <utility>

#include "scheduler.h"

using namespace std;
using namespace artcc;

vector<Task> Scheduler::addTask(Task && task)
{
    cout << "Adding task " << task.getTitle() << " to schedule" << endl;
    taskList.push_back(task);
}
