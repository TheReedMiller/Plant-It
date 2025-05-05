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
Background::Background(Game *game, const wxString& filename) : Item(game, filename)
{
 //Simple up-call - No added functionality
}