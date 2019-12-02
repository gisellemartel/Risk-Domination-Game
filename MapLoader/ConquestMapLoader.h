
#ifndef TEAMPROJECT_COMP345_CONQUESTMAPLOADER_H
#define TEAMPROJECT_COMP345_CONQUESTMAPLOADER_H

#include "../Map/Map.h"
#include "../Utility/Utility.h"

#include <string>
#include <iostream>
#include <fstream>
#include <iostream>
#include <map>
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
