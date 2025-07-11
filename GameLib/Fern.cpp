/**
 * @file Fern.cpp
 * @author Reed Miller
 */

#include "pch.h"
#include "Fern.h"
#include "Game.h"

///Constant for Watered FileName
const std::wstring RegFernImage = L"fern_1.png";
///Constant for Dry FileName
const std::wstring DryFernImage = L"fern_2.png";

/**
 * Constructor
 * @param game Game this Flytrap belongs to
 */
Fern::Fern(Game* game, const std::wstring &resourseDir) : Plant(game, RegFernImage, resourseDir)
{
    //Set the MaxLevel for Cactus
    SetMaxLevel(1000);
}

/**
 * Function to save the state of this Fern
 * @param gameNode root node of XML
 * @return a completed xmlNode for this object
 */
wxXmlNode* Fern::Save(wxXmlNode *gameNode)
{
    //Up-call to item class
    auto itemNode = Item::Save(gameNode);

    //Call to Plant Class
    Plant::Save(itemNode);

    //Add type of plant
    itemNode->AddAttribute(L"type", L"fern");

    //Return the Node
    return itemNode;
}

/**
 * A Function to Toggle The State of the Plant
 */
void Fern::Toggle()
{
    //First we get the state
    auto state = GetState();

    //State is currently watered, flip it
    if (state == L"watered")
    {
        //Set New State
        SetState(L"dry");

        //Set new image and Bitmap
        SetImage(DryFernImage);
    }

    //Otherwise state is Dry, flip it
    else
    {
        //Set New State
        SetState(L"watered");

        //Set the Image and Bitmap
        SetImage(RegFernImage);

        //Reset the Level
        SetLevel(0);
    }
}

/**
 * Function to Load in the state of this Fern
 * @param childNode node to load Xml data from
 */
void Fern::Load(wxXmlNode* childNode)
{
    //Get State Attribute
    auto state = childNode->GetAttribute(L"state");

    //If state is Dry, toggle it
    if (state == L"dry")
    {
        Toggle();
    }

    //Call to Plant Class to load
    Plant::Load(childNode);
}