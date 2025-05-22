/**
 * @file Cactus.cpp
 * @author Reed Miller
 */

#include "pch.h"
#include "Cactus.h"

///Constant for Watered FileName
const std::wstring RegCactusImage = L"cactus_1.png";
///Constant for Dry FileName
const std::wstring DryCactusImage = L"cactus_2.png";

/**
 * Constructor
 * @param game game this Cactus belongs to
 */
Cactus::Cactus(Game* game) : Plant(game, RegCactusImage)
{
    //Set the MaxLevel for Rose
    SetMaxLevel(1000);
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

    //Call to Plant Class
    Plant::Save(itemNode);

    //Add type of plant
    itemNode->AddAttribute(L"type", L"cactus");

    //Return the Node
    return itemNode;
}

/**
 * A Function to Toggle The State of the Plant
 */
void Cactus::Toggle()
{
    //First we get the state
    auto state = GetState();

    //State is currently watered, flip it
    if (state == L"watered")
    {
        //Set New State
        SetState(L"dry");

        //Set new image and Bitmap
        SetImage(DryCactusImage);
    }

    //Otherwise state is Dry, flip it
    else
    {
        //Set New State
        SetState(L"watered");

        //Set the Image and Bitmap
        SetImage(RegCactusImage);

        //Reset the Level
        SetLevel(0);
    }
}