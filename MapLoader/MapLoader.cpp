/**
 * Assignment #3 COMP345, FALL 2019
 * Project: Risk Domination Game
 * Authors: Giselle Martel (26352936), Wayne Tam (21308688), Jeffrey Li (40017627), Rania Az (40041630)
 */

#include <stdexcept>
#include <string>
#include <iostream>

#include "MapLoader.h"

using namespace std;

//MapLoader class (TARGET) ---------------------------------------------------------------------------------------------
MapLoader::MapLoader() {
    file_name_ = "";
    parsed_map_ = nullptr;
}

MapLoader::MapLoader(string file_name) {
    cout << "Creating MapLoader object for file: " << file_name << endl;
    string map_name = Map::StripString(file_name, "/", ".");
    file_name_ = file_name;
    parsed_map_ = new Map(map_name);
}

MapLoader::MapLoader(const MapLoader &map) {
    file_name_ = map.file_name_;
    parsed_map_ = map.parsed_map_;
}

MapLoader::~MapLoader() {
    delete parsed_map_;
}

MapLoader &MapLoader::operator=(const MapLoader &map) = default;

Map *MapLoader::GetParsedMap() const {
    return parsed_map_;
}


bool MapLoader::ParseMap() {
    string line;
    char line_delim = '\n';
    ifstream file_to_load(file_name_);
    if (file_to_load.peek() == ifstream::traits_type::eof()) {
        cout << "File is empty! Please load a another file\n\n";
        return false;
    }

    if (file_to_load.is_open()) {
        int border_entry_count = 0;
        //read contents of .map file line by line
        while (getline(file_to_load, line, line_delim)) {
            //if line is empty or line is comment, skip it
            if (line.length() == 0 || line.at(0) == ';') {
                continue;
            }

            //parse the data in the continents section
            if (line.find("[continents]") == 0) {
                //get the next line
                int current_id = 0;
                while (getline(file_to_load, line, line_delim)) {
                    bool line_is_valid = line.find('[') == -1 && line[0] != '\r';
                    //we have reached the end of the continents section
                    if (!line_is_valid) {
                        break;
                    } else if (line[0] == '\n' || line.length() == 0 || line.at(0) == ';') {
                        continue;
                    } else {
                        string continent_data = line;
                        string delim = " ";
                        //parse the name of the continent
                        string continent_name = Map::StripString(continent_data, "", delim);
                        continent_data.erase(0, continent_name.length() + delim.length());

                        if (continent_data.length() == 0) {
                            cout << "continent " << continent_name
                                 << " is missing an army value. Please load a valid file\n\n";
                            return false;
                        }

                        //parse the army value of the continent
                        string army_value_str = Map::StripString(continent_data, "", delim);
                        int army_value;

                        try {
                            army_value = stoi(army_value_str);
                        } catch (const invalid_argument &e) {
                            cout << "the army value for continent " << continent_name
                                 << " is invalid. Please load a valid file.\n\n";
                            return false;
                        }

                        //debug string
                        //cout << continent_name << " " << army_value << endl;

                        parsed_map_->AddContinentToMap(continent_name, army_value, current_id + 1);
                        ++current_id;
                    }
                }
            }

            //parse the data in the countries  section
            if (line.find("[countries]") == 0) {
                if (parsed_map_->GetNumContinents() == 0) {
                    cout << "Failed to generate map, file was missing continents!\n\n";
                    return false;
                }
                int current_index = 1;
                //get the next line
                while (getline(file_to_load, line, line_delim)) {
                    bool line_is_valid = line.find('[') == -1 && line[0] != '\r';
                    //we have reached the end of the continents section
                    if (!line_is_valid) {
                        break;
                    } else if (line[0] == '\n' || line.length() == 0 || line.at(0) == ';') {
                        continue;
                    } else {
                        string country_data = line;
                        string delim = " ";
                        //parse the name of the continent
                        string country_num_str = Map::StripString(country_data, "", delim);
                        int country_num;

                        try {
                            country_num = stoi(country_num_str);
                        } catch (const invalid_argument &e) {
                            cout << "the country number is invalid. Please load a valid file.\n\n";
                            return false;
                        }

                        //ensure countries are in order
                        if (country_num != 0 && parsed_map_->GetNumCountries() > 0 && current_index > 0 &&
                            country_num < current_index) {
                            cout << "Countries are not in order in the file. Please load a valid file\n\n";
                            return false;
                        }

                        country_data.erase(0, country_num_str.length() + delim.length());

                        if (country_data.length() == 0) {
                            cout << "country " << country_num
                                 << " is not associated to any continent. Please load a valid file\n\n";
                            return false;
                        }

                        string continent_name = Map::StripString(country_data, "", delim);
                        country_data.erase(0, continent_name.length() + delim.length());

                        if (country_data.length() == 0) {
                            cout << "country " << country_num
                                 << " continent is missing its index value. Please load a valid file\n\n";
                            return false;
                        }

                        string continent_index_str = Map::StripString(country_data, "", delim);
                        int continent_index;

                        try {
                            continent_index = stoi(continent_index_str);
                        } catch (const invalid_argument &e) {
                            cout << "the index given for continent " << continent_name << " for country " << country_num
                                 << " is invalid. Please load a valid file.\n\n";
                            return false;
                        }
                        country_data.erase(0, continent_index_str.length() + delim.length());

                        if (country_data.length() == 0) {
                            cout << "country " << country_num
                                 << " is missing its X coordinate. Please load a valid file\n\n";
                            return false;
                        }

                        string x_coordinate_str = Map::StripString(country_data, "", delim);
                        int x_coordinate;

                        try {
                            x_coordinate = stoi(x_coordinate_str);
                        } catch (const invalid_argument &e) {
                            cout << "the X coordinate for country" << country_num
                                 << " is invalid. Please load a valid file.\n\n";
                            return false;
                        }
                        country_data.erase(0, x_coordinate_str.length() + delim.length());

                        if (country_data.length() == 0) {
                            //throw error
                            cout << "country " << country_num
                                 << " is missing its Y coordinate. Please load a valid file\n\n";
                            return false;
                        }

                        string y_coordinate_str = Map::StripString(country_data, "", delim);
                        int y_coordinate;

                        try {
                            y_coordinate = stoi(y_coordinate_str);
                        } catch (const invalid_argument &e) {
                            cout << "the Y coordinate for country" << country_num
                                 << " is invalid. Please load a valid file.\n\n";
                            return false;
                        }
                        country_data.erase(0, y_coordinate_str.length() + delim.length());

                        //debug string
                        //cout << country_num << " " << continent_name << " " << continent_index << " " << x_coordinate << " " << y_coordinate << endl;

                        parsed_map_->AddCountryToMap(country_num, continent_name, continent_index, x_coordinate,
                                                     y_coordinate);
                        ++current_index;
                    }
                }

                if (parsed_map_->GetNumCountries() > 0) {
                    parsed_map_->CreateAdjacencyMatrix();
                }
            }

            //parse the data in the borders section
            if (line.find("[borders]") == 0) {

                if (parsed_map_->GetNumCountries() == 0) {
                    cout << "Failed to generate map, file was missing countries!\n\n";
                    return false;
                }
                //get the next line
                int current_country = 0;
                while (getline(file_to_load, line, line_delim)) {
                    bool line_is_valid = line.find('[') == -1 && line[0] != '\r';
                    //we have reached the end of the border section
                    if (!line_is_valid) {
                        break;
                    } else if (line[0] == '\n' || line.length() == 0 || line.at(0) == ';') {
                        continue;
                    } else {
                        string border_data = line;
                        vector<int> borders;

                        while (border_data.length() > 0 && border_data[0] != '\r') {
                            string delim = " ";
                            string border_str = Map::StripString(border_data, "", delim);
                            border_data.erase(0, border_str.length() + delim.length());

                            int border;
                            try {
                                border = stoi(border_str);
                                //border values start from 1 and end at last country
                                if (border < 0 || border > parsed_map_->GetNumCountries()) {
                                    cout << "invalid values given for border. Please load a valid file\n\n";
                                    return false;
                                }
                                borders.push_back(border);
                            } catch (const invalid_argument &e) {
                                cout << "invalid values given for border. Please load a valid file\n\n";
                                return false;
                            }

                            //debug string
                            // cout << border << " ";
                        }

                        if (borders.empty()) {
                            cout << "No borders specified for entry in borders section. Please load a valid file\n\n";
                            return false;

                        } else if (borders.size() > parsed_map_->GetNumCountries()) {
                            cout << "File contains more border than there are countries. Please load a valid file.\n\n";
                            return false;
                        } else {

                            for (size_t i = 1; i < borders.size(); ++i) {

                                if (borders[i] - 1 == -1) {
                                    cout << "invalid values given for border. Please load a valid file\n\n";
                                    return false;
                                }
                                if (i == current_country) {
                                    continue;
                                }
                                parsed_map_->SetTwoCountriesAsNeighbours(true, borders[0] - 1, borders[i] - 1);
                            }
                            ++current_country;
                            ++border_entry_count;
                        }

                        //debug string
                        //cout << endl;
                    }
                }
            }
        }
        file_to_load.close();

        if (border_entry_count == 0) {
            cout << "Failed to generate map, file was missing borders!\n\n";
            return false;
        }

        if (border_entry_count != parsed_map_->GetNumCountries()) {
            cout << "Invalid values given for border. Please load a valid file!\n\n";
            return false;
        }

        if (parsed_map_->GetNumCountries() == 0 && parsed_map_->GetNumContinents() == 0) {
            cout << "Failed to generate map for file " << file_name_ << "! Please try again\n\n";
            return false;
        }

        return true;

    } else {
        cout << "unable to open the file " << file_name_ << ". Please try again\n\n";
        return false;
    }
}


