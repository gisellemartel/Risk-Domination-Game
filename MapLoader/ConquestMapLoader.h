//
// Created by Giselle Martel on 2019-11-26.
//

#ifndef TEAMPROJECT_COMP345_CONQUESTMAPLOADER_H
#define TEAMPROJECT_COMP345_CONQUESTMAPLOADER_H

#include "Adapter.h"

#include <string>

using namespace std;
//ConquestMapLoader class (ADAPTEE)-------------------------------------------------------------------------------------
class ConquestMapLoader {

private:
    string file_name_;
    Map* parsed_map_;

public:
    ConquestMapLoader(string file_name);
    ConquestMapLoader(const ConquestMapLoader& conquest_map_loader);

    ~ConquestMapLoader();

    ConquestMapLoader& operator=(const ConquestMapLoader& conquest_map_loader);

    Map* GetParsedConquestMap() const;

    bool ParseConquestMap();
};


#endif //TEAMPROJECT_COMP345_CONQUESTMAPLOADER_H
