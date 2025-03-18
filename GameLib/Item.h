/**
 * @file Item.h
 * @author Reed Miller
 *
 *
 */
 
#ifndef ITEM_H
#define ITEM_H

class Game;

/**
 * This BASE class describes items found within the game
 */
class Item {
protected:
    Item(Game *game);   //Constructor

private:
    ///Game object that this item belongs to
    Game *mGame = nullptr;

    ///X-coordinate of this item
    double mX = 0;
    ///Y-coordinate of this item
    double mY = 0;

    /// The image file name
    std::wstring mImageFileName;
    /// The underlying item image
    std::unique_ptr<wxImage> mItemImage;
    /// The bitmap we can display for this item
    std::unique_ptr<wxBitmap> mItemBitmap;

public:

    /// Default constructor (disabled)
    Item() = delete;

    /// Copy constructor (disabled)
    Item(const Item &) = delete;

    virtual ~Item();

    /// Assignment Operator
    Item &operator=(const Item &) = delete;

    /**
     * Getter for mX
     * @return the Value of mX
     */
    double getX() const { return mX; }

    /**
     * Getter for mY
     * @return value for mY
     */
    double getY() const { return mY; }

    void SetPosition(double x, double y);

};



#endif //ITEM_H
