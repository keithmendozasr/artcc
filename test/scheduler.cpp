#include <utility>
#include <algorithm>
#include <iostream>

#include <log4cpp/BasicConfigurator.hh>

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
        s.addTask(Task(1, "Item 2"));
        s.addTask(Task(3, "Item 5", 3));
        s.addTask(Task(1, "Item 3", 2));
        s.addTask(Task(1, "Item 4"));
    }

    ::testing::AssertionResult checkExpectedTasks(const Task taskBaseline[], const unsigned int &cnt, vector<Task> &rslt)
    {
        for(auto i=0u; i<cnt; i++)
        {
            auto t = taskBaseline[i];
            auto o = find_if(begin(rslt), end(rslt), [t](const Task &rhs) { return t.getTitle() == rhs.getTitle(); });
            if(o == end(rslt))
                return ::testing::AssertionFailure() << "Failed to find " << t.getTitle() << " from task queue";
        }

        return ::testing::AssertionSuccess();
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
    {
        auto rslt = s.getNextTasks();
        EXPECT_EQ(rslt.size(), 3u);
        const Task taskBaseline[] = {
            Task(1, "Item 1"),
            Task(2, "Item 3"),
            Task(3, "Item 5", 3),
        };
        EXPECT_TRUE(checkExpectedTasks(taskBaseline, 3, rslt));
    }
}

TEST_F(TestScheduler, getAllTasks)
{
    auto rslt = s.getAllTasks();
    Task taskBaseline[] = {
        Task(1, "Item 1"),
        Task(2, "Item 2"),
        Task(3, "Item 3"),
        Task(4, "Item 4"),
        Task(5, "Item 5", 100)
    };
    EXPECT_TRUE(checkExpectedTasks(taskBaseline, 5, rslt));
}

TEST_F(TestScheduler, notifyTaskDone)
{
    EXPECT_THROW(s.notifyTaskDone(Task(1, "")), invalid_argument);

    auto rslt = s.getNextTasks();
    for(auto i : rslt)
        ASSERT_NO_THROW(s.notifyTaskDone(i));
    EXPECT_THROW(s.notifyTaskDone(rslt[0]), invalid_argument);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
