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
}