#include "task.h"

namespace artcc
{

const int Task::getWeight() const { return weight; }
void Task::setWeight(const int &weight) { this->weight = weight; }

const std::string Task::getTitle() const { return title; }
void Task::setTitle(const std::string &title) { this->title = title; }

}
