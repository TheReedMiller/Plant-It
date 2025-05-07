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
    ///Difficulty class for tasks
    enum class Difficulty {Easy, Moderate, Hard};

    ///Difficulty of this Task
    Difficulty mDifficulty = Difficulty::Easy;

    ///Width of area to display task
    int mWidth;

    ///Position of this Object
    wxPoint mPosition;

    ///Is Complete Bool - initially false
    bool mIsComplete = false;

public:
    Task(int width);
    void Draw(wxDC* dc);
    bool HitTest(int x, int y);
    void SetPosition(int x, int y);
    void ToggleDifficulty();
    bool SetComplete();
    void Save(wxXmlNode* taskNode);
    wxString Difficulty();
    void SetDifficulty(wxString diff);
};



#endif //TASK_H
