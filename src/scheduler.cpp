#include <iostream>
#include <utility>
#include <stdexcept>
#include <vector>
#include <iomanip>
#include <algorithm>

#include "scheduler.h"

using namespace std;

namespace artcc
{

void Scheduler::addTask(Task && task)
{
    cout << "Adding task \"" << task.getTitle() << "\" to schedule" << endl;

    if(task.getWeight() > maxWeight)
        throw invalid_argument("Task weight exceeds scheduler's max weight");

    taskList.push_back(task);
}

void Scheduler::printSchedule() const
{
    cout << "Schedule:" << endl;

    for(auto i : taskList)
    {
        cout << "Task name: " << i.getTitle()
            << "\n\tID: " << i.getId()
            << "\n\tWeight: " << i.getWeight()
            << "\n\tPriority: " << i.getPriority() << endl;
    }
}

vector<Task> Scheduler::getNextTasks()
{
    const int taskRowSize = taskList.size() + 1;
    const int weightScaleSize = maxWeight + 1;
    
    // Build knapsack optimal solution set
    int **grid = new int* [taskRowSize];
    for(int i=0; i< taskRowSize; i++)
        grid[i] = new int[weightScaleSize];

    for(int i=0; i<weightScaleSize; i++)
        grid[0][i] = 0;

    for(int i=1; i < taskRowSize; i++)
        for(int j=0; j < weightScaleSize; j++)
        {
            if(taskList[i-1].getWeight() > j)
                grid[i][j] = grid[i-1][j];
            else
                grid[i][j] = max(grid[i-1][j],
                    (int)(
                        grid[i-1][j-taskList[i-1].getWeight()] + taskList[i-1].getPriority()
                    )
                );
        }

    for(int i=0; i< taskRowSize; i++)
    {
        for(int j=0; j< weightScaleSize; j++)
            cout << setw(5) << grid[i][j];
        cout << endl;
    }

    vector<Task> rslt;
    int nextTaskWeight = 0;

    // Collect tasks that should run next
    {
        int i = taskList.size();
        cout << "Task list before collecting tasks: " << i << endl;
        int j = maxWeight;
        while (i>0 && j > 0)
        {
            if(grid[i][j] != grid[i-1][j])
            {
                auto schedIter = taskList.begin() + (i -1);
                cout << "Including task \"" << schedIter->getTitle() << "\" to result" << endl;
                i--;
                j-= schedIter->getWeight();
                nextTaskWeight += schedIter->getWeight();
                rslt.push_back(*schedIter);
                taskList.erase(schedIter);
            }
            else
            {
                cout << "Skipping item \"" << taskList[i-1].getTitle() << "\"" << endl;
                i--;
            }
        }
    }
    for(int i=0; i<taskRowSize; i++)
        delete[] grid[i];
    delete[] grid;

    maxWeight -= nextTaskWeight;
    cout << "Total weight of new tasks: " << nextTaskWeight << endl
        << "New value for maxWeight: " << (int)maxWeight << endl;

    //Bump priority up by 1 to make sure that a "newer" task doesn't overtake
    //tasks that have were missed this pass
    for_each(taskList.begin(), taskList.end(), [](Task &i)
    {
        i.setPriority(i.getPriority()+1);
        cout << "New priority for \"" << i.getTitle() << ": " << i.getPriority() << endl;
    });

    return rslt;
}

}
