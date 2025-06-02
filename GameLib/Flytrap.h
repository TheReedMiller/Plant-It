/**
 * @file Flytrap.h
 * @author Reed Miller
 *
 *
 */
 
#ifndef FLYTRAP_H
#define FLYTRAP_H

#include "Plant.h"

/**
 * A class that describes a Flytrap Plant
 */
class Flytrap : public Plant {
private:

public:
    Flytrap(Game* game, const std::wstring &resourseDir);
    wxXmlNode* Save(wxXmlNode* gameNode) override;
    void Toggle() override;
    void Load(wxXmlNode* childNode) override;
};



#endif //FLYTRAP_H
