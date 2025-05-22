/**
 * @file Plant.cpp
 * @author Reed Miller
 */

#include "pch.h"
#include "Plant.h"
#include "Game.h"
#include "Item.h"

Plant::Plant(Game *game, const wxString& filename) : Item(game, filename)
{
    //Simple Up-call for right now
}

/**
 *  Set the image file to draw
 * @param file The base filename. Blank files are allowed
 */
void Plant::SetImage(const std::wstring& file)
{
    // This save the first image supplied to SetImage to
    // a member variable so we can restore it later on
    if(!file.empty() && mPlantImageFile.empty())
    {
        mPlantImageFile = file;
    }

    Item::SetImage(file);
}

/**
 * Setter for the State of this plant
 * @param state state to set
 */
void Plant::SetState(std::wstring state)
{
    if (state == L"watered")
    {
        mState = State::Watered;
    }
    if (state == L"dry")
    {
        mState = State::Dry;
    }
}

/**
 * Getter for Plant state
 * @return The state of this Plant
 */
std::wstring Plant::GetState()
{
    if (mState == State::Watered)
    {
        return L"watered";
    }

    else if (mState == State::Dry)
    {
        return L"dry";
    }
}

/**
    * Checks if this item is in the dry state
    * @return bool if this object is currently is the dry state
    */
bool Plant::IsDry()
{
    //If state is dry -> True
    if (mState == State::Dry)
    {
        return true;
    }

    //Otherwise -> False
    return false;
}

/**
 * An update function for this Plant
 * @param elapsed time since last update
 */
void Plant::Update(double elapsed)
{
    //Increment the Level
    mLevel++;

    //Change the state of this Plant if it reached max level
    if (GetLevel() >= mMaxLevel)
    {
        //Reset the level
        mLevel = 0;

        //Alter the State - only if in watered state
        if (mState == State::Watered)
        {
            //Call to the Click Function to change this plants state
            Click();
        }
    }
}
