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

public:
    TaskManager(int width);
    void Draw(wxDC* dc);
};



#endif //TASKMANAGER_H
