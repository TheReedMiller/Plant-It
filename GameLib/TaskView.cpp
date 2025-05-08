/**
 * @file TaskView.cpp
 * @author Reed Miller
 */

#include "pch.h"
#include "TaskView.h"
#include "Task.h"
#include "Bank.h"
#include "ids.h"
#include "TaskDlgBox.h"

/**
 * Constructor for this View
 * @param parent parent window
 */
TaskView::TaskView(wxWindow* parent, std::shared_ptr<Bank> bank) :
    wxScrolledCanvas(parent,
                     wxID_ANY,
                     wxDefaultPosition,
                     wxSize(Width, 800),
                     wxBORDER_SIMPLE), mTaskManager(Width), mBank(bank)
{
    SetBackgroundStyle(wxBG_STYLE_PAINT);

    //Bind Events
    Bind(wxEVT_PAINT, &TaskView::OnPaint, this); //Paint Bind
    Bind(wxEVT_LEFT_DOWN, &TaskView::OnLeftDown, this);
    Bind(wxEVT_LEFT_UP, &TaskView::OnLeftUp, this);
    Bind(wxEVT_RIGHT_DOWN, &TaskView::OnRightClick, this);
    Bind(wxEVT_MOTION, &TaskView::OnMouseMove, this);
    Bind(wxEVT_LEFT_DCLICK, &TaskView::OnDoubleClick, this);
    Bind(wxEVT_TIMER, &TaskView::OnTimer, this);
    Bind(wxEVT_KEY_DOWN, &TaskView::OnKeyDown, this);

    //Menu Event Handler
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &TaskView::OnAddTask, this, IDM_ADDTASK);

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

    //Call to Task Manager to Draw tasks
    mTaskManager.Draw(&dc);
}

/**
 * Event Handler for Left Mouse Down
 * @param event event to handle
 */
void TaskView::OnLeftDown(wxMouseEvent& event)
{
    auto click = CalcUnscrolledPosition(event.GetPosition());

    mGrabbedTask = mTaskManager.HitTest(click.x, click.y);
    mSelectedTask = mGrabbedTask;   //Set Most recently selected also
    if (mGrabbedTask != nullptr)
    {
        // Move to Back of List
        mTaskManager.MoveToBack(mGrabbedTask);

    }
}

/**
 * Event Handler for left mouse up
 * @param event event to handle
 */
void TaskView::OnLeftUp(wxMouseEvent& event)
{
    OnMouseMove(event);
    mGrabbedTask = nullptr;
}

/**
 * Event handler for mouse movement
 * @param event event to handle
 */
void TaskView::OnMouseMove(wxMouseEvent& event)
{
    // See if an item is currently being moved by the mouse
    if (mGrabbedTask != nullptr)
    {
        // If an item is being moved, we only continue to
        // move it while the left button is down.
        if (event.LeftIsDown())
        {
            mGrabbedTask->SetPosition(event.GetX(), event.GetY());
        }
        else
        {
            // When the left button is released, we release the
            // item.
            mGrabbedTask = nullptr;
        }

        // Force the screen to redraw
        Refresh();
    }
}

/**
 * Event handler for mouse double click
 * @param event event to handle
 */
void TaskView::OnDoubleClick(wxMouseEvent& event)
{
    //See if we Double-Clicked a Task
    mGrabbedTask = mTaskManager.HitTest(event.GetX(), event.GetY());

    if (mGrabbedTask != nullptr)
    {
        //Set Task
        if (mGrabbedTask->ToggleComplete())
        {
            //Add to bank
            mBank->Add(50);
        }
    }

    //Refresh the view
    Refresh();
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
    //Create Task node
    auto taskNode = new wxXmlNode(wxXML_ELEMENT_NODE, L"Task");
    root->AddChild(taskNode);

    //Save Task Manager
    mTaskManager.Save(taskNode);
}

/**
 *Load function for this view
 * @param taskNode root node of xml
 */
void TaskView::Load(wxXmlNode* taskNode)
{
    //Call to task manager to load
    mTaskManager.Load(taskNode);
    Refresh();
}

/**
 * Event handler for right-clicking
 * @param event event to handler
 */
void TaskView::OnRightClick(wxMouseEvent& event)
{
    //See if we Double-Clicked a Task
    mGrabbedTask = mTaskManager.HitTest(event.GetX(), event.GetY());

    if (mGrabbedTask != nullptr)
    {
        //Get USer Input Via Dlg Box
        TaskDlgBox dlg(this, mGrabbedTask);
        if (dlg.ShowModal() == wxID_OK) {
            // task->GetDescription() has been updated
            Refresh();
        }
    }

    //Refresh the view
    Refresh();
}

/**
 * Handles creating a new Task
 * @param event event to handle
 */
void TaskView::OnAddTask(wxCommandEvent& event)
{
    //Call to task Manager to Add Task
    auto task = mTaskManager.Add();

    //Get USer Input Via Dlg Box
    TaskDlgBox dlg(this, task);
    if (dlg.ShowModal() == wxID_OK) {
        // task->GetDescription() has been updated
        Refresh();
    }
}

/**
 * Event Handler for a Key Being Pressed
 * @param event event to handle
 */
void TaskView::OnKeyDown(wxKeyEvent& event)
{
    if (event.GetKeyCode() == WXK_BACK)
    {
        //Delete most recently Selected Task
        if (mSelectedTask != nullptr)
        {
            mTaskManager.Remove(mSelectedTask); //Call to delete the selected task
            mSelectedTask = nullptr;
        }
    }
    else
    {
        event.Skip(); // Let other handlers run if not handled
    }
}