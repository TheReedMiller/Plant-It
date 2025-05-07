/**
 * @file Flytrap.cpp
 * @author Reed Miller
 */

#include "pch.h"
#include "Flytrap.h"

/**
 * Constructor
 * @param game Game this Flytrap belongs to
 */
Flytrap::Flytrap(Game* game) : Plant(game, L"flytrap.png")
{
    //Simple up-call
}

/**
 * Function to save the state of this Flytrap
 * @param gameNode root node of XML
 * @return a completed xmlNode for this object
 */
wxXmlNode* Flytrap::Save(wxXmlNode *gameNode)
{
    //Up-call to item class
    auto itemNode = Item::Save(gameNode);

    //Add type of plant
    itemNode->AddAttribute(L"type", L"flytrap");

    //Return the Node
    return itemNode;
}