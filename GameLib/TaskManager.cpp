/**
 * @file TaskManager.cpp
 * @author Reed Miller
 */

#include "pch.h"
#include "TaskManager.h"
#include "Task.h"

///Constant for Task Manager Header
const int HeaderHeight = 50;

/**
 *Constructor
 *@param width the width of the given view
 */
TaskManager::TaskManager(int width) : mWidth(width)
{
}



/**
 * Function to Draw this task
 * @param dc dc to draw on
 */
void TaskManager::Draw(wxDC* dc)
{
    //Draw the Header for the Task View

    int rectX = 0;  // X coordinate
    int rectY = 0;  // Y coordinate

    // Set pen and brush (optional)
    dc->SetPen(wxPen(*wxBLACK, 3));      //Black border
    dc->SetBrush(wxColor(150,150,150)); // fill color

    // Draw the rectangle
    dc->DrawRectangle(rectX, rectY, mWidth, HeaderHeight);

    // Set the font and text color
    wxFont font(18, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    dc->SetFont(font);
    dc->SetTextForeground(*wxBLACK);

    // The text to draw
    wxString text = "Task Manager";

    // Measure the text size
    int textWidth, textHeight;
    dc->GetTextExtent(text, &textWidth, &textHeight);

    // Center the text within the box
    int textX = rectX + (mWidth - textWidth) / 2;
    int textY = rectY + (HeaderHeight - textHeight) / 2;

    // Draw the text
    dc->DrawText(text, textX, textY);


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

/**
 * Saves the state of the task manager
 * @param taskNode root node for the tasks portion of the XML document
 */
void TaskManager::Save(wxXmlNode* taskNode)
{
    //Save each Task
    for (auto task : mTasks)
    {
        task->Save(taskNode);
    }
}

/**
 *Load function for this task manager
 * @param taskNode root node of xml
 */
void TaskManager::Load(wxXmlNode* taskNode)
{
    //Iterate over nodes, creating a Task for each
    auto child = taskNode->GetChildren();

    while (child != nullptr)
    {
        //Create Task
        auto task = std::make_shared<Task>(mWidth);

        //Load in task
        task->Load(child);

        //Add Task
        mTasks.push_back(task);

        //Retrieve next Child
        child = child->GetNext();

    }
}

/**
 * Function to add a new task to the task manager
 * @return Task that was created
 */
std::shared_ptr<Task> TaskManager::Add()
{
    //Create New Task
    auto task = std::make_shared<Task>(mWidth);

    //SET POSITION LOGIC HERE

    //Add to Tasks
    mTasks.push_back(task);

    //Return the task for editing
    return task;
}

/**
 * Function to Remove a given task from the TaskManager
 * @param task task to remove
 */
void TaskManager::Remove(std::shared_ptr<Task> task)
{
    //Remove the Given Task
    mTasks.erase(std::remove(mTasks.begin(), mTasks.end(), task),mTasks.end());
}