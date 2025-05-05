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

public:
    TaskManager();
};



#endif //TASKMANAGER_H
