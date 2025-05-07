/**
 * @file TaskView.h
 * @author Reed Miller
 *
 *
 */
 
#ifndef TASKVIEW_H
#define TASKVIEW_H

#include "TaskManager.h"

//Forward Reference
class Bank;


/**
* A Class that describes the view that operates the tasks of this game
*/
class TaskView final : public wxScrolledCanvas {
private:

public:
    ///Constant for Window Width
    static const int Width = 300;

    ///Task Manager Object
    TaskManager mTaskManager;

    ///Parent Window
    std::shared_ptr<Bank> mBank = nullptr;

    ///Grabbed Task for Moving Tasks
    std::shared_ptr<Task> mGrabbedTask = nullptr;

    TaskView(wxWindow * parent, std::shared_ptr<Bank> bank);
    void OnPaint(wxPaintEvent& event);
    void OnLeftDown(wxMouseEvent& event);
    void OnLeftUp(wxMouseEvent& event);
    void OnMouseMove(wxMouseEvent& event);
    void OnDoubleClick(wxMouseEvent& event);
    void OnTimer(wxTimerEvent& event);
    void Save(wxXmlNode* root);
    void Load(wxXmlNode* taskNode);
    void OnRightClick(wxMouseEvent& event);
};



#endif //TASKVIEW_H
