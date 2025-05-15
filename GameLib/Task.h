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

    ///Height of the Area to display to
    int mHeight;

    ///Position of this Object
    wxPoint mPosition;

    ///Index Within the Task Manager Object
    int mIndex = -1;    //< Starts as -1 so we can detect errors/unplaced tasks

    ///Is Complete Bool - initially false
    bool mIsComplete = false;

    ///Task Description
    wxString mDescription = L"NA";

public:
    Task(int width, int height);
    void Draw(wxDC* dc);
    bool HitTest(int x, int y);
    void SetPosition(int x, int y, bool isSet = false);
    void ToggleDifficulty();
    bool ToggleComplete();
    void Save(wxXmlNode* taskNode);
    void Load(wxXmlNode* child);
    wxString GetDifficulty();
    void SetDifficulty(wxString diff);
    void SetIndex(int index);

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

    /**
     * Getter for Description
     * @return description of task
     */
    wxString GetDescription(){return mDescription;}

    /**
     * Setter for the view height that this task is within
     * @param height height to set
     */
    void SetHeight(int height){mHeight = height;}

    /**
     * Getter for Y Coord
     * @return Y coord of this task
     */
    int GetY(){return mPosition.y;}
};



#endif //TASK_H
