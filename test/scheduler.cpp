#include <utility>

#include "gtest/gtest.h"
#include "src/gtest-all.cc"

#include "scheduler.h"

using namespace std;
using namespace artcc;

class TestScheduler : public ::testing::Test
{
protected:
    Scheduler s;
    TestScheduler() : s(5) {}

    virtual void SetUp()
    {
        s.addTask(Task(1, "Item 1"));
        s.addTask(Task(2, "Item 2"));
        s.addTask(Task(3, "Item 3"));
        s.addTask(Task(4, "Item 4"));
        s.addTask(Task(5, "Item 5", 100));
    }
};

TEST_F(TestScheduler, addTask)
{
    Task t(1, "Item 1");
    EXPECT_NO_THROW(s.addTask(std::move(t)));

    Task t2(10, "Bad Task");
    EXPECT_THROW(s.addTask(std::move(t2)), invalid_argument);
}

TEST_F(TestScheduler, getNextTask)
{
    //rslt will be a vector<Task> type
    auto rslt = s.getNextTasks();
    EXPECT_EQ(rslt.size(), 1u);
    auto t = rslt[0];
    EXPECT_EQ(t.getTitle(), string("Item 5"));

    rslt = s.getNextTasks();
    EXPECT_EQ(rslt.size(), 0u);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
