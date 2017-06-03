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
#ifndef ARTCC_TASK_H
#define ARTCC_TASK_H

#include <iostream>
#include <string>
#include <utility>
#include <functional>

#include <log4cpp/Category.hh>

namespace artcc
{

class Task
{
private:
	int weight;
	std::string title;
    std::function<void()> taskProcess;
    unsigned int priority;
    unsigned int id;
    static log4cpp::Category& log;

    Task() = delete;

public:
	//Task(const int &, const std::string &);
    Task(const int &, const std::string &, std::function<void()>, const unsigned int & = 1);

	const unsigned int getWeight() const;
	void setWeight(const int &);

	const std::string getTitle() const;
	void setTitle(const std::string &);

    const unsigned int getPriority() const;
    void setPriority(const unsigned int &);

    void setTaskProcess(std::function<void()>);
    void runTask();
};

}

#endif
