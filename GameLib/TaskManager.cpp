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
TaskManager::TaskManager(int width, int height) : mWidth(width), mHeight(height)
{
    //Add a Few Empty Nullptrs to the Task Vector
    for (int i = 0; i < 7; i++)
    {
        mTasks.push_back(nullptr);
    }
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
        if (task != nullptr)
        {
            task->Draw(dc);
        }
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
        //Check for Nullptr
        if (*i == nullptr)
        {
            continue;
        }

        if ((*i)->HitTest(x, y))
        {
            return *i;
        }
    }

    return  nullptr;
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
        if (task != nullptr)
        {
            task->Save(taskNode);
        }
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
        //Create Task and add
        auto task = Add();

        //Load in task
        task->Load(child);

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
    auto task = std::make_shared<Task>(mWidth - 15, mHeight);   //<Offset so that the Task Isn't drawn over my the Scroll Bar

    //SET POSITION LOGIC HERE
    //Find the Next Index
    FindNextIndex();

    //We are inserting to a new slot
    if (mTasks.size() == mNextIndex)
    {
        mTasks.insert(mTasks.begin() + mNextIndex, task);
    }

    //Otherwise, replace the nullptr
    else
    {
        mTasks[mNextIndex] = task;
    }

    //Update the Window Height, based on the Size of the Tasks
    mHeight = std::max(static_cast<int>(mTasks.size() * 160 + HeaderHeight), 800);

    //Update all Heights
    for (auto task : mTasks)
    {
        //Safeguard against empty spots
        if (task != nullptr)
        {
            task->SetHeight(mHeight);
        }
    }

    //Set Task Index
    task->SetIndex(mNextIndex);

    //Return the task for editing
    return task;
}

/**
 * Function to Remove a given task from the TaskManager
 * @param task task to remove
 */
void TaskManager::Remove(std::shared_ptr<Task> task)
{
    //Replace the Item with a Nullpr
    auto it = std::find(mTasks.begin(), mTasks.end(), task);
    if (it != mTasks.end()) {
        *it = nullptr;
    }
}

/**
 * A Function to calculate the next index to insert a task at
 */
void TaskManager::FindNextIndex()
{
    //Reset the mNext Index
    mNextIndex = 0;

    //Continue to Iterate while the Index isn't out of bounds
    while (mNextIndex < mTasks.size())
    {
        if (mTasks[mNextIndex] == nullptr)
        {
            return;
        }
        //Increment mNextIndex
        mNextIndex++;
    }
}

/**
 * This function, given a task, will set it into a correct location
 * @param task Task to move
 */
void TaskManager::SetInPlace(std::shared_ptr<Task> task)
{
    //Get its Y value
    auto y = task->GetY();

    //Get a starting index
    int index = (y - 50)/160;

    //Find Closest Index Above
    int aboveIndex = index;
    while (aboveIndex != -1)
    {
        if (mTasks[aboveIndex] == nullptr)
        {
            //Index found
            break;
        }
        //Otherwise go up
        aboveIndex--;
    }

    //Out of range above
    if (aboveIndex == -1)
    {
        aboveIndex = -1000;
    }

    //Find Closest Index Below
    int belowIndex = index + 1;
    while (belowIndex < mTasks.size())
    {
        if (mTasks[belowIndex] == nullptr)
        {
            //Lower index found
            break;
        }
        //Otherwise go down
        belowIndex++;
    }

    //Out of range below
    if (belowIndex == mTasks.size())
    {
        belowIndex = 1000;
    }

    //Find which of the two indices are closer
    auto top = index - aboveIndex;
    auto bottom = belowIndex - index;

    //Indicates are Equal or top is closer than bottom
    if (( top == bottom) || (top < bottom))
    {
        index = aboveIndex;
    }

    //Bottom is Closer
    else
    {
        index = belowIndex;
    }

    //Set the Task in Place
    mTasks[index] = task;
    task->SetIndex(index);

    if (index == 0)
    {
        task->SetPosition(mWidth/2, 125);
    }
}