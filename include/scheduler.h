#ifndef ARTCC_SCHEDULER_H
#define ARTCC_SCHEDULER_H

#include <vector>
#include <cstdint>
#include "task.h"

namespace artcc
{

class Scheduler
{
private:
    std::vector<Task> taskList;

    uint8_t maxWeight;

    Scheduler() = delete;
    Scheduler(Scheduler &&) = delete;

public:
    Scheduler(const uint8_t &maxWeight) :
        maxWeight(maxWeight)
    {}

    std::vector<Task> addTask(Task &&);
};

}
#endif
