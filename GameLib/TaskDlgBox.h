/**
 * @file TaskDlgBox.h
 * @author Reed Miller
 *
 *
 */
 
#ifndef TASKDLGBOX_H
#define TASKDLGBOX_H

#include <memory>

//Forward Reference
class Task;


/**
 * A Class that describes a Dialog box used to retrieve data from the user about a dask
 */
class TaskDlgBox final : public wxDialog{
private:
    ///The Task to edit
    std::shared_ptr<Task> mTask = nullptr;

    /// The machine number control
    wxTextCtrl* mTaskCtrl = nullptr;

    ///Description of Task
    wxString mDesc = "NA";

    ///Choice object for difficulty
    wxChoice* mDifficultyChoice = nullptr;

public:
    TaskDlgBox(wxWindow* parent, std::shared_ptr<Task> task);
    void OnOK(wxCommandEvent& event);
    void OnInitDialog(wxInitDialogEvent& event);
};



#endif //TASKDLGBOX_H
