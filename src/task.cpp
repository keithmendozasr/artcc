#include <iostream>

#include "task.h"

using namespace std;

namespace artcc
{

/*Task::Task(const int &weight, const std::string &title)
{
    cout << __PRETTY_FUNCTION__ << " called" << endl;
    this->weight = weight;
    this->title = title;
    priority = 1;
    id = getNextId();
}*/

Task::Task(const int &weight, const std::string &title, const unsigned int &priority) :
    weight(weight),
    title(title),
    priority(priority),
    id(getNextId())
{
    cout << __PRETTY_FUNCTION__ << " called" << endl;
}
/*    Task(weight, title);
    this->priority = priority;
}*/

unsigned int Task::getNextId()
{
    static unsigned int id = -1;
    id++;
    return id;
}

const int Task::getWeight() const { return weight; }
void Task::setWeight(const int &weight) { this->weight = weight; }

const std::string Task::getTitle() const { return title; }
void Task::setTitle(const std::string &title) { this->title = title; }

const unsigned int Task::getId() const { return id; }

const unsigned int Task::getPriority() const { return priority; }
void Task::setPriority(const unsigned int &priority) { this-> priority = priority; }

}
