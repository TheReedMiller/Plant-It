/**
 * @file Fern.h
 * @author Reed Miller
 *
 *
 */
 
#ifndef FERN_H
#define FERN_H

#include "Plant.h"


/**
 * A Class that Describes A fern Plant
 */
class Fern : public Plant{
private:

public:
    Fern(Game* game);
    wxXmlNode* Save(wxXmlNode* gameNode);
    void Toggle() override;
};



#endif //FERN_H
