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

#include "task.h"

using namespace std;

namespace artcc
{

Task::Task(const int &weight, const std::string &title, const unsigned int &priority) :
    weight(weight),
    title(title),
    priority(priority),
    id(getNextId())
{
    cout << __PRETTY_FUNCTION__ << " called" << endl;
}

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
