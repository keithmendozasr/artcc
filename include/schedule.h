#ifndef ARTCC_SCHEDULE_H
#define ARTCC_SCHEDULE_H

#include <string>

namespace artcc
{

class Schedule
{
private:
	int weight;
	std::string title;

	Schedule() {};

public:
	Schedule(const int &weight, const std::string &title) :
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
