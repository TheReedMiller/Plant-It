/**
 * @file WateringCan.cpp
 * @author Reed Miller
 */

#include "pch.h"
#include "WateringCan.h"

///Constant for Rotation point
const wxPoint BasePoint = wxPoint(140,140);
///Constant for headbutt speed
const double HeadbuttSpeed = 220;
///Constant for Headbutt angle
const double HeadButtAngle = 1.5;


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

/**
 * Click this item, and begin 'watering' rotation
 */
void WateringCan::Click()
{
    std::cout << "WateringCan::Click" << std::endl;
    //Activate the Watering can for animation
    mIsActive = true;
}

/**
 * Special Draw function for this watering can
 * @param dc object we are drawing on
 */
void WateringCan::Draw(wxDC* dc)
{
    //Right now just draw
    Item::Draw(dc);
    return;
    //Create a GC
    auto gc = std::shared_ptr<wxGraphicsContext>(wxGraphicsContext::Create(dc));

    //Get the Bitmap Pointer
    auto bitmap = Item::GetBitmap();

    //If this object is in the Active Animation state, rotate and draw
    if (mIsActive)
    {
        gc->PushState();
        gc->Translate(BasePoint.x, BasePoint.y);
        gc->Rotate(mCurrentAngle);
        gc->Translate(-BasePoint.x, -BasePoint.y);

        int drawX = BasePoint.x - bitmap->GetWidth() / 2;
        int drawY = BasePoint.y - bitmap->GetHeight() / 2;
        gc->DrawBitmap(*bitmap, drawX, drawY, bitmap->GetWidth(), bitmap->GetHeight());

        gc->PopState();
    }

    //otherwise just draw
    else
    {
        int drawX = BasePoint.x - bitmap->GetWidth() / 2;
        int drawY = BasePoint.y - bitmap->GetHeight() / 2;
        gc->DrawBitmap(*bitmap, drawX, drawY, bitmap->GetWidth(), bitmap->GetHeight());
    }
}

/**
 * Updates the watering can for animation
 * @param elapsed time elapsed since last update
 */
void WateringCan::Update(double elapsed)
{
    if (mIsActive)
    {
        //Check which part of the animation state it is in
        if (mIsDown)
        {
            mCurrentAngle += elapsed * HeadbuttSpeed;
            if (mCurrentAngle >= HeadButtAngle)
            {
                mIsDown = false;
            }
        }
        else
        {
            mCurrentAngle -= elapsed * HeadbuttSpeed;
            if (mCurrentAngle <= 0)
            {
                mIsActive = false;
                mCurrentAngle = 0;
            }
        }
    }
}