/**
 * @file TaskManager.cpp
 * @author Reed Miller
 */

#include "pch.h"
#include "TaskManager.h"
#include "Task.h"

/**
 *Constructor
 */
TaskManager::TaskManager(int width) : mWidth(width)
{
    auto task = std::make_shared<Task>(width);
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
