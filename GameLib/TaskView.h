/**
 * @file TaskView.h
 * @author Reed Miller
 *
 *
 */
 
#ifndef TASKVIEW_H
#define TASKVIEW_H


/**
* A Class that describes the view that operates the tasks of this game
*/
class TaskView final : public wxScrolledCanvas {
private:

public:
    ///Constant for Window Width
    static const int Width = 300;
    TaskView(wxWindow * parent);
};



#endif //TASKVIEW_H
