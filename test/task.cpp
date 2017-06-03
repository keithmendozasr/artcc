#include <string>

#include "gtest/gtest.h"
#include "src/gtest-all.cc"

#include "task.h"

using namespace std;
using namespace artcc;

TEST(TaskTest, InitObject)
{
    const char * const tName = "Init Object Test";
    Task t(1, tName, [](){});
    EXPECT_EQ(t.getWeight(), 1u);
    EXPECT_STREQ(t.getTitle().c_str(), tName);
    EXPECT_EQ(t.getPriority(), 1u);

    const char * const t2Name = "Task New Priority";
    Task t2(10, t2Name, [](){}, 11);
    EXPECT_EQ(t2.getWeight(), 10u);
    EXPECT_STREQ(t2.getTitle().c_str(), t2Name);
    EXPECT_EQ(t2.getPriority(), 11u);
}

TEST(TaskTest, WeightGetSet)
{
    Task t(1, "WeightGetSet", [](){});

    EXPECT_EQ(t.getWeight(), 1u);
    t.setWeight(100);
    EXPECT_EQ(t.getWeight(), 100u);
}

TEST(TaskTest, TitleGetSet)
{
    Task t(1, "TitleGetSet", [](){});

    EXPECT_STREQ(t.getTitle().c_str(),"TitleGetSet");
    t.setTitle("New Title");
    EXPECT_STREQ(t.getTitle().c_str(), "New Title");
}

TEST(TaskTest, PriorityGetSet)
{
    Task t(1, "PriorityGetSet", [](){}, 5);
    EXPECT_EQ(t.getPriority(), 5u);

    t.setPriority(2);
    EXPECT_EQ(t.getPriority(), 2u);
}

TEST(TaskTest, runTask)
{
    int v = 0;
    Task t(1, "runTask", [&v](){ v += 10; });
    t.runTask();
    EXPECT_EQ(v, 10);
}

TEST(TaskTest, setTaskPriority)
{
    int v = 0;
    Task t(1, "setTaskPriority", [](){});

    t.setTaskProcess([&v](){ v = 20; });
    t.runTask();
    EXPECT_EQ(v, 20);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
