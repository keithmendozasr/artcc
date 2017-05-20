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

void Scheduler::printSchedule() const
{
    cout << "Schedule:" << endl;

    for(auto i : taskList)
    {
        cout << "Task name: " << i.getTitle()
            << "\n\tID: " << i.getId()
            << "\n\tWeight: " << i.getWeight()
            << "\n\tPriority: " << i.getPriority() << endl;
    }
}
