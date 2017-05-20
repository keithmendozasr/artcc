#include <iostream>
#include <utility>
#include <stdexcept>

#include "scheduler.h"

using namespace std;
using namespace artcc;

void Scheduler::addTask(Task && task)
{
    cout << "Adding task \"" << task.getTitle() << "\" to schedule" << endl;

    if(task.getWeight() > maxWeight)
        throw invalid_argument("Task weight exceeds scheduler's max weight");

    taskList.push_back(task);
}
