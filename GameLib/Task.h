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

    ///Task Description
    wxString mDescription;

public:
    Task(int width, wxString desc);
    void Draw(wxDC* dc);
    bool HitTest(int x, int y);
    void SetPosition(int x, int y);
    void ToggleDifficulty();
    bool ToggleComplete();
    void Save(wxXmlNode* taskNode);
    void Load(wxXmlNode* child);
    wxString Difficulty();
    void SetDifficulty(wxString diff);

    /**
     * Setter for the IsComplete member variable
     * @param complete bool telling if this task is completed
     */
    void SetComplete(bool complete){mIsComplete = complete;}

    /**
     * Setter for Description
     * @param desc Description to set
     */
    void SetDescription(wxString desc){mDescription = desc;}
};



#endif //TASK_H
