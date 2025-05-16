/**
 * @file WateringCan.cpp
 * @author Reed Miller
 */

#include "pch.h"
#include "WateringCan.h"

/**
 * Constructor
 */
WateringCan::WateringCan(Game *game) : Item(game, L"wateringcan.png")
{
    //Simple Up-call
}

/**
 * Removes the Ability to delete this item
 * @return Bool telling that this item cannot be deleted
 */
bool WateringCan::CanDelete()
{
    return false;
}
