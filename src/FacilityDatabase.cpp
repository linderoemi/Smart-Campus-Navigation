#include "FacilityDatabase.h"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

string FacilityDatabase::trim(const string& value) const {
    size_t first = value.find_first_not_of(" \t\r\n\f\v");
    if (first == string::npos) {
        return "";
    }

    size_t last = value.find_last_not_of(" \t\r\n\f\v");
    return value.substr(first, last - first + 1);
}



string FacilityDatabase::normalizeName(const string& name) const {
    string result = trim(name);
    for (char& character : result) {
        character = static_cast<char>(tolower(static_cast<unsigned char>(character)));
    }
    return result;
}


bool FacilityDatabase::loadFromFile(
    const string& filename,
    const vector<string>& buildings,
    int& accepted,
    int& rejected) {

    facilities.clear();
    idTable = HashTable();
    accepted = 0;
    rejected = 0;

    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cout << "Error: Unable to open file: " << filename << endl;
    }

    string line;
    int lineNumber = 0;

    while (getline(inputFile, line)) {
        lineNumber++;
        line = trim(line);

        if (line.empty() || line[0] == '#') {
            continue;
        }

        if (count(line.begin(), line.end(), '|') != 3) {
            cout << "Warning: " << filename << ":" << lineNumber
                 << ": Expected four fields." << endl;
            rejected++;
            continue;
        }


        stringstream record(line);
        Facility facility;
        getline(record, facility.id, '|');
        getline(record, facility.name, '|');
        getline(record, facility.building, '|');
        getline(record, facility.category);

        facility.id = HashTable::normalizeID(facility.id);
        facility.name = trim(facility.name);
        facility.building = trim(facility.building);
        facility.category = trim(facility.category);


        if (facility.id.empty() || facility.name.empty() ||
            facility.building.empty() || facility.category.empty()) {
            cout << "Warning: " << filename << ":" << lineNumber
                 << ": Empty facility field." << endl;
            rejected++;
            continue;
        }

        if (!HashTable::isValidID(facility.id)) {
            cout << "Warning: " << filename << ":" << lineNumber
                 << ": Invalid ID. Use F followed by three digits." << endl;
            rejected++;
            continue;
        }


        string buildingName;
        string buildingKey = normalizeName(facility.building);
        for (const string& building : buildings) {
            if (normalizeName(building) == buildingKey) {
                buildingName = building;
                break;
            }

        }

        if (buildingName.empty()) {
            cout << "Warning: " << filename << ":" << lineNumber
                 << ": Unknown building: " << facility.building << endl;
            rejected++;
            continue;
        }

        facility.building = buildingName;

        // Keep the category spelling from the first accepted record.
        string categoryKey = normalizeName(facility.category);
        for (const Facility& existing : facilities) {
            if (normalizeName(existing.category) == categoryKey) {
                facility.category = existing.category;
                break;
            }

        }

        if (!idTable.insert(facility.id, accepted)) {
            cout << "Warning: " << filename << ":" << lineNumber
                 << ": Duplicate facility ID: " << facility.id << endl;
            rejected++;
            continue;
        }


        facilities.push_back(facility);
        accepted++;
    }


    cout << filename << ": " << accepted << " accepted, "
         << rejected << " rejected";
    idTable.displayStats();
    cout << endl;
    return inputFile.is_open();


}




void FacilityDatabase::displayFacility(const Facility& facility) const {
    cout << facility.id << " | " << facility.name << " | "
         << facility.building << " | " << facility.category << endl;
}

void FacilityDatabase::displayAll() const {
    if (facilities.empty()) {
        cout << "No facilities are loaded." << endl;

    }

    for (const Facility& facility : facilities) {
        displayFacility(facility);
    }


    cout << "Total facilities: " << facilities.size() << endl;
}




void FacilityDatabase::searchByID(const string& id) const {
    string key = HashTable::normalizeID(id);
    if (!HashTable::isValidID(key)) {
        cout << "Invalid ID format. Use F followed by three digits." << endl;
        return;

    }


    int index = idTable.find(key);
    if (index == -1) {
        cout << "No facility found with ID " << key << "." << endl;
        return;

    }


    displayFacility(facilities[index]);
}
