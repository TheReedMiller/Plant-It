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
Sunflower::Sunflower(Game* game) : Plant(game, L"sunflower_1.png")
{
    //Simple Up-call no other functionality right now
}

/**
 * Function to save the state of this Sunflower
 * @param gameNode root node of XML
 * @return a completed xmlNode for this object
 */
wxXmlNode* Sunflower::Save(wxXmlNode *gameNode)
{
    //Up-call to item class
    auto itemNode = Item::Save(gameNode);

    //Add type of plant
    itemNode->AddAttribute(L"type", L"sunflower");

    //Return the Node
    return itemNode;
}

/**
 * A Function to Toggle The State of the Plant
 */
void Sunflower::Click()
{

}