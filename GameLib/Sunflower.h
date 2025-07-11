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
    Sunflower(Game* game, const std::wstring &resourseDir);
    wxXmlNode* Save(wxXmlNode* gameNode) override;
    void Toggle() override;
    void Load(wxXmlNode* childNode) override;
};



#endif //SUNFLOWER_H
