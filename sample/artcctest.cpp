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
#include <sstream>
#include <stdexcept>
#include <memory>

#include <log4cpp/Category.hh>
#include <log4cpp/BasicConfigurator.hh>
#include <log4cpp/SimpleLayout.hh>

#include "task.h"
#include "scheduler.h"

using namespace std;
using namespace artcc;
using namespace log4cpp;

void getNextTasks(Scheduler &scheduler)
{
    Category &root = Category::getRoot();

    auto rslt = scheduler.getNextTasks();
    root << Priority::INFO << "Next tasks: ";
    for(auto i : rslt)
        root << Priority::INFO << i.getTitle() << " Weight: " << i.getWeight() << " Priority: " << i.getPriority();
}

int main()
{
    BasicConfigurator::configure();

    Category &root = Category::getRoot();
    root.getAppender()->setLayout(new SimpleLayout);

    {
        Category &scheduler = Category::getInstance("artcc.Scheduler");
        scheduler.setPriority(Priority::DEBUG);
    }
    //root.setPriority(Priority::DEBUG);

    Scheduler scheduler(5);

    Task tasks[] = {
        Task(1, "Item 1", 2),
        Task(1, "Item 2"),
        Task(3, "Item 5", 3),
        Task(2, "Item 3", 2),
        Task(1, "Item 4"),
    };

    for(auto i : tasks)
        scheduler.addTask(i);

    root << Priority::INFO << "Schedule after insert";
    {
        for(auto i : scheduler.getAllTasks())
            root << Priority::INFO << "Task name: " << i.getTitle()
                << "\n\tWeight: " << i.getWeight()
                << "\n\tPriority: " << i.getPriority();
    }

    getNextTasks(scheduler);
    scheduler.notifyTaskDone(tasks[3]);
    getNextTasks(scheduler);
    scheduler.notifyTaskDone(tasks[2]);
    getNextTasks(scheduler);

	return 0;
}

