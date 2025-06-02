/**
 * @file Background.cpp
 * @author Reed Miller
 */

#include "pch.h"
#include "Background.h"

/**
 * Constructor
 * @param game The game this Background is a member of
*/
Background::Background(Game *game, const wxString& filename, const std::wstring &resourseDir) : Item(game, filename, resourseDir)
{
 //Simple up-call - No added functionality
}

/**
 * Override the Draw Function for Background Item
 * @param gc graphics to draw on
 */
void Background::Draw(std::shared_ptr<wxGraphicsContext> gc)
{
    auto wid = GetBitmap()->GetWidth();
    auto hit = GetBitmap()->GetHeight();
    gc->DrawBitmap(*GetBitmap(), GetX(), GetY(), wid, hit);
}