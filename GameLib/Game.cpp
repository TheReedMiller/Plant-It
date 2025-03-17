/**
 * @file Game.cpp
 * @author Reed Miller
 */

#include "pch.h"
#include "Game.h"

using namespace std;

/**
 * Constructor
 */
Game::Game()
{
    mBackground = make_unique<wxBitmap>(
            L"images/background.png", wxBITMAP_TYPE_ANY);

}
void Game::OnDraw(wxDC* graphics)
{
    graphics->DrawBitmap(*mBackground, 0, 0);
}