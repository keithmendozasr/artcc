#include <utility>
#include <algorithm>

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

    ::testing::AssertionResult checkExpectedTasks(const Task taskBaseline[], const unsigned int &cnt)
    {
        auto rslt = s.getAllTasks();
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
    //rslt will be a vector<Task> type
    auto rslt = s.getNextTasks();
    EXPECT_EQ(rslt.size(), 1u);
    auto t = rslt[0];
    EXPECT_EQ(t.getTitle(), string("Item 5"));

    const Task taskBaseline[] = {
        Task(1, "Item 1"),
        Task(2, "Item 2"),
        Task(3, "Item 3"),
        Task(4, "Item 4")
    };
    EXPECT_TRUE(checkExpectedTasks(taskBaseline, 4));
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
    EXPECT_TRUE(checkExpectedTasks(taskBaseline, 5));
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
