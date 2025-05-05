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
};



#endif //TASK_H
