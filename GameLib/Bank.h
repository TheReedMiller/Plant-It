/**
 * @file Bank.h
 * @author Reed Miller
 *
 *
 */
 
#ifndef BANK_H
#define BANK_H


/**
* A Class that Describes the Bank for the Game View
*/
class Bank {
private:
    ///Coins in the bank
    int mCoins = 0;

    /// The underlying item image
    std::unique_ptr<wxImage> mItemImage;

    /// The bitmap we can display for this item
    std::unique_ptr<wxBitmap> mItemBitmap;
public:
    Bank();

    /**
     * Getter for Coins
     * @return Amount of Coins
     */
    int GetCoins(){return mCoins;}

    /**
     * Setter for Coins
     * @param coins Coins to set
     */
    void SetCoins(int coins) {mCoins = coins;}
    void Add(int coins);
    void Draw(std::shared_ptr<wxGraphicsContext> gc);
    void Sub(int coins);
};



#endif //BANK_H