//ConquestMapLoader class (ADAPTEE)-------------------------------------------------------------------------------------
ConquestMapLoader::ConquestMapLoader(string file_name) {
    file_name_ = file_name;
    parsed_map_ = nullptr;
}

ConquestMapLoader::ConquestMapLoader(const ConquestMapLoader &conquest_map_loader) {
    file_name_ = conquest_map_loader.file_name_;
    parsed_map_ = conquest_map_loader.parsed_map_;
}

ConquestMapLoader::~ConquestMapLoader() {
    parsed_map_ = nullptr;
    delete parsed_map_;
}

ConquestMapLoader &ConquestMapLoader::operator=(const ConquestMapLoader &conquest_map_loader) {
    file_name_ = conquest_map_loader.file_name_;
    parsed_map_ = conquest_map_loader.parsed_map_;
    return *this;
}

Map *ConquestMapLoader::GetParsedConquestMap() const {
    return parsed_map_;
}

bool ConquestMapLoader::ParseConquestMap() {
    cout << "\n started parsing conquest map\n";

    string line;
    vector< string> neigbours;
    char line_delim = '\n';
    ifstream file_to_load(file_name_);
    if (file_to_load.peek() == ifstream::traits_type::eof()) {
        cout << "File is empty! Please load a another file\n\n";
        return false;
    }

    if (file_to_load.is_open()) {
        int border_entry_count = 0;
        //read contents of .map file line by line
        while (getline(file_to_load, line, line_delim)) {
            //if line is empty or line is comment, skip it
            if (line.length() == 0) {
                continue;
            }

            //parse the data in the continents section
            if (line.find("[Continents]") == 0) {
                //get the next line
                int current_id = 0;
                while (getline(file_to_load, line, line_delim)) {
                    bool line_is_valid = line.find('[') == -1 && line[0] != '\r';
                    //we have reached the end of the continents section
                    if (!line_is_valid) {
                        break;
                    } else if (line[0] == '\n' || line.length() == 0) {
                        continue;
                    } else {
                        string continent_data = line;
                        string delim = "=";
                        //parse the name of the continent
                        string continent_name = Map::StripString(continent_data, "", delim);
                        continent_data.erase(0, continent_name.length() + delim.length());

                        if (continent_data.length() == 0) {
                            cout << "continent " << continent_name
                                 << " is missing an army value. Please load a valid file\n\n";
                            return false;
                        }

                        //parse the army value of the continent

                        int army_value;

                        try {
                            army_value = stoi(continent_data);
                        } catch (const invalid_argument &e) {
                            cout << "the army value for continent " << continent_name
                                 << " is invalid. Please load a valid file.\n\n";
                            return false;
                        }

                        //debug string
                        //cout << continent_name << " " << army_value << endl;

                        parsed_map_->AddContinentToMap(continent_name, army_value, current_id + 1);
                        ++current_id;
                    }
                }
            }

            //parse the data in the countries  section
            if (line.find("[Territories]") == 0) {
                if (parsed_map_->GetNumContinents() == 0) {
                    cout << "Failed to generate map, file was missing continents!\n\n";
                    return false;
                }
                int current_index = 1;
                //get the next line
                while (getline(file_to_load, line, line_delim)) {
                    bool line_is_valid = line.find('[') == -1 && line[0] != '\r';
                    //we have reached the end of the continents section
                    if (!line_is_valid) {
                        break;
                    } else if (line[0] == '\n' || line.length() == 0) {
                        continue;
                    } else {
                        string country_data = line;
                        string delim = ",";


                        int country_num = current_index;

                        string country_name = Map::StripString(country_data, "", delim);
                        country_data.erase(0, country_name.length() + delim.length());

                        if (country_data.length() == 0) {
                            cout << "country " << country_num
                                 << " Country Data is not complete. Please load a valid file\n\n";
                            return false;
                        }


                        string x_coordinate_str = Map::StripString(country_data, "", delim);
                        int x_coordinate;

                        try {
                            x_coordinate = stoi(x_coordinate_str);
                        } catch (const invalid_argument &e) {
                            cout << "the X coordinate for country" << country_num
                                 << " is invalid. Please load a valid file.\n\n";
                            return false;
                        }
                        country_data.erase(0, x_coordinate_str.length() + delim.length());

                        if (country_data.length() == 0) {
                            //throw error
                            cout << "country " << country_num
                                 << " is missing its Y coordinate. Please load a valid file\n\n";
                            return false;
                        }

                        string y_coordinate_str = Map::StripString(country_data, "", delim);
                        int y_coordinate;

                        try {
                            y_coordinate = stoi(y_coordinate_str);
                        } catch (const invalid_argument &e) {
                            cout << "the Y coordinate for country" << country_name
                                 << " is invalid. Please load a valid file.\n\n";
                            return false;
                        }
                        country_data.erase(0, y_coordinate_str.length() + delim.length());


                        string continent_name = Map::StripString(country_data, "", delim);
                        country_data.erase(0, continent_name.length() + delim.length());

                        int continent_index;

                        try {
                            continent_index = parsed_map_->GetContinentByName(continent_name)->GetContinentID();
                        } catch (const exception &e) {
                            cout << "the name given for continent " << continent_name << " for country " << country_name
                                 << " is invalid. Please load a valid file.\n\n";
                            return false;
                        }


                        if (country_data.length() == 0) {
                            cout << "country " << country_num
                                 << " is missing its neighbours. Please load a valid file\n\n";
                            return false;
                        }

                        country_data = country_data + delim;

                        while (true) {
                            string neighbour_name = Map::StripString(country_data, "", delim);
                            neigbours.push_back(neighbour_name);
                            country_data.erase(0, neighbour_name.length() + delim.length());
                            if (country_data.length() == 0) {
                                break;
                            }
                        }
                        //debug string
                        //cout << country_num << " " << continent_name << " " << continent_index << " " << x_coordinate << " " << y_coordinate << endl;

                        parsed_map_->AddCountryToMap(country_num, country_name, continent_index, x_coordinate,
                                                     y_coordinate);
                        ++current_index;
                    }
                }

                if (parsed_map_->GetNumCountries() > 0) {
                    parsed_map_->CreateAdjacencyMatrix();
                }
            }


            for (int i = 0; i < neigbours.size(); i++) {
                int id_1 = i+1;
                int id_2 = parsed_map_->GetCountryByName(neigbours.at(i))->GetCountryID();
                parsed_map_->SetTwoCountriesAsNeighbours(true, id_1, id_2);
            }

        }
        file_to_load.close();


        if (parsed_map_->GetNumCountries() == 0 && parsed_map_->GetNumContinents() == 0) {
            cout << "Failed to generate map for file " << file_name_ << "! Please try again\n\n";
            return false;
        }

        return true;

    } else {
        cout << "unable to open the file " << file_name_ << ". Please try again\n\n";
        return false;
    }
}




//Adapter class --------------------------------------------------------------------------------------------------------

Adapter::Adapter(ConquestMapLoader *conquest_map_loader) : MapLoader() {
    conquest_map_loader_ = conquest_map_loader;
}

Adapter::Adapter(const Adapter &adapter) : MapLoader(adapter) {
    conquest_map_loader_ = adapter.conquest_map_loader_;
}

Adapter::~Adapter() {
    conquest_map_loader_ = nullptr;
    delete conquest_map_loader_;
}

Adapter &Adapter::operator=(const Adapter &adapter) {
    conquest_map_loader_ = adapter.conquest_map_loader_;
    return *this;
}

bool Adapter::ParseMap() {
    return conquest_map_loader_->ParseConquestMap();
}