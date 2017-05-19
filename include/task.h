#ifndef ARTCC_TASK_H
#define ARTCC_TASK_H

#include <string>

namespace artcc
{

class Task
{
private:
	int weight;
	std::string title;
    unsigned int priority;
    unsigned int id;

	Task() {}

    static unsigned int getNextId();

public:
	Task(const int &weight, const std::string &title) :
		weight(weight),
		title(title),
        id(getNextId()),
        priority(1)
    {}

    Task(const int &, const std::string &, const unsigned int &);

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
