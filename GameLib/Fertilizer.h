/**
 * @file Fertilizer.h
 * @author Reed Miller
 *
 *
 */
 
#ifndef FERTILIZER_H
#define FERTILIZER_H

#include "Item.h"


/**
* A class that describes a bag of fertilizer object
*/
class Fertilizer : public Item{
private:

public:
    Fertilizer(Game* game, const std::wstring &resourseDir);
    wxXmlNode* Save(wxXmlNode* gameNode) override;

    /**
     * A function that classifies
     * @return wstring representation for this item
     */
    std::wstring GetItemName()override{return L"fertilizer";}

};

#endif //FERTILIZER_H
