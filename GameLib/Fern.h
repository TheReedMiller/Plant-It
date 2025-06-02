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
    Fern(Game* game, const std::wstring &resourseDir);
    wxXmlNode* Save(wxXmlNode* gameNode) override;
    void Toggle() override;
    void Load(wxXmlNode* childNode) override;
};



#endif //FERN_H
