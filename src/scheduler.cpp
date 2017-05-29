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
#include <iostream>
#include <utility>
#include <stdexcept>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <sstream>

#include <log4cpp/Category.hh>

#include "scheduler.h"

using namespace std;
using namespace log4cpp;

namespace artcc
{

Category& Scheduler::log = Category::getInstance("artcc.Scheduler");

void Scheduler::addTask(Task && task)
{
    log << Priority::DEBUG << "Adding task \"" << task.getTitle() << "\" to schedule";

    if(task.getWeight() > maxWeight)
        throw invalid_argument("Task weight exceeds scheduler's max weight");

    taskList.push_back(std::move(task));
}

void Scheduler::printSchedule() const
{
    if(log.isDebugEnabled())
    {
        log << Priority::DEBUG << "Schedule:";
        for(auto i : taskList)
        {
            log << Priority::DEBUG << "Task name: " << i.getTitle()
                << "\n\tID: " << i.getId()
                << "\n\tWeight: " << i.getWeight()
                << "\n\tPriority: " << i.getPriority();
        }
    }
}

vector<Task> Scheduler::getNextTasks()
{
    const unsigned int taskRowSize = taskList.size() + 1;
    const unsigned int weightScaleSize = maxWeight - currentLoad + 1;
    vector<Task> rslt;

    //Check if there's even room for new tasks
    if(maxWeight <= currentLoad)
    {
        log << Priority::INFO << "Current load is at max capacity of " << maxWeight << ". Not returning new tasks";
        return std::move(rslt);
    }
    
    // Build knapsack optimal solution set
    int **grid = new int* [taskRowSize];
    for(unsigned int i=0; i< taskRowSize; i++)
        grid[i] = new int[weightScaleSize];

    for(unsigned int i=0; i<weightScaleSize; i++)
        grid[0][i] = 0;

    for(unsigned int i=1; i < taskRowSize; i++)
        for(unsigned int j=0; j < weightScaleSize; j++)
        {
            if(taskList[i-1].getWeight() > j)
                grid[i][j] = grid[i-1][j];
            else
                grid[i][j] = max(grid[i-1][j],
                    (int)(
                        grid[i-1][j-taskList[i-1].getWeight()] + taskList[i-1].getPriority()
                    )
                );
        }

    if(log.isDebugEnabled())
    {
        ostringstream logBuf;
        for(unsigned int i=0; i< taskRowSize; i++)
        {
            for(unsigned int j=0; j< weightScaleSize; j++)
                logBuf << setw(5) << grid[i][j];
            logBuf << "\n";
        }

        log << Priority::DEBUG << "Current grid\n"
            << logBuf.str();
    }


    // Collect tasks that should run next
    {
        int i = taskList.size();
        log << Priority::DEBUG << "Task list before collecting tasks: ";
        int j = maxWeight - currentLoad;
        currentLoad = 0;
        while (i>0 && j > 0)
        {
            if(grid[i][j] != grid[i-1][j])
            {
                auto schedIter = taskList.begin() + (i -1);
                log << Priority::DEBUG << "Including task \"" << schedIter->getTitle() << "\" to result";
                i--;
                j-= schedIter->getWeight();
                currentLoad += schedIter->getWeight();
                rslt.push_back(*schedIter);
                taskList.erase(schedIter);
            }
            else
            {
                log << Priority::DEBUG << "Skipping item \"" << taskList[i-1].getTitle() << "\"";
                i--;
            }
        }
    }
    for(unsigned int i=0; i<taskRowSize; i++)
        delete[] grid[i];
    delete[] grid;

    log << Priority::DEBUG << "Total weight of new tasks: " << currentLoad;

    //Bump priority up by 1 to make sure that a "newer" task doesn't overtake
    //tasks that have were missed this pass
    for_each(taskList.begin(), taskList.end(), [](Task &i)
    {
        i.setPriority(i.getPriority()+1);
        log << Priority::DEBUG << "New priority for \"" << i.getTitle() << ": " << i.getPriority();
    });

    return std::move(rslt);
}

}
