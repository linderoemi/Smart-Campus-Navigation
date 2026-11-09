#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <string>
#include <vector>


class HashTable {
private:
    struct Entry {
        std::string id;
        int facilityIndex;
    };


    static const int CAPACITY = 11;
    std::vector<std::vector<Entry>> buckets;
    int entries;
    int collisions;

    int hashID(const std::string& id) const;

public:
    HashTable();

    static std::string normalizeID(const std::string& id);
    static bool isValidID(const std::string& id);
    bool insert(const std::string& id, int facilityIndex);
    int find(const std::string& id) const;
    void displayStats() const;
};


#endif
