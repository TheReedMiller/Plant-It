/**
 * @file TaskManager.h
 * @author Reed Miller
 *
 *
 */
 
#ifndef TASKMANAGER_H
#define TASKMANAGER_H

//Forward References
class Task;

/**
* A Class that describes an object to manage tasks within the Plant-It system
*/
class TaskManager {
private:
    ///List of Tasks
    std::vector<std::shared_ptr<Task>> mTasks;
    ///Width of Parent Frame
    int mWidth;
    ///Height of the parent frame
    int mHeight;
    ///Index of the Next Available Slot to Add tasks
    int mNextIndex = 0;     //<Starts as 0

public:
    TaskManager(int width, int height);
    void Draw(wxDC* dc);
    std::shared_ptr<Task> HitTest(int x, int Y);
    void Save(wxXmlNode* taskNode);
    void Load(wxXmlNode* taskNode);
    std::shared_ptr<Task> Add();
    void Remove(std::shared_ptr<Task> task);
    void FindNextIndex();
    void SetInPlace(std::shared_ptr<Task> task);

    /**
     * Getter for the Current Number of Tasks
     * @return Number of Tasks
     */
    int GetNumTasks(){return mTasks.size();}

    /**
     * Getter for the frame height
     * @return Height of the Frame
     */
    int GetHeight(){return mHeight;}
};



#endif //TASKMANAGER_H
