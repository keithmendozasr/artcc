/******************************************************************************
 * Copyright 2017 Keith Mendoza
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ******************************************************************************/
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
    Scheduler(const Scheduler &) = delete;

public:
    Scheduler(const uint8_t &maxWeight) :
        maxWeight(maxWeight)
    {}

    void addTask(Task &&);
    
    void printSchedule() const;

    std::vector<Task> getNextTasks();
};

}
#endif
