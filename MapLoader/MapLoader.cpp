/**
 * Assignment #1 COMP345, FALL 2019
 * Authors: Giselle Martel (26352936), Wayne Tam (), Jeffrey Li (40017627), Rania Az (40041630)
 */

#include <stdexcept>
#include <string>
#include <iostream>

#include "MapLoader.h"

using namespace std;

MapLoader::MapLoader(string file_name) {
    cout << "Creating MapLoader object for file: " << file_name << endl;
    file_name_ = file_name;
}

MapLoader& MapLoader::operator=(const MapLoader &map) {
    parsed_map_ = map.parsed_map_;
    return *this;
}

MapLoader::MapLoader(const MapLoader &map) {
    parsed_map_ = map.parsed_map_;
}

MapLoader::~MapLoader() {
    delete parsed_map_;
}

void MapLoader::ParseMap() {
    string line;
    ifstream file_to_load(file_name_);
    bool file_is_valid = true;

    if(file_to_load.is_open()) {
        vector<Country*> countries;
        vector<Continent*> continents;
        int border_entry_count = 0;

        string map_name = file_name_.substr(0, '.');
        parsed_map_ = new Map(map_name);

        //read contents of .map file line by line
        while ( getline (file_to_load,line, '\n') && file_is_valid )
        {
            //if line is empty or line is comment, skip it
           if(line.length() == 0 ||  line.at(0) == ';') {
               continue;
           }

           if(line.find("[continents]") == 0) {
               //get the next line
               int current_id = 0;
               while(getline (file_to_load,line, '\n') && file_is_valid) {
                   bool line_is_valid = line.find("[") == -1 && line[0] != '\r';
                   //we have reached the end of the continents section
                   if(!line_is_valid) {
                       break;
                   } else if (line[0] == '\n' || line.length() == 0) {
                       continue;
                   } else {
                       string continent_data = line;
                       string delim = " ";
                       //parse the name of the continent
                       string continent_name = continent_data.substr(0, continent_data.find(delim));
                       continent_data.erase(0, continent_name.length() + delim.length());

                       if(continent_data.length() == 0) {
                           //throw error
                           cout << "continent " << continent_name << " is missing an army value. Please load a valid file\n\n";
                           file_is_valid = false;
                           return;
                       }

                       //parse the army value of the continent
                       string army_value_str = continent_data.substr(0, continent_data.find(delim));
                       int army_value;

                       try {
                           army_value = stoi(army_value_str);
                       } catch (const invalid_argument& e) {
                           cout << "the army value for continent " << continent_name << " is invalid. Please load a valid file.\n\n";
                           file_is_valid = false;
                           return;
                       }

                       //debug string
                       //cout << continent_name << " " << army_value << endl;

                       Continent* continent = new Continent(continent_name, army_value, current_id);
                       parsed_map_->AddContinentToMap(continent);
                       continents.push_back(continent);
                       ++current_id;
                   }
               }
           }

            if(line.find("[countries]") == 0) {
                int current_index = 0;
                //get the next line
                while(getline (file_to_load,line, '\n') && file_is_valid) {
                    bool line_is_valid = line.find("[") == -1 && line[0] != '\r';
                    //we have reached the end of the continents section
                    if(!line_is_valid) {
                      break;
                    } else if (line[0] == '\n' || line.length() == 0) {
                        continue;
                    } else {
                        string country_data = line;
                        string delim = " ";
                        //parse the name of the continent
                        string country_num_str = country_data.substr(0, country_data.find(delim));
                        int country_num;

                        try {
                            country_num = stoi(country_num_str);
                        } catch (const invalid_argument& e) {
                            cout << "the country number is invalid. Please load a valid file.\n\n";
                            file_is_valid = false;
                            return;
                        }

                        //ensure countries are in order
                        if(country_num !=0 && countries.size() > 0 && country_num < countries[current_index - 1]->GetCountryID()) {
                            cout << "Countries are not in order in the file. Please load a valid file\n\n";
                            file_is_valid = false;
                            return;
                        }

                        country_data.erase(0, country_num_str.length() + delim.length());

                        if(country_data.length() == 0) {
                            //throw error
                            cout << "country " << country_num << " is not associated to any continent. Please load a valid file\n\n";
                            file_is_valid = false;
                            return;
                        }

                        string continent_name = country_data.substr(0, country_data.find(delim));
                        country_data.erase(0, continent_name.length() + delim.length());

                        if(country_data.length() == 0) {
                            //throw error
                            cout << "country " << country_num << " continent is missing its index value. Please load a valid file\n\n";
                            file_is_valid = false;
                            return;
                        }

                        string continent_index_str = country_data.substr(0, country_data.find(delim));
                        int continent_index;

                        try {
                            continent_index = stoi(continent_index_str);
                        } catch (const invalid_argument& e) {
                            cout << "the index given for continent " << continent_name << " for country " << country_num << " is invalid. Please load a valid file.\n\n";
                            file_is_valid = false;
                            return;
                        }
                        country_data.erase(0, continent_index_str.length() + delim.length());

                        if(country_data.length() == 0) {
                            //throw error
                            cout << "country " << country_num << " is missing its X coordinate. Please load a valid file\n\n";
                            file_is_valid = false;
                            return;
                        }

                        string x_coordinate_str = country_data.substr(0, country_data.find(delim));
                        int x_coordinate;

                        try {
                            x_coordinate = stoi(x_coordinate_str);
                        } catch (const invalid_argument& e) {
                            cout << "the X coordinate for country" << country_num << " is invalid. Please load a valid file.\n\n";
                            file_is_valid = false;
                            return;
                        }
                        country_data.erase(0, x_coordinate_str.length() + delim.length());

                        if(country_data.length() == 0) {
                            //throw error
                            cout << "country " << country_num << " is missing its Y coordinate. Please load a valid file\n\n";
                            file_is_valid = false;
                            return;
                        }

                        string y_coordinate_str = country_data.substr(0, country_data.find(delim));
                        int y_coordinate;

                        try {
                            y_coordinate =  stoi(y_coordinate_str);
                        } catch (const invalid_argument& e) {
                            cout << "the Y coordinate for country" << country_num << " is invalid. Please load a valid file.\n\n";
                            file_is_valid = false;
                            return;
                        }
                        country_data.erase(0, y_coordinate_str.length() + delim.length());

                        //debug string
                        //cout << country_num << " " << continent_name << " " << continent_index << " " << x_coordinate << " " << y_coordinate << endl;

                        Country* country = new Country(country_num, continent_name, continent_index, x_coordinate, y_coordinate);
                        parsed_map_->AddCountryToMap(country);
                        countries.push_back(country);
                        ++current_index;
                    }
                }

                if(countries.size() > 0) {

                    parsed_map_->CreateAdjacencyMatrix();
                }
            }

            if(line.find("[borders]") == 0) {
                //get the next line
                int current_country = 0;
                while(getline (file_to_load,line, '\n') && file_is_valid) {
                    bool line_is_valid = line.find("[") == -1 && line[0] != '\r';
                    //we have reached the end of the border section
                    if(!line_is_valid) {
                        break;
                    } else if (line[0] == '\n' || line.length() == 0) {
                        continue;
                    } else {
                        string border_data = line;
                        vector<int> borders;

                        while(border_data.length() > 0 && border_data[0] != '\r') {
                            string delim = " ";
                            string border_str = border_data.substr(0, border_data.find(delim));
                            border_data.erase(0, border_str.length() + delim.length());

                            int border;
                            try{
                                border = stoi(border_str);
                                if(border == 0) {
                                    cout << "invalid values given for border. Please load a valid file\n\n";
                                    file_is_valid = false;
                                    return;
                                }
                                borders.push_back(border);
                            } catch( const invalid_argument& e) {
                                cout << "invalid values given for border. Please load a valid file\n\n";
                                file_is_valid = false;
                                return;
                            }

                            //debug string
                            //cout << border << " ";
                        }

                        if(borders.size() == 0) {
                            cout << "No borders specified for entry in borders section. Please load a valid file\n\n";

                        } else if(borders.size() > countries.size()) {
                            cout << "invalid values given for border. Please load a valid file.\n\n";
                            file_is_valid = false;
                            return;
                        } else {

                            for(int i = 1; i < borders.size(); ++i) {

                                if(i == current_country) {
                                    continue;
                                }
                                parsed_map_->SetTwoCountriesAsNeighbours(true, borders[0] - 1, borders[i] - 1);
                            }
                            ++current_country;
                            ++border_entry_count;
                        }
                    }
                }
            }
        }
        file_to_load.close();

        file_is_valid &= border_entry_count == countries.size();

        if(file_is_valid && countries.size() > 0 && continents.size() > 0) {
            cout << "Success! Generated map for file" << file_name_ << "!" << endl << "\nHere is the result:\n";
            parsed_map_->DisplayAdjacencyMatrix();
            cout << endl << endl;
        } else {
            cout << "Failed to generate map for file " << file_name_ << "! Please try again\n\n";
        }
    } else {
        cout << "unable to open the file " << file_name_ << ". Please try again\n\n";
    }
}

