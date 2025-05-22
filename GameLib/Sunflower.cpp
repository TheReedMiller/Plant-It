/**
 * @file Sunflower.cpp
 * @author Reed Miller
 */

#include "pch.h"
#include "Sunflower.h"
#include "Plant.h"
#include "Game.h"

///Constant for Watered FileName
const std::wstring RegSunflowerImage = L"sunflower_1.png";
///Constant for Dry FileName
const std::wstring DrySunflowerImage = L"sunflower_2.png";

/**
 * Constructor
 * @param game the game that this object belongs to
 */
Sunflower::Sunflower(Game* game) : Plant(game, RegSunflowerImage)
{
    //Set the MaxLevel for Sunflower
    SetMaxLevel(1000);
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

    //Call to Plant Class
    Plant::Save(itemNode);

    //Add type of plant
    itemNode->AddAttribute(L"type", L"sunflower");

    //Return the Node
    return itemNode;
}

/**
 * A Function to Toggle The State of the Plant
 */
void Sunflower::Toggle()
{
    //First we get the state
    auto state = GetState();

    //State is currently watered, flip it
    if (state == L"watered")
    {
        //Set New State
        SetState(L"dry");

        //Set new image and Bitmap
        SetImage(DrySunflowerImage);
    }

    //Otherwise state is Dry, flip it
    else
    {
        //Set New State
        SetState(L"watered");

        //Set the Image and Bitmap
        SetImage(RegSunflowerImage);

        //Reset the Level
        SetLevel(0);
    }
}