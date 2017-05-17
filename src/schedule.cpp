#include "schedule.h"

namespace artcc
{

const int Schedule::getWeight() const { return weight; }
void Schedule::setWeight(const int &weight) { this->weight = weight; }

const std::string Schedule::getTitle() const { return title; }
void Schedule::setTitle(const std::string &title) { this->title = title; }

}
