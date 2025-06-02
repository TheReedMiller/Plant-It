/**
 * @file Background.h
 * @author Reed Miller
 *
 *
 */
 
#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "Item.h"

/**
 * This Class Describes the Background Item within the game
 */
class Background : public Item
{
private:

public:
    Background(Game *game, const wxString& filename, const std::wstring &resourseDir);
    void Draw(std::shared_ptr<wxGraphicsContext> gc) override ;
};



#endif //BACKGROUND_H
