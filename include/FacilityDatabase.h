#ifndef FACILITY_DATABASE_H
#define FACILITY_DATABASE_H

#include "HashTable.h"

#include <string>
#include <vector>



struct Facility {
    std::string id;
    std::string name;
    std::string building;
    std::string category;
};

class FacilityDatabase {
private:
    std::vector<Facility> facilities;
    HashTable idTable;

    std::string trim(const std::string& value) const;
    std::string normalizeName(const std::string& name) const;
    void displayFacility(const Facility& facility) const;


public:
    bool loadFromFile(const std::string& filename,
                      const std::vector<std::string>& buildings,
                      int& accepted, int& rejected);

    void displayAll() const;
    void searchByID(const std::string& id) const;
};


#endif
