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
    if (node->name == name) {
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

bool Departmenttree::isEmpty() const {
  return root == nullptr;
}
    









