/**
 * @file TaskView.cpp
 * @author Reed Miller
 */

#include "pch.h"
#include "TaskView.h"

/**
 * CConstructor for this View
 * @param parent parent window
 */
TaskView::TaskView(wxWindow* parent) :
    wxScrolledCanvas(parent,
            wxID_ANY,
            wxDefaultPosition,
            wxSize(Width, 800),
            wxBORDER_SIMPLE)
    {
        SetBackgroundStyle(wxBG_STYLE_PAINT);

        //Bind Events
        Bind(wxEVT_PAINT, &TaskView::OnPaint, this);    //Paint Bind
        Bind(wxEVT_LEFT_DOWN, &TaskView::OnLeftDown, this);
        Bind(wxEVT_LEFT_UP, &TaskView::OnLeftUp, this);
        Bind(wxEVT_MOTION, &TaskView::OnMouseMove, this);
        Bind(wxEVT_TIMER, &TaskView::OnTimer, this);
    }


/**
 * Function to pain this view
 * @param event event to trigger paint
 */
void TaskView::OnPaint(wxPaintEvent& event)
{
    SetVirtualSize(300, 800);
    SetScrollRate(0, 1);

    wxAutoBufferedPaintDC dc(this);
    DoPrepareDC(dc);

    wxBrush background(wxColour(139,146,158));
    dc.SetBackground(background);
    dc.Clear();
}

/**
 * Event Handler for Left Mouse Down
 * @param event event to handle
 */
void TaskView::OnLeftDown(wxMouseEvent& event)
{

}

/**
 * Event Handler for left mouse up
 * @param event event to handle
 */
void TaskView::OnLeftUp(wxMouseEvent& event)
{

}

/**
 * Event handler for mouse movement
 * @param event event to handle
 */
void TaskView::OnMouseMove(wxMouseEvent& event)
{

}

/**
 * Event handler for mouse double click
 * @param event event to handle
 */
void TaskView::OnDoubleClick(wxMouseEvent& event)
{

}

/**
 * Event handler for timer oeprations
 * @param event event to handle
 */
void TaskView::OnTimer(wxTimerEvent& event)
{

}

/**
 * save function for this view
 * @param root root node of xml
 */
void TaskView::Save(wxXmlNode* root)
{

}