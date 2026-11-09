#include "DepartmentTree.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>

DepartmentTree::DepartmentTree(){
    root = nullptr;
}

void DepartmentTree::deleteTree(DepartmentNode* node) {
    if (node == nullptr) {
        return;
    }
    
    for (DepartmentNode* child : node->children) {
        deleteTree(child);
    }

    delete node;
}

DepartmentTree::~DepartmentTree() {
   deleteTree(root);
   root = nullptr;
}

DepartmentNode* DepartmentTree::findDepartment(
    DepartmentNode* node,
    const string& name) const {

    if (node == nullptr) {
        return nullptr;
    }
    
    if (normalizeName(node->name == name) == normalizeName(name)){
         return node;
    }

    for (DepartmentNode* child : node->children) {
         DepartmentNode* result = findDepartment(child, name);

         if (result != nullptr) {
             return result;
         }
    }
 return nullptr
}

bool DepartmentTree::isEmpty() const {
  return root == nullptr;
}

string DepartmentTree::trim(const string& value) const {
    size_t first = value.find_first_not_of(" \t\r\n");

    if (first == string::npos) {
        return "";
    }   

    size_t last = value.find_last_not_of(" \t\r\n");
    
    return value.substr(first, last - first + 1);
}

string DepartmentTree::normalizeName(const string& name) const {
    
    string result = name;
    

    transform(result.begin(), result.end(), result.begin(),
        [](unsigned char character) {
            return static_cast<char>(tolower(character));
        });
   return result;
}

bool DepartmentTree::loadFromFile(
    const string& filename,
    int& accepted,
    int& rejected) {

    ifstream inputFile(filename);

    accepted = 0;
    rejected = 0;

    if (!inputFile.is_open()) {
        cout << "Error: Unable to open file: "
             << filename << endl;
        return false;
    }
    string line;
    int lineNumber = 0;

    while (getline(inputFile, line)) {
        lineNumber++;

        line = trim(line);

        if (line.empty() || line[0] =='#') {
            continue;
        }

        stringstream record(line);
        string departmentName;
        string parentName;
        string extraField;

        if (!getline(record, departmentName, '|') ||
            !getline(record, parentName, '|') ||
            getline(record, extraField, '|')) {
            cout << filename << ":" << lineNumber
                 << ": Invalid number of fields." << endl;
            rejected++;
            continue;
        }
        departmentName = trim(departmentName);
        parentName = trim(parentName);

        if (departmentName.empty() || parentName.empty()) {
            cout << filename << ":" << lineNumber 
                 << ": Empty department name or parent."
                 << endl;
            rejected++;
            continue;
        }
        if (findDepartment(root, departmentName) != nullptr) {
            cout << filename << ":" << lineNumber
                 << ": Duplicate department name: "
                 << departmentName < endl;
            rejected++;
            continue;
        }

        if (root == nullptr) {
            if (normalizeName(parentName) != "none") {
                cout << filename << ":" << lineNumber
                     << ": First department must have parent NONE."
                     << endl;
                rejected++;
                continue;
            }

            root = new DepartmentNode(departmentName, nullptr);
            accepted++;
            continue;
        }
        if (normalizeName(parentName) == "none") {
            cout << filename << ":" << lineNumber
                 << ": Only the root can have parent NONE."
                 << endl;
            rejected++;
            continue;
        }
        DepartmentNode* parent =
            findDepartment(root, parentName);
        if (parent == nullptr) {
            cout << filename << ":" << lineNumber
                 << ": Parent department not found: "
                 << parentName << endl;
            rejected++;
            continue;
        }

        DepartmentNode* newDepartment =
            new DepartmentNode(departmentName, parent);

        parent->children.push_back(newDepartment);
        accepted++;
    }
    inputFile.close();
    cout << "Department loading complete." << endl;
    cout << "Accepted records: " << accepted <, endl;
    cout << "Rejected records: " << rejected <<endl;
    return true;
}
           
            

    









