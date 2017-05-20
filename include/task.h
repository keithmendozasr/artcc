#ifndef ARTCC_TASK_H
#define ARTCC_TASK_H

#include <iostream>
#include <string>
#include <utility>

namespace artcc
{

class Task
{
private:
	int weight;
	std::string title;
    unsigned int priority;
    unsigned int id;

    static unsigned int getNextId();

    Task() = delete;

public:
	//Task(const int &, const std::string &);
    Task(const int &, const std::string &, const unsigned int & = 1);

	const int getWeight() const;
	void setWeight(const int &);

	const std::string getTitle() const;
	void setTitle(const std::string &);

    const unsigned int getId() const;

    const unsigned int getPriority() const;
    void setPriority(const unsigned int &);
};

}

#endif
