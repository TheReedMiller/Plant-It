/**
 * @file Task.cpp
 * @author Reed Miller
 */

#include "pch.h"
#include "Task.h"


///Constant for Height of a Task
const int Height = 150;
///Constant for Task Manager Header
const int MinHeight = 125;

/**
 * Constructor
 * @param width the width of the parent frame
 */
Task::Task(int width, int height) : mWidth(width), mHeight(height)
{
    //Set Initial Position
    SetPosition(width/2, 127, true);
}

/**
 * Function to Draw this task
 * @param dc dc to draw on
 */
void Task::Draw(wxDC* dc)
{
    //Set Drawing Position
    auto pos = wxPoint(mPosition.x - mWidth / 2, mPosition.y - Height / 2);

    //MAIN BOX OBJECT

    // Set pen (for border) and brush (for fill color)
    dc->SetPen(*wxBLACK_PEN);            // Black border

    //Draw a Different shade if Completed
    if (mIsComplete)
    {
        dc->SetBrush(wxColor(208, 245, 229));
    }
    else
    {
        dc->SetBrush(*wxLIGHT_GREY_BRUSH);   // Light gray fill
    }


    // Define rectangle parameters
    double radius = 20.0;   // Radius for the rounded corners

    // Draw the rounded rectangle
    dc->DrawRoundedRectangle(pos.x, pos.y, mWidth, Height, radius);

    //Draw Checkbox
    int checkboxSize = 30;
    int checkboxPadding = 10;

    int checkboxX = pos.x + checkboxPadding;
    int checkboxY = pos.y + checkboxPadding;

    wxPen thickPen(*wxBLACK, 3);  // color, thickness
    dc->SetPen(thickPen);
    //Draw a Different shade if Completed
    if (mIsComplete)
    {
        dc->SetBrush(wxColor(208, 245, 229));
    }
    else
    {
        dc->SetBrush(*wxLIGHT_GREY_BRUSH);   // Light gray fill
    }
    dc->DrawRectangle(checkboxX, checkboxY, checkboxSize, checkboxSize);

    //Only Draw Checkbox if this Box is Marked Completed
    if (mIsComplete)
    {
        //Draw Check in box
        dc->SetPen(wxPen(wxColor(50,168,82), 5));  // green pen, slightly thicker for clarity

        // Compute center of checkbox
        int checkCenterX = checkboxX + checkboxSize / 2;
        int checkCenterY = checkboxY + checkboxSize / 2;

        // Compute size of checkmark relative to checkbox size
        int offset = checkboxSize / 4;

        // Draw checkmark (a simple "tick" shape)
        wxPoint checkStart(checkCenterX - offset, checkCenterY);
        wxPoint checkMid(checkCenterX - offset / 2, checkCenterY + offset / 2);
        wxPoint checkEnd(checkCenterX + offset, checkCenterY - offset);

        // Two lines for the check
        dc->DrawLine(checkStart, checkMid);
        dc->DrawLine(checkMid, checkEnd);
    }

    //Draw Circle
    int circleRadius = 15;  // Radius of the circle
    int circlePadding = 10;  // Space between checkbox and circle

    // Circle center position: right of the checkbox
    int circleCenterX = checkboxX + checkboxSize + circlePadding + circleRadius;
    int circleCenterY = checkboxY + checkboxSize / 2;

    dc->SetPen(*wxTRANSPARENT_PEN);               // No border

    //Determine the color of the difficulty Circle
    if (mDifficulty == Difficulty::Easy)
    {
        dc->SetBrush(wxColor(50,168,82));     // Fill with green
    }
    else if (mDifficulty == Difficulty::Moderate)
    {
        dc->SetBrush(wxColor(244,95,2));     // Fill with Orange
    }
    else if (mDifficulty == Difficulty::Hard)
    {
        dc->SetBrush(wxColor(173,39,5));
    }

    dc->DrawCircle(circleCenterX, circleCenterY, circleRadius);

    //DRAW TEXT
    // Set text color
    // Set a larger font
    wxFont font(20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    dc->SetFont(font);
    dc->SetTextForeground(*wxBLACK);

    // Get text size to center it
    int textWidth, textHeight;
    dc->GetTextExtent(mDescription, &textWidth, &textHeight);

    // Center the text within the rectangle
    int textX = pos.x + (mWidth - textWidth) / 2;
    int textY = pos.y + (Height - textHeight) / 2;

    // Draw the text
    dc->DrawText(mDescription, textX, textY);
}

/**
 * Hit Testing for this Task Object
 * @param x x coord
 * @param y y coord
 * @return success of test
 */
bool Task::HitTest(int x, int y)
{

    // Make x and y relative to the top-left corner of the bitmap image
    // Subtracting the center makes x, y relative to the image center
    // Adding half the size makes x, y relative to the image top corner
    double testX = x - mPosition.x + mWidth / 2;
    double testY = y - mPosition.y + Height / 2;

    // Test to see if x, y are in the image
    if (testX < 0 || testY < 0 || testX >= mWidth || testY >= Height)
    {
        // We are outside the image
        return false;
    }

    return true;
}

/**
 * Setter for Task Position
 * @param x x coord to set
 * @param y y coord to set
 * @param isSet True when this Function needs to be moved with the x coord too
 */
void Task::SetPosition(int x, int y, bool isSet)
{
    if (isSet)
    {
        mPosition.x = x;
    }

    if ((y > MinHeight)&&(y < mHeight))
    {
        mPosition.y = y;
    }

}

/**
 * Sets the difficulty for this task
 */
void Task::ToggleDifficulty()
{
    if (mDifficulty == Difficulty::Easy)
    {
        mDifficulty = Difficulty::Moderate;
    }
    else if (mDifficulty == Difficulty::Moderate)
    {
        mDifficulty = Difficulty::Hard;
    }
    else if (mDifficulty == Difficulty::Hard)
    {
        mDifficulty = Difficulty::Easy;
    }
}

/**
    * Function to set this task as Complete
    * @return Bool representing if this Task is now Complete
    */
bool Task::ToggleComplete()
{
    //Flip Status
    mIsComplete = !mIsComplete;

    return mIsComplete;
}

/**
 * Saves the state of this Task
 * @param taskNode root node of the task portion of the xml document
 */
void Task::Save(wxXmlNode* taskNode)
{
    //Create item node
    auto task = new wxXmlNode(wxXML_ELEMENT_NODE, L"task");
    taskNode->AddChild(task);

    //Save Task Attributes
    auto xCoord = wxString::Format(wxT("%d"), mPosition.x);
    task->AddAttribute(L"x", xCoord);  //Save x

    auto yCoord = wxString::Format(wxT("%d"), mPosition.y);
    task->AddAttribute(L"y", yCoord);  //Save y

    task->AddAttribute(L"diff", GetDifficulty());  //Save Difficulty

    task->AddAttribute(L"desc", mDescription);      //Save Description

    //Save isComplete bool member variable
    if (mIsComplete)
    {
        task->AddAttribute(L"isComplete", L"y");
    }
    else
    {
        task->AddAttribute(L"isComplete", L"n");
    }
}

/**
 * Load in a Task Object
 * @param child child node to load xml data from
 */
void Task::Load(wxXmlNode* child)
{
    //Position
    int x = 0, y = 0;
    child->GetAttribute(L"x").ToInt(&x);
    child->GetAttribute(L"y").ToInt(&y);
    SetPosition(x, y, true);

    //Difficulty
    wxString diff = child->GetAttribute(L"diff");
    SetDifficulty(diff);

    //IsComplete
    wxString isComplete = child->GetAttribute(L"isComplete");
    if (isComplete == "y")
    {
        mIsComplete = true;
    }
    else
    {
        mIsComplete = false;
    }

    //Description
    wxString desc = child->GetAttribute(L"desc");
    mDescription = desc;
}

/**
 * Function to convert the difficulty component
 * @return difficulty enum converted to a wxstrijng
 */
wxString Task::GetDifficulty()
{
    switch (mDifficulty)
    {
        case Difficulty::Easy: return L"easy";
        case Difficulty::Moderate: return L"moderate";
        case Difficulty::Hard: return L"hard";
        default: return L"easy";
    }
}

/**
 * Setter for Difficulty of task
 * @param diff difficulty to set
 */
void Task::SetDifficulty(wxString diff)
{
    if (diff == L"easy")
    {
        mDifficulty = Difficulty::Easy;
    }

    else if (diff == L"moderate")
    {
        mDifficulty = Difficulty::Moderate;
    }

    else if (diff == L"hard")
    {
        mDifficulty = Difficulty::Hard;
    }
}

/**
     * Setter for the Index of this task
     * @param index index to set
     */
void Task::SetIndex(int index)
{
    //Set the Index
    mIndex = index;

    //Set 0 index
    if (mIndex == 0)
    {
        SetPosition(mWidth/2,125, true);
        return;
    }

    SetPosition(mWidth/2, MinHeight + mIndex*(Height + 10), true);
}