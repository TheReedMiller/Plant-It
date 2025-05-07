/**
 * @file Sunflower.cpp
 * @author Reed Miller
 */

#include "pch.h"
#include "Sunflower.h"
#include "Plant.h"
#include "Game.h"

/**
 * Constructor
 * @param game the game that this object belongs to
 */
Sunflower::Sunflower(Game* game) : Plant(game, L"sunflower.png")
{
    //Simple Up-call no other functionality right now
}
