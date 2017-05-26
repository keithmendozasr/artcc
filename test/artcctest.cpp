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

int main()
{
    BasicConfigurator::configure();

    Category &root = Category::getRoot();
    root.getAppender()->setLayout(new SimpleLayout);
    root.setPriority(Priority::DEBUG);

    Scheduler scheduler(5);

	{
        Task tasks[] = {
            Task(1, "Item 1"),
            Task(2, "Item 2"),
            Task(5, "Item 6", 100),
            Task(3, "Item 3"),
            Task(4, "Item 4"),
            Task(6, "Item 5"),
        };

        for(auto i : tasks)
        {
            root << Priority::INFO << "ID: " << i.getId();
            root << Priority::INFO << "Title: " << i.getTitle();
            root << Priority::INFO << "Weight: " << i.getWeight();
            root << Priority::INFO << "Priority: " << i.getPriority();
            try
            {
                scheduler.addTask(std::move(i));
            }
            catch(const invalid_argument &e)
            {
                root << Priority::INFO << "Failed to add task \"" << i.getTitle() << "\" to scheduler. Cause: "
                    << e.what();
            }
        }
    }

    root << Priority::DEBUG << "Schedule after insert";
    scheduler.printSchedule();

    auto tasks = scheduler.getNextTasks();
    while(tasks.size())
    {
        root << Priority::DEBUG << "Schedule after collecting tasks";
        scheduler.printSchedule();
        tasks = scheduler.getNextTasks();
    }

	return 0;
}

