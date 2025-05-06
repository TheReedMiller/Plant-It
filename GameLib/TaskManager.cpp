/**
 * @file TaskManager.cpp
 * @author Reed Miller
 */

#include "pch.h"
#include "TaskManager.h"
#include "Task.h"

/**
 *Constructor
 *@param width the width of the given view
 */
TaskManager::TaskManager(int width) : mWidth(width)
{
    auto task = std::make_shared<Task>(width);
    task->SetPosition(width/2, 75);
    mTasks.push_back(task);
}



/**
 * Function to Draw this task
 * @param dc dc to draw on
 */
void TaskManager::Draw(wxDC* dc)
{
    //Iterate over tasks and Draw
    for (auto task : mTasks)
    {
        task->Draw(dc);
    }
}

/**
 * Hit Testing Function for Tasks
 * @param x X coord
 * @param y y coord
 * @return bool on whether we hit a task
 */
std::shared_ptr<Task> TaskManager::HitTest(int x, int y)
{
    for (auto i = mTasks.rbegin(); i != mTasks.rend();  i++)
    {
        if ((*i)->HitTest(x, y))
        {
            return *i;
        }
    }

    return  nullptr;
}

/**
 *A function to move a grabbed item to the back of the task-list
 *@param task the task to move
 */
void TaskManager::MoveToBack(std::shared_ptr<Task> task)
{
    //First We Find the Location of the clicked Task
    auto loc = find(begin(mTasks), end(mTasks), task);
    if (loc != end(mTasks))
    {
        //Remove the original element from the vector
        mTasks.erase(loc);
        //Add it back to the end of the list
        mTasks.push_back(task);
    }
}