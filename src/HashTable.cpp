#include "HashTable.h"

#include <cctype>
#include <iostream>

using namespace std;

HashTable::HashTable() : buckets(CAPACITY) {
    entries = 0;
    collisions = 0;
}


//checking and validating the ID
string HashTable::normalizeID(const string& id) {
    size_t first = id.find_first_not_of(" \t\r\n\f\v");
    if (first == string::npos) {
        return "";
    }


    size_t last = id.find_last_not_of(" \t\r\n\f\v");
    string result = id.substr(first, last - first + 1);

    for (char& character : result) {
        character = static_cast<char>(toupper(static_cast<unsigned char>(character)));
    }


    return result;
}



bool HashTable::isValidID(const string& id) {
    if (id.size() != 4 || id[0] != 'F') {
        return false;
    }

    for (size_t i = 1; i < id.size(); i++) {
        if (id[i] < '0' || id[i] > '9') {
            return false;
        }
    }


    return true;
}

//compute hash i
int HashTable::hashID(const string& id) const {
    int index = 0;
    for (char character : id) {
        index = (index * 31 + character) % CAPACITY;
    }
    return index;
}


//inserting a new entry into the hash table
bool HashTable::insert(const string& id, int facilityIndex) {
    string key = normalizeID(id);
    if (!isValidID(key)) {
        return false;
    }


    vector<Entry>& bucket = buckets[hashID(key)];
    for (const Entry& entry : bucket) {
        if (entry.id == key) {
            return false;
        }
    }

    bucket.push_back({key, facilityIndex});
    if (bucket.size() > 1) {
        collisions++;
    }
    entries++;
    return true;
}



//Search for the facility index with the given ID.
int HashTable::find(const string& id) const {
    string key = normalizeID(id);
    if (!isValidID(key)) {
        return -1;
    }


    const vector<Entry>& bucket = buckets[hashID(key)];
    for (const Entry& entry : bucket) {
        if (entry.id == key) {
            return entry.facilityIndex;
        }
    }

    return -1;
}



//Printing the display stats of the hash table
void HashTable::displayStats() const {
    cout << " (hash capacity " << CAPACITY
         << ", entries " << entries
         << ", collisions " << collisions << ")";
}



