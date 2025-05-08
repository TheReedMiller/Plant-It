/**
 * @file TaskDlgBox.cpp
 * @author Reed Miller
 */

#include "pch.h"
#include "TaskDlgBox.h"
#include "Task.h"

#include <wx/valnum.h>
#include <wx/xrc/xmlres.h>


/**
 * Constructor
 */
TaskDlgBox::TaskDlgBox(wxWindow* parent, std::shared_ptr<Task> task)
    : wxDialog(parent, wxID_ANY, "Edit Task", wxDefaultPosition, wxDefaultSize),
      mTask(task), mDesc(task->GetDescription())
{
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // Description field
    mainSizer->Add(new wxStaticText(this, wxID_ANY, "Description:"), 0, wxALL, 10);
    mTaskCtrl = new wxTextCtrl(this, wxID_ANY, mDesc);
    mTaskCtrl->SetMaxLength(25);
    mainSizer->Add(mTaskCtrl, 0, wxEXPAND | wxLEFT | wxRIGHT, 10);

    // Difficulty dropdown
    mainSizer->Add(new wxStaticText(this, wxID_ANY, "Difficulty:"), 0, wxALL, 10);
    mDifficultyChoice = new wxChoice(this, wxID_ANY);
    mDifficultyChoice->Append("easy");
    mDifficultyChoice->Append("moderate");
    mDifficultyChoice->Append("hard");
    mainSizer->Add(mDifficultyChoice, 0, wxEXPAND | wxLEFT | wxRIGHT, 10);

    // Set current selection (match string)
    wxString currentDiff = task->GetDifficulty(); // assuming this returns "Easy", etc.
    int index = mDifficultyChoice->FindString(currentDiff);
    if (index != wxNOT_FOUND) {
        mDifficultyChoice->SetSelection(index);
    }

    mainSizer->Add(CreateSeparatedButtonSizer(wxOK | wxCANCEL), 0, wxEXPAND | wxALL, 10);
    SetSizerAndFit(mainSizer);
    Centre();

    Bind(wxEVT_BUTTON, &TaskDlgBox::OnOK, this, wxID_OK);
}

/**
 * Handle the OK button press event
 * @param event Button press event
 */
void TaskDlgBox::OnOK([[maybe_unused]] wxCommandEvent& event)
{
    mDesc = mTaskCtrl->GetValue().Trim();

    if (mDesc.IsEmpty()) {
        wxMessageBox("Description cannot be empty.", "Input Error", wxICON_ERROR);
        return;
    }

    wxString selectedDifficulty = mDifficultyChoice->GetStringSelection();

    mTask->SetDescription(mDesc);
    mTask->SetDifficulty(selectedDifficulty); // your function does the internal mapping

    EndModal(wxID_OK);
}

/**
 * Initialize dialog event handler.
 *
 * This allows us to preselect the content of the edit control
 * so we don't have to do so manually to change it.
 *
 * @param event EVT_INIT_DIALOG event object
 */
void TaskDlgBox::OnInitDialog([[maybe_unused]] wxInitDialogEvent& event)
{
    // Pre-fill description with current task text
    mDesc = mTask->GetDescription();
    TransferDataToWindow();
    if (mTaskCtrl) mTaskCtrl->SelectAll();
}