/**
 * @file Cactus.cpp
 * @author Reed Miller
 */

#include "pch.h"
#include "Cactus.h"

/**
 * Constructor
 * @param game game this Cactus belongs to
 */
Cactus::Cactus(Game* game) : Plant(game, L"cactus.png")
{
    //Simple up-call
}

/**
 * Function to save the state of this Cactus
 * @param gameNode root node of XML
 * @return a completed xmlNode for this object
 */
wxXmlNode* Cactus::Save(wxXmlNode *gameNode)
{
    //Up-call to item class
    auto itemNode = Item::Save(gameNode);

    //Add type of plant
    itemNode->AddAttribute(L"type", L"cactus");

    //Return the Node
    return itemNode;
}