/**
 * @file MainFrame.h
 * @author Reed Miller
 *The Main Frame of the GUI
 *
 */
 
#ifndef MAINFRAME_H
#define MAINFRAME_H

//Forward References
class GameView;
class TaskView;


class MainFrame : public wxFrame{
private:
    ///Path to the resource Directory
    std::wstring mResDir;
    ///Game View Object
    GameView* mGameView = nullptr;
    ///Task View Object
    TaskView* mTaskView = nullptr;
    ///Enum Class for which Load this game is using/saving to
    enum class LoadState{Load1, Load2, Load3};
    ///Which load this Application is currently using
    LoadState mLoadState = LoadState::Load1;

    void OnAbout(wxCommandEvent &event);
    void OnCustomLoad(wxCommandEvent& event);
    void OnCustomSave(wxCommandEvent& event);
    void OnShowControls(wxCommandEvent& event);
    void OnLoad1(wxCommandEvent& event);
    void OnLoad2(wxCommandEvent& event);
    void OnLoad3(wxCommandEvent& event);
    void LoadState();
    void OnSaveCurrent(wxCommandEvent& event);
    void SaveToLoad();
    void OnExit(wxCommandEvent &event);

public:
    void Initialize();
    MainFrame(std::wstring resDir);
};



#endif //MAINFRAME_H
