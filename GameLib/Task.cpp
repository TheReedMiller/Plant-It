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
    //Set Drawing Position
    auto pos = wxPoint(mPosition.x - mWidth / 2, mPosition.y - Height / 2);

    //MAIN BOX OBJECT

    // Set pen (for border) and brush (for fill color)
    dc->SetPen(*wxBLACK_PEN);            // Black border
    dc->SetBrush(*wxLIGHT_GREY_BRUSH);   // Light gray fill

    // Define rectangle parameters
    double radius = 20.0;   // Radius for the rounded corners

    // Draw the rounded rectangle
    dc->DrawRoundedRectangle(pos.x, pos.y, mWidth, Height, radius);

    // === Small Checkbox (top-left) ===
    int checkboxSize = 30;
    int checkboxPadding = 10;

    int checkboxX = pos.x + checkboxPadding;
    int checkboxY = pos.y + checkboxPadding;

    wxPen thickPen(*wxBLACK, 3);  // color, thickness
    dc->SetPen(thickPen);
    dc->SetBrush(*wxLIGHT_GREY_BRUSH);  // white interior with black border
    dc->DrawRectangle(checkboxX, checkboxY, checkboxSize, checkboxSize);

    //Only Draw Checkbox if this Box is Marked Completed
    if (mIsComplete)
    {
        // === Checkmark ===
        dc->SetPen(wxPen(*wxGREEN, 3));  // green pen, slightly thicker for clarity

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

    //DRAW TEXT
    // Set text color
    // Set a larger font
    wxFont font(20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    dc->SetFont(font);
    dc->SetTextForeground(*wxBLACK);

    // The text to draw (you could use a class member here like mName or mLabel)
    wxString text = L"My Task ";

    // Get text size to center it
    int textWidth, textHeight;
    dc->GetTextExtent(text, &textWidth, &textHeight);

    // Center the text within the rectangle
    int textX = pos.x + (mWidth - textWidth) / 2;
    int textY = pos.y + (Height - textHeight) / 2;

    // Draw the text
    dc->DrawText(text, textX, textY);
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
 */
void Task::SetPosition(int x, int y)
{
    mPosition.x = x;
    mPosition.y = y;
}