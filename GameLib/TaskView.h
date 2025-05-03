/**
 * @file TaskView.h
 * @author Reed Miller
 *
 *
 */
 
#ifndef TASKVIEW_H
#define TASKVIEW_H


/**
* A Class that describes the view that operates the tasks of this game
*/
class TaskView final : public wxScrolledCanvas {
private:

public:
    ///Constant for Window Width
    static const int Width = 300;

    TaskView(wxWindow * parent);
    void OnPaint(wxPaintEvent& event);
    void OnLeftDown(wxMouseEvent& event);
    void OnLeftUp(wxMouseEvent& event);
    void OnMouseMove(wxMouseEvent& event);
    void OnDoubleClick(wxMouseEvent& event);
    void OnTimer(wxTimerEvent& event);
    void Save(wxXmlNode* root);
};



#endif //TASKVIEW_H
