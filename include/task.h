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

	Task() {};

public:
	Task(const int &weight, const std::string &title) :
		weight(weight),
		title(title)
		{}

	const int getWeight() const;
	void setWeight(const int &);

	const std::string getTitle() const;
	void setTitle(const std::string &);
};

}

#endif
