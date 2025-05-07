/**
 * @file Cactus.h
 * @author Reed Miller
 *
 *
 */
 
#ifndef CACTUS_H
#define CACTUS_H

#include "Plant.h"

/**
 * A Class that describes a Cactus Plant
 */
class Cactus : public Plant {
private:

public:
    Cactus(Game* game);
    wxXmlNode* Save(wxXmlNode* gameNode) override;
};



#endif //CACTUS_H
