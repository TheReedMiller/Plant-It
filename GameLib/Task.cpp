/**
 * @file Task.cpp
 * @author Reed Miller
 */

#include "pch.h"
#include "Task.h"


///Constant for Height of a Task
const int Height = 150;


/**
 * Constructor
 * @param width the width of the parent frame
 */
Task::Task(int width) : mWidth(width)
{

}

/**
 * Function to Draw this task
 * @param dc dc to draw on
 */
void Task::Draw(wxDC* dc)
{
    // Set pen (for border) and brush (for fill color)
    dc->SetPen(*wxBLACK_PEN);            // Black border
    dc->SetBrush(*wxLIGHT_GREY_BRUSH);   // Light gray fill

    // Define rectangle parameters
    double radius = 20.0;   // Radius for the rounded corners

    // Draw the rounded rectangle
    dc->DrawRoundedRectangle(mPosition.x, mPosition.y, mWidth, Height, radius);

    // Set text color
    dc->SetTextForeground(*wxBLACK);

    // The text to draw (you could use a class member here like mName or mLabel)
    wxString text = L"My Task";

    // Get text size to center it
    int textWidth, textHeight;
    dc->GetTextExtent(text, &textWidth, &textHeight);

    // Center the text within the rectangle
    int textX = mPosition.x + (mWidth - textWidth) / 2;
    int textY = mPosition.y + (Height - textHeight) / 2;

    // Draw the text
    dc->DrawText(text, textX, textY);
}