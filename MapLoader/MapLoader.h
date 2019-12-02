
#ifndef MAP_LOADER_H
#define MAP_LOADER_H

#include "../Utility/Utility.h"
#include "../Map/Map.h"

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>
using namespace std;

//MapLoader class (TARGET) ---------------------------------------------------------------------------------------------
class MapLoader {

private:
    string file_name_;
    Map* parsed_map_;

public:
    MapLoader();
    explicit MapLoader(string file_name);
    MapLoader(const MapLoader& map);
    virtual ~MapLoader();

    MapLoader& operator=(const MapLoader& map);

    Map* GetParsedMap() const;

    virtual bool ParseMap();
};

#endif //MAP_LOADER_H
