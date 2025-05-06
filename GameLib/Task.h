/**
 * @file Task.h
 * @author Reed Miller
 *
 *
 */
 
#ifndef TASK_H
#define TASK_H


/**
* A Class that describes a Task Object
*/
class Task {
private:
    ///Width of area to display task
    int mWidth;

    ///Position of this Object
    wxPoint mPosition;

public:
    Task(int width);
    void Draw(wxDC* dc);
    bool HitTest(int x, int y);
    void SetPosition(int x, int y);
};



#endif //TASK_H
