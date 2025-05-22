/**
 * @file Sunflower.h
 * @author Reed Miller
 *
 *
 */
 
#ifndef SUNFLOWER_H
#define SUNFLOWER_H

#include "Plant.h"

/**
 * A Class that Describes a Sunflower Plant
 */
class Sunflower : public Plant{
private:

public:
    Sunflower(Game* game);
    wxXmlNode* Save(wxXmlNode* gameNode) override;
    void Toggle() override;
};



#endif //SUNFLOWER_H
