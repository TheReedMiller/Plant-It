/**
 * @file Bank.cpp
 * @author Reed Miller
 */

#include "pch.h"
#include "Bank.h"
#include <memory>

///Constant for X coord
const int X = 850;
///Constant for Y coord
const int Y = 15;

/**
 * Constructor
 */
Bank::Bank(const std::wstring &resourseDir) : mResourseDir(resourseDir)
{
    //Set Image and Bitmap
    mItemImage = std::make_unique<wxImage>( mResourseDir + L"/Images/coin.png", wxBITMAP_TYPE_ANY);
    mItemBitmap = std::make_unique<wxBitmap>(*mItemImage);
}

/**
 * Function to Draw the Bank
 * @param gc graphics to draw on
 */
void Bank::Draw(std::shared_ptr<wxGraphicsContext> gc)
{
    //Sizes to Draw Rectangle with
    int rectWidth = 250;
    int rectHeight = 100;
    double radius = 30.0;

    //Set pen and brush (optional)
    wxPen thickPen(*wxBLACK, 3);    //color, thickness
    gc->SetPen(thickPen);
    gc->SetBrush(wxColor(3,145,93));    //fill color

    gc->DrawRoundedRectangle(X, Y, rectWidth, rectHeight, radius);


    //Draw the Coin
    gc->DrawBitmap(*mItemBitmap, X, Y, mItemBitmap->GetWidth(), mItemBitmap->GetHeight());

    //Draw the Amount of Coins

    //Convert number to wxString
    wxString numberText = wxString::Format("%d", mCoins);

    //Create a graphics font from wxFont
    wxGraphicsFont graphicsFont = gc->CreateFont(
        wxFont(50, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD),
        wxColor(195, 219, 210) // text color
    );

    //Set font on the graphics context
    gc->SetFont(graphicsFont);

    //Calculate Y position with Windows-specific adjustment
    int textY = Y + 30;

#ifdef _WIN32
    //Move text up by 50 pixels on Windows only
    textY -= 20;
#endif

    //Draw the text
    gc->DrawText(numberText, X + 105, textY);
}

/**
     * Function to Subtrack coins from the bank
     * @param coins coins to subtrack
     */
void Bank::Sub(int coins)
{
    //Subtract from coins
    mCoins -= coins;

    //Make sure there are never negatives
    if (mCoins < 0)
    {
        //If the value is ever negative, reset it to 0
        mCoins = 0;
    }
}

/**
* Function to add coins to the bank
* @param coins Coins to Add
*/
void Bank::Add(int coins)
{
    mCoins += coins;

    if (mCoins > 9999)
    {
        mCoins = 9999;
    }
}