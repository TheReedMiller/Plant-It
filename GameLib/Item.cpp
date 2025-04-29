/**
 * @file Item.cpp
 * @author Reed Miller
 */

#include "pch.h"
#include "Item.h"
#include "Game.h"

/**
 * Constructor
 * @param game The game this item is a member of
 */
Item::Item(Game *game) : mGame(game)
{

}

/**
 * This function sets the positions of the item
 * @param x X coordinate we want to set
 * @param y Y coordinate we want to set
 */
void Item::SetPosition(double x, double y)
{
    //Get stuff
    mX = x;
    mY = y;
}

/**
 * Destructor for this item
 */
Item::~Item()
{

}
