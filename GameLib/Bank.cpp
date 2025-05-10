/**
 * @file Bank.cpp
 * @author Reed Miller
 */

#include "pch.h"
#include "Bank.h"

///Constant for X coord
const int X = 850;
///Constant for Y coord
const int Y = 15;

/**
 * Constructor
 */
Bank::Bank()
{
    //Set Image and Bitmap
    mItemImage = std::make_unique<wxImage>( L"Images/coin.png", wxBITMAP_TYPE_ANY);
    mItemBitmap = std::make_unique<wxBitmap>(*mItemImage);
}

/**
 * Function to Draw the Bank
 * @param dc dc to draw on
 */
void Bank::Draw(wxDC* dc)
{
    //Draw Rectangle

    int rectWidth = 250;
    int rectHeight = 100;
    double radius = 30.0;

    // Set pen and brush (optional)
    wxPen thickPen(*wxBLACK, 3);  // color, thickness
    dc->SetPen(thickPen);
    dc->SetBrush(wxColor(3,145,93)); // fill color

    dc->DrawRoundedRectangle(X, Y, rectWidth, rectHeight, radius);


    //Draw the Coin
    dc->DrawBitmap(*mItemBitmap, X, Y);

    //Draw the Amount of Coins

    // Convert number to wxString
    wxString numberText = wxString::Format("%d", mCoins);

    // Set font and text color
    wxFont font(50, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    dc->SetFont(font);
    dc->SetTextForeground(wxColor(195, 219, 210));  // or any color

    // Draw the text
    dc->DrawText(numberText, X + 105, Y + 30);

}

/**
     * Function to Subtrack coins from the bank
     * @param coins coins to subtrack
     */
void Bank::Sub(int coins)
{
    mCoins -= coins;

    //Make sure there are never negatives
    if (mCoins < 0)
    {
        mCoins = 0;
    }
}