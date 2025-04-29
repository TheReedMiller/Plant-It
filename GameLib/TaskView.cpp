/**
 * @file TaskView.cpp
 * @author Reed Miller
 */

#include "pch.h"
#include "TaskView.h"

/**
 * CConstructor for this View
 * @param parent parent window
 */
TaskView::TaskView(wxWindow* parent) :
    wxScrolledCanvas(parent,
            wxID_ANY,
            wxDefaultPosition,
            wxSize(Width, 100),
            wxBORDER_SIMPLE)
    {
        SetBackgroundStyle(wxBG_STYLE_PAINT);
    }

